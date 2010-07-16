#include <QDir>
#include <QFile>
#include <QDateTime>
#include <set>

#include "outputcreator.h"
#include "qtframework.h"

cOutputCreator::cOutputCreator( cLogDataSource *p_poDataSource, tmActionList *p_poActionList, const QString &p_qsDirPrefix )
{
    cTracer  obTracer( "cOutputCreator::cOutputCreator" );

    m_poDataSource = p_poDataSource;
    m_poActionList = p_poActionList;
    m_qsOutDir     = QDir::cleanPath( g_poPrefs->getOutputDir() + "/" + p_qsDirPrefix );
}

cOutputCreator::~cOutputCreator()
{
    cTracer  obTracer( "cOutputCreator::~cOutputCreator" );

    for( tiActionCountList itActionCount = m_maActionCounts.begin(); itActionCount != m_maActionCounts.end(); itActionCount++ )
    {
        delete itActionCount->second;
    }
}

void cOutputCreator::countActions() throw()
{
    cTracer  obTracer( "cOutputCreator::countActions" );

    for( tiActionList itAction = m_poActionList->begin(); itAction != m_poActionList->end(); itAction++ )
    {
        tsActionResCount  *poResCount = NULL;
        tiActionCountList  itResCount = m_maActionCounts.find( itAction->second.name() );
        if( itResCount == m_maActionCounts.end() )
        {
            poResCount = new tsActionResCount;
            poResCount->ulFailed = 0;
            poResCount->ulOk     = 0;
            m_maActionCounts.insert( pair<QString, tsActionResCount*>( itAction->second.name(), poResCount ) );
        }
        else
        {
            poResCount = itResCount->second;
        }

        if( itAction->second.result() == cActionResult::OK ) poResCount->ulOk++;
        else poResCount->ulFailed++;
    }
}

void cOutputCreator::generateActionSummary() const throw( cSevException )
{
    cTracer  obTracer( "cOutputCreator::generateActionSummary" );

    QDir obDir;
    if( !obDir.exists( m_qsOutDir ) ) obDir.mkpath( m_qsOutDir );

    QString qsFileName = m_qsOutDir + "/actionsummary.txt";
    QFile   obActionSummaryFile( qsFileName );
    if( !obActionSummaryFile.open( QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text ) )
        throw cSevException( cSeverity::ERROR, QString( "%1: %2" ).arg( qsFileName ).arg( obActionSummaryFile.errorString() ).toStdString() );

    obActionSummaryFile.write( "This is an Action Summary file generated by " + g_poPrefs->getAppName().toAscii() );
    obActionSummaryFile.write( " version " + g_poPrefs->getVersion().toAscii() + "\n" );

    obActionSummaryFile.write( "Generation time: " );
    obActionSummaryFile.write( QDateTime::currentDateTime().toString( "dd-MMM-yyyy hh:mm:ss" ).toAscii() + "\n\n" );

    obActionSummaryFile.write( "Input files:\n" );
    QStringList slInputFiles = m_poDataSource->origFileList();
    for( int i = 0; i < slInputFiles.size(); i++ )
    {
        obActionSummaryFile.write( QString::number( i ).toAscii() + " " );
        obActionSummaryFile.write( slInputFiles.at( i ).toAscii() + "\n" );
    }
    obActionSummaryFile.write( "\n" );

    obActionSummaryFile.write( "Identified Actions:\n" );
    for( tiActionList itAction = m_poActionList->begin(); itAction != m_poActionList->end(); itAction++ )
    {
        obActionSummaryFile.write( itAction->second.timeStamp().toAscii() + " " );
        obActionSummaryFile.write( itAction->second.name().toAscii() + " " );
        obActionSummaryFile.write( cActionResult::toStr( itAction->second.result() ) );
        obActionSummaryFile.write( " " + slInputFiles.at( itAction->second.fileId() ).toAscii() + ":" );
        obActionSummaryFile.write( QString::number( itAction->second.lineNum() ).toAscii() + "\n" );
    }

    obActionSummaryFile.write( "\n" );

    obActionSummaryFile.write( "Action Counts:\n" );
    for( tiActionCountList itAction = m_maActionCounts.begin(); itAction != m_maActionCounts.end(); itAction++ )
    {
        obActionSummaryFile.write( itAction->first.toAscii() );
        obActionSummaryFile.write( " OK: " + QString::number( itAction->second->ulOk ).toAscii() );
        obActionSummaryFile.write( " FAILED: " + QString::number( itAction->second->ulFailed ).toAscii() );
        obActionSummaryFile.write( " TOTAL: " + QString::number( itAction->second->ulOk + itAction->second->ulFailed ).toAscii() );
        obActionSummaryFile.write( "\n" );
    }

    obActionSummaryFile.flush();
    obActionSummaryFile.close();
}