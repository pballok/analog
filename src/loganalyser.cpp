#include <QDir>
#include <cstdlib>
#include <stdio.h>

#include "lara.h"
#include "loganalyser.h"

const unsigned long long  g_ulMSecPerYear   = 32140800000;
const unsigned long long  g_ulMSecPerMonth  = 2678400000;
const unsigned long long  g_ulMSecPerDay    = 86400000;
const unsigned long long  g_ulMSecPerHour   = 3600000;
const unsigned long long  g_ulMSecPerMinute = 60000;
const unsigned long long  g_ulMSecPerSec    = 1000;

cLogAnalyser::cLogAnalyser( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions, cOutputCreator *p_poOC ) throw()
{
    cTracer obTracer( &g_obLogger, "cLogAnalyser::cLogAnalyser",
                      QString( "prefix: \"%1\", files: \"%2\", actions:\"%3\"" ).arg( p_qsPrefix ).arg( p_qsFiles ).arg( p_qsActions ).toStdString() );

    QString qsInputDir = g_poPrefs->inputDir();
    qsInputDir += QDir::separator();
    qsInputDir += p_qsPrefix;
    qsInputDir = QDir::cleanPath( qsInputDir );
    m_poDataSource    = new cLogDataSource( qsInputDir, p_qsFiles );

    m_poActionDefList = new cActionDefList( p_qsActions, "data/lara_actions.xsd" );

    m_poOC = p_poOC;
}

cLogAnalyser::~cLogAnalyser() throw()
{
    cTracer  obTracer( &g_obLogger, "cLogAnalyser::~cLogAnalyser" );

    delete m_poActionDefList;
    delete m_poDataSource;
}

void cLogAnalyser::analyse() throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cLogAnalyser::analyse" );

    QStringList slLogFiles = m_poDataSource->logFileList();
    for( int i = 0; i < slLogFiles.size(); i++ )
    {
        findPatterns( slLogFiles.at( i ) );
    }

    identifySingleLinerActions();

    for( cActionDefList::tiCountActionList itCountAction = m_poActionDefList->countActionBegin();
         itCountAction != m_poActionDefList->countActionEnd();
         itCountAction++ )
    {
        for( cCountAction::tiActionsToCount itActionToCount = itCountAction->actionsToCountBegin();
             itActionToCount != itCountAction->actionsToCountEnd();
             itActionToCount++ )
        {
            countActions( itCountAction->name(), *itActionToCount );
        }
    }

    storeActions();
}

void cLogAnalyser::findPatterns( const QString &p_qsFileName ) throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cLogAnalyser::findPatterns", p_qsFileName.toStdString() );

    unsigned int uiFileId = m_poOC->fileId( p_qsFileName );

    for( cActionDefList::tiPatternList itPattern = m_poActionDefList->patternBegin();
         itPattern != m_poActionDefList->patternEnd();
         itPattern++ )
    {
        QString qsCommand = QString( "pcregrep -n \"%1\" %2" ).arg( itPattern->pattern() ).arg( p_qsFileName );

        tmFoundPatternList::iterator itLastPattern = m_maFoundPatterns.begin();

        FILE*  poGrepOutput = popen( qsCommand.toAscii(), "r" );
        char poLogLine[1000] = "";
        while( !feof( poGrepOutput ) )
        {
            if( fgets( poLogLine, 1000, poGrepOutput ) )
                storePattern( uiFileId, itPattern, QString::fromAscii( poLogLine ), &itLastPattern );
        }

        pclose( poGrepOutput );
    }

    obTracer << "Found " << m_maFoundPatterns.size() << " patterns so far";
}

void cLogAnalyser::storePattern( const unsigned int p_uiFileId, cActionDefList::tiPatternList p_itPattern, const QString &p_qsLogLine,
                                 tmFoundPatternList::iterator  *p_poInsertPos ) throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cLogAnalyser::storePattern", p_itPattern->name().toStdString() );

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

    QStringList  slCaptures = p_itPattern->captures();
    if( slCaptures.size() )
    {
        QStringList  slCapturedTexts = p_itPattern->capturedTexts( qsLogLine );
        for( int i = 0; i < slCaptures.size(); i++ )
        {
            if( i < slCapturedTexts.size() - 1 )
                suFoundPattern.maCaptures.insert( pair<QString,QString>( slCaptures.at( i ), slCapturedTexts.at( i + 1 ) ) );
        }
    }

    *p_poInsertPos = m_maFoundPatterns.insert( *p_poInsertPos, pair<QString, tsFoundPattern>( p_itPattern->name(), suFoundPattern ) );
}

void cLogAnalyser::identifySingleLinerActions() throw()
{
    cTracer  obTracer( &g_obLogger, "cLogAnalyser::identifySingleLinerActions" );

    for( cActionDefList::tiSingleLinerList itSingleLiner = m_poActionDefList->singleLinerBegin();
         itSingleLiner != m_poActionDefList->singleLinerEnd();
         itSingleLiner++ )
    {
        pair<tiFoundPatternList,tiFoundPatternList> paFoundActionPatterns = m_maFoundPatterns.equal_range( itSingleLiner->pattern() );
        for( tiFoundPatternList  itFoundPattern = paFoundActionPatterns.first;
             itFoundPattern != paFoundActionPatterns.second;
             itFoundPattern++ )
        {
            cAction  obAction( itSingleLiner->name(), itFoundPattern->second.qsTimeStamp,
                               itFoundPattern->second.uiFileId, itFoundPattern->second.ulLineNum,
                               itSingleLiner->result(), itSingleLiner->upload() );
            if( itFoundPattern->second.maCaptures.size() )
            {
                for( tiActionCapturedTexts itCapture = itFoundPattern->second.maCaptures.begin();
                     itCapture != itFoundPattern->second.maCaptures.end();
                     itCapture++ )
                {
                    obAction.addCapturedText( itCapture->first, itCapture->second );
                }
            }

            m_mmActionList.insert( pair<QString, cAction>(obAction.name(), obAction ) );
        }
    }
}

void cLogAnalyser::countActions( const QString &p_qsCountName,
                                 const QString &p_qsActionName ) throw()
{
    cTracer  obTracer( &g_obLogger, "cLogAnalyser::countActions",
                       QString( "CountName: \"%1\" ActionName: \"%2\"" ).arg( p_qsCountName ).arg( p_qsActionName ).toStdString() );

    unsigned long ulFailed = 0;
    unsigned long ulOk     = 0;

    pair<tiActionList, tiActionList> paActionsToCount = m_mmActionList.equal_range( p_qsActionName );
    for( tiActionList itAction = paActionsToCount.first; itAction != paActionsToCount.second; itAction++ )
    {
        if( itAction->second.result() == cActionResult::OK ) ulOk++;
        else ulFailed++;
    }

    m_poOC->addCountAction( p_qsCountName, ulOk, ulFailed );

    obTracer << QString( "Ok: %1 Failed: %2" ).arg( ulOk ).arg( ulFailed ).toStdString();
}

void cLogAnalyser::storeActions() throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cLogAnalyser::storeActions" );

    for( tiActionList itAction = m_mmActionList.begin();
         itAction != m_mmActionList.end();
         itAction++ )
    {
        m_poOC->addAction( &(itAction->second) );
    }
}
