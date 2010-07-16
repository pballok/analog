#include <QDir>
#include <cstdlib>
#include <stdio.h>

#include "loganalyzer.h"
#include "qtframework.h"

extern const unsigned long long g_ulMSecPerYear;
extern const unsigned long long g_ulMSecPerMonth;
extern const unsigned long long g_ulMSecPerDay;
extern const unsigned long long g_ulMSecPerHour;
extern const unsigned long long g_ulMSecPerMinute;
extern const unsigned long long g_ulMSecPerSec;

cLogAnalyzer::cLogAnalyzer( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions ) throw()
{
    string stParams = "prefix: \"" + p_qsPrefix.toStdString();
    stParams += "\", files: \"" + p_qsFiles.toStdString();
    stParams += "\", actions: \"" + p_qsActions.toStdString();
    stParams += "\"";
    cTracer  obTracer( "cLogAnalyser::cLogAnalyser", stParams );

    QString qsInputDir = g_poPrefs->getInputDir();
    qsInputDir += QDir::separator();
    qsInputDir += p_qsPrefix;
    qsInputDir += QDir::separator();
    qsInputDir = QDir::cleanPath( qsInputDir );
    m_poDataSource    = new cLogDataSource( qsInputDir, p_qsFiles );

    m_poActionDefList = new cActionDefList( p_qsActions );
}

cLogAnalyzer::~cLogAnalyzer() throw()
{
    cTracer  obTracer( "cLogAnalyser::~cLogAnalyser" );

    delete m_poActionDefList;
    delete m_poDataSource;
}

void cLogAnalyzer::analyze() throw( cSevException )
{
    cTracer  obTracer( "cLogAnalyser::analyze" );

    QStringList slLogFiles = m_poDataSource->logFileList();
    for( int i = 0; i < slLogFiles.size(); i++ )
    {
        findPatterns( i, slLogFiles.at( i ) );
    }

    identifySingleLinerActions();
}

void cLogAnalyzer::findPatterns( const unsigned int p_uiFileId, const QString &p_qsFileName ) throw( cSevException )
{
    cTracer  obTracer( "cLogAnalyser::findPatterns", p_qsFileName.toStdString() );

    for( cActionDefList::tiPatternList itPattern = m_poActionDefList->patternBegin();
         itPattern != m_poActionDefList->patternEnd();
         itPattern++ )
    {
        QString qsCommand = QString( "grep -n \"%1\" %2" ).arg( itPattern->pattern() ).arg( p_qsFileName );
        tmFoundPatternList::iterator itLastPattern = m_maFoundPatterns.begin();

        FILE*  poGrepOutput = popen( qsCommand.toAscii(), "r" );
        char poLogLine[1000] = "";
        while( !feof( poGrepOutput ) )
        {
            if( fgets( poLogLine, 1000, poGrepOutput ) )
                storePattern( p_uiFileId, itPattern->name(), QString::fromAscii( poLogLine ), &itLastPattern );
        }

        pclose( poGrepOutput );
    }


    obTracer << "Found " << m_maFoundPatterns.size() << " patterns";
}

void cLogAnalyzer::storePattern( const unsigned int p_uiFileId, const QString &p_qsPatternName, const QString &p_qsLogLine,
                                 tmFoundPatternList::iterator  *p_poInsertPos ) throw( cSevException )
{
    cTracer  obTracer( "cLogAnalyser::storePattern", p_qsPatternName.toStdString() );

    QString qsLogLine = p_qsLogLine.section( ':', 1 ); //Remove line number from front
    qsLogLine.chop( 1 );                               // and the new line character from end

    QRegExp obTimeStampRegExp = m_poActionDefList->timeStampRegExp();
    if( obTimeStampRegExp.indexIn( qsLogLine ) == -1 )
        throw cSevException( cSeverity::ERROR, "TimeStamp Regular Expression does not match on Log Line.");

    QStringList    slTimeStampParts = obTimeStampRegExp.capturedTexts();
    tsFoundPattern suFoundPattern;

    suFoundPattern.qsTimeStamp = slTimeStampParts.at( 0 );

    suFoundPattern.ulTimeStamp = 0;
    for( int i = 1; i < slTimeStampParts.size(); i++ )
    {
        switch( m_poActionDefList->timeStampPart( i - 1 ) )
        {
            case cTimeStampPart::YEAR:    suFoundPattern.ulTimeStamp += slTimeStampParts.at( i ).toULongLong() * g_ulMSecPerYear;   break;
            case cTimeStampPart::MONTH:   suFoundPattern.ulTimeStamp += slTimeStampParts.at( i ).toULongLong() * g_ulMSecPerMonth;  break;
            case cTimeStampPart::DAY:     suFoundPattern.ulTimeStamp += slTimeStampParts.at( i ).toULongLong() * g_ulMSecPerDay;    break;
            case cTimeStampPart::HOUR:    suFoundPattern.ulTimeStamp += slTimeStampParts.at( i ).toULongLong() * g_ulMSecPerHour;   break;
            case cTimeStampPart::MINUTE:  suFoundPattern.ulTimeStamp += slTimeStampParts.at( i ).toULongLong() * g_ulMSecPerMinute; break;
            case cTimeStampPart::SECOND:  suFoundPattern.ulTimeStamp += slTimeStampParts.at( i ).toULongLong() * g_ulMSecPerSec;    break;
            case cTimeStampPart::MSECOND: suFoundPattern.ulTimeStamp += slTimeStampParts.at( i ).toULongLong();                     break;
            default: ;
        }
    }

    suFoundPattern.uiFileId = p_uiFileId;
    suFoundPattern.ulLineNum = p_qsLogLine.section( ':', 0, 0 ).toULong();

    *p_poInsertPos = m_maFoundPatterns.insert( *p_poInsertPos, pair<QString, tsFoundPattern>( p_qsPatternName, suFoundPattern ) );
}

void cLogAnalyzer::identifySingleLinerActions() throw()
{
    cTracer  obTracer( "cLogAnalyser::identifySingleLinerActions" );

    for( cActionDefList::tiSingleLinerList itSingleLiner = m_poActionDefList->singleLinerBegin();
         itSingleLiner != m_poActionDefList->singleLinerEnd();
         itSingleLiner++ )
    {
        tmActionList::iterator  itLastAction = m_maActions.begin();

        pair<tiFoundPatternList,tiFoundPatternList> paFoundActionPatterns = m_maFoundPatterns.equal_range( itSingleLiner->pattern() );
        for( tiFoundPatternList  itFoundPattern = paFoundActionPatterns.first;
             itFoundPattern != paFoundActionPatterns.second;
             itFoundPattern++ )
        {
            cAction  obAction( itSingleLiner->name(), itFoundPattern->second.qsTimeStamp,
                               itFoundPattern->second.uiFileId, itFoundPattern->second.ulLineNum,
                               itSingleLiner->result(), itSingleLiner->upload() );
            itLastAction = m_maActions.insert( itLastAction, pair<QString, cAction>( itSingleLiner->name(), obAction ) );
        }
    }

    obTracer << "Found " << m_maActions.size() << " actions";
}
