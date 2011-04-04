#include <logger.h>
#include <qtmysqlconnection.h>
#include <preferences.h>

#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>

#include "action.h"

#include "outputcreatortest.h"

extern cLogger       g_obLogger;
extern cPreferences *g_poPrefs;

cOutputCreatorTest::cOutputCreatorTest() throw() : cUnitTest( "Output Creator" )
{
    m_poOC = new cOutputCreator( "." );
}

cOutputCreatorTest::~cOutputCreatorTest() throw()
{
    delete m_poOC;
}

void cOutputCreatorTest::run() throw()
{
    testTextFileResults();
    testDatabaseResults();
    testCombilogResults();
}

void cOutputCreatorTest::testTextFileResults()  throw()
{
    printNote( "TEXT FILE RESULTS TESTS" );

    try
    {
        m_poOC->fileId( "test_input.log.1" );
        m_poOC->fileId( "test_input.log.2" );

        QStringList slExpectedActionListContent;
        QStringList slExpectedActionSummaryContent;

        cAction::tsTimeStamp  suTimeStamp;
        suTimeStamp.uiYear    = 2000;
        suTimeStamp.uiMonth   = 1;
        suTimeStamp.uiDay     = 12;
        suTimeStamp.uiHour    = 13;
        suTimeStamp.uiMinute  = 42;
        suTimeStamp.uiSecond  = 20;
        suTimeStamp.uiMSecond = 476;
        cAction *poAction = new cAction( "TEST_ACTION_1", "2000-01-12 13:42:20.476",
                                         &suTimeStamp, 0, 38, cActionResult::OK,
                                         cActionUpload::ALWAYS );
        poAction->addAttribute( "occurrencePattern", "LARA_TEST_OK_ALWAYS" );
        m_poOC->addAction( poAction );
        slExpectedActionListContent << "2000-01-12 13:42:20.476 TEST_ACTION_1 OK occurrencePattern=\"LARA_TEST_OK_ALWAYS\" test_input.log.1:38";
        delete poAction;

        suTimeStamp.uiHour    = 14;
        poAction = new cAction( "TEST_ACTION_2", "2000-01-12 14:42:20.476",
                                &suTimeStamp, 0, 39, cActionResult::OK,
                                cActionUpload::OK );
        poAction->addAttribute( "occurrencePattern", "LARA_TEST_OK_OK" );
        m_poOC->addAction( poAction );
        slExpectedActionListContent << "2000-01-12 14:42:20.476 TEST_ACTION_2 OK occurrencePattern=\"LARA_TEST_OK_OK\" test_input.log.1:39";
        delete poAction;

        suTimeStamp.uiHour    = 15;
        poAction = new cAction( "TEST_ACTION_3", "2000-01-12 15:42:20.476",
                                &suTimeStamp, 0, 40, cActionResult::OK,
                                cActionUpload::FAILED );
        poAction->addAttribute( "occurrencePattern", "LARA_TEST_OK_FAILED" );
        m_poOC->addAction( poAction );
        slExpectedActionListContent << "2000-01-12 15:42:20.476 TEST_ACTION_3 OK occurrencePattern=\"LARA_TEST_OK_FAILED\" test_input.log.1:40";
        delete poAction;

        suTimeStamp.uiHour    = 16;
        poAction = new cAction( "TEST_ACTION_4", "2000-01-12 16:42:20.476",
                                &suTimeStamp, 0, 41, cActionResult::OK,
                                cActionUpload::NEVER );
        m_poOC->addAction( poAction );
        slExpectedActionListContent << "2000-01-12 16:42:20.476 TEST_ACTION_4 OK test_input.log.1:41";
        delete poAction;

        suTimeStamp.uiHour    = 17;
        poAction = new cAction( "TEST_ACTION_5", "2000-01-12 17:42:20.476",
                                &suTimeStamp, 1, 38, cActionResult::FAILED,
                                cActionUpload::ALWAYS );
        m_poOC->addAction( poAction );
        slExpectedActionListContent << "2000-01-12 17:42:20.476 TEST_ACTION_5 FAILED test_input.log.2:38";
        delete poAction;

        suTimeStamp.uiHour    = 18;
        poAction = new cAction( "TEST_ACTION_6", "2000-01-12 18:42:20.476",
                                &suTimeStamp, 1, 39, cActionResult::FAILED,
                                cActionUpload::OK );
        poAction->addAttribute( "occurrencePattern", "LARA_TEST_FAILED_OK" );
        m_poOC->addAction( poAction );
        slExpectedActionListContent << "2000-01-12 18:42:20.476 TEST_ACTION_6 FAILED occurrencePattern=\"LARA_TEST_FAILED_OK\" test_input.log.2:39";
        delete poAction;

        suTimeStamp.uiHour    = 19;
        poAction = new cAction( "TEST_ACTION_7", "2000-01-12 19:42:20.476",
                                &suTimeStamp, 1, 40, cActionResult::FAILED,
                                cActionUpload::FAILED );
        poAction->addAttribute( "occurrencePattern", "LARA_TEST_FAILED_FAILED" );
        m_poOC->addAction( poAction );
        slExpectedActionListContent << "2000-01-12 19:42:20.476 TEST_ACTION_7 FAILED occurrencePattern=\"LARA_TEST_FAILED_FAILED\" test_input.log.2:40";
        delete poAction;

        suTimeStamp.uiHour    = 20;
        poAction = new cAction( "TEST_ACTION_8", "2000-01-12 20:42:20.476",
                                &suTimeStamp, 1, 41, cActionResult::FAILED,
                                cActionUpload::NEVER );
        m_poOC->addAction( poAction );
        slExpectedActionListContent << "2000-01-12 20:42:20.476 TEST_ACTION_8 FAILED test_input.log.2:41";
        delete poAction;

        m_poOC->addCountAction( "nbPatients", 42, 38 );
        slExpectedActionSummaryContent << "nbPatients OK: 42 FAILED: 38 TOTAL: 80";

        m_poOC->addCountAction( "nbMovements", 14, 8 );
        m_poOC->addCountAction( "nbMovements", 10, 20 );
        slExpectedActionSummaryContent << "nbMovements OK: 24 FAILED: 28 TOTAL: 52";

        m_poOC->addAttribute( "cellName", "LARA_TEST_CELL" );
        slExpectedActionSummaryContent << "cellName: LARA_TEST_CELL";

        QString qsActionListFileName    = g_poPrefs->outputDir() + "/" + "actionlist.txt";
        QString qsActionSummaryFileName = g_poPrefs->outputDir() + "/" + "actionsummary.txt";
        QFile::remove( qsActionListFileName );
        QFile::remove( qsActionSummaryFileName );
        m_poOC->generateActionList();
        m_poOC->generateActionSummary();

        checkFileContents( qsActionListFileName.toStdString(), slExpectedActionListContent );
        checkFileContents( qsActionSummaryFileName.toStdString(), slExpectedActionSummaryContent );

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_uiFailedNum++;
    }
}

void cOutputCreatorTest::testDatabaseResults()  throw()
{
    printNote( "DATABASE RESULTS TESTS" );

    try
    {
        unsigned long long ulSummaryId = m_poOC->uploadActionSummary();

        QSqlQuery obSummaryQuery( QString( "SELECT nbPatients, nbMovements, cellName FROM cyclerconfigs WHERE cyclerconfigId=%1" ).arg( ulSummaryId ) );

        testCase( "Number of cyclerconfigs records created", 1, obSummaryQuery.size() );

        obSummaryQuery.first();
        testCase( "Value of nbPatients column of the new record", 80, obSummaryQuery.value( 0 ).toInt() );
        testCase( "Value of nbMovements column of the new record", 52, obSummaryQuery.value( 1 ).toInt() );
        testCase( "Value of the cellName column of the new record", "LARA_TEST_CELL", obSummaryQuery.value( 2 ).toString().toStdString() );

        m_poOC->uploadActionList();

        QSqlQuery obListQuery( QString( "SELECT occurrencePattern FROM occurrences WHERE cyclerconfigId=%1" ).arg( ulSummaryId ) );

        testCase( "Number of occurrences records created", 4, obListQuery.size() );

        if( obListQuery.first() )
            testCase( "Value of occurrencePattern column of occurrence record 1",
                      "LARA_TEST_OK_ALWAYS", obListQuery.value( 0 ).toString().toStdString() );

        if( obListQuery.next() )
            testCase( "Value of occurrencePattern column of occurrence record 2",
                      "LARA_TEST_OK_OK", obListQuery.value( 0 ).toString().toStdString() );

        if( obListQuery.next() )
            testCase( "Value of occurrencePattern column of occurrence record 3",
                      "", obListQuery.value( 0 ).toString().toStdString() );

        if( obListQuery.next() )
            testCase( "Value of occurrencePattern column of occurrence record 4",
                      "LARA_TEST_FAILED_FAILED", obListQuery.value( 0 ).toString().toStdString() );

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_uiFailedNum++;
    }
}

void cOutputCreatorTest::testCombilogResults()  throw()
{
    printNote( "COMBILOG RESULTS TESTS" );

    try
    {
        QStringList slExpectedCombilogContent;

        m_poOC->addCombilogEntry( 3, "CombiLog Line 3", "#0000AA" );
        slExpectedCombilogContent << "<div><pre class=\"combilogline\" style=\"background: #0000AA\">CombiLog Line 3</pre></div>";

        m_poOC->addCombilogEntry( 1, "CombiLog Line 1", "#000088" );
        slExpectedCombilogContent << "<div><pre class=\"combilogline\" style=\"background: #000088\">CombiLog Line 1</pre></div>";

        m_poOC->addCombilogEntry( 2, "CombiLog Line 2", "#000099" );
        slExpectedCombilogContent << "<div><pre class=\"combilogline\" style=\"background: #000099\">CombiLog Line 2</pre></div>";

        m_poOC->addCombilogEntry( 5, "CombiLog Line 5", "#0000CC" );
        slExpectedCombilogContent << "<div><pre class=\"combilogline\" style=\"background: #0000CC\">CombiLog Line 5</pre></div>";

        m_poOC->addCombilogEntry( 6, "CombiLog Line 6", "#0000DD" );
        slExpectedCombilogContent << "<div><pre class=\"combilogline\" style=\"background: #0000DD\">CombiLog Line 6</pre></div>";

        m_poOC->addCombilogEntry( 4, "CombiLog Line 4", "#0000BB" );
        slExpectedCombilogContent << "<div><pre class=\"combilogline\" style=\"background: #0000BB\">CombiLog Line 4</pre></div>";

        QString qsCombilogFileName = g_poPrefs->outputDir() + "/" + "combilog.html";
        QFile::remove( qsCombilogFileName );

        m_poOC->generateCombilog();

        checkFileContents( qsCombilogFileName.toStdString(), slExpectedCombilogContent );

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_uiFailedNum++;
    }
}
