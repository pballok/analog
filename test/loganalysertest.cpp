#include <QStringList>
#include <QFile>

#include <logger.h>
#include <preferences.h>

#include <action.h>
#include <loganalyser.h>

#include "loganalysertest.h"

extern cLogger       g_obLogger;
extern cPreferences *g_poPrefs;

cLogAnalyserTest::cLogAnalyserTest() throw() : cUnitTest( "Log Analyser" )
{
}

cLogAnalyserTest::~cLogAnalyserTest() throw()
{
}

void cLogAnalyserTest::run() throw()
{
    testAction();
    testLogAnalyser();
}

void cLogAnalyserTest::testAction() throw()
{
    printNote( "IDENTIFIED ACTION TESTS" );

    try
    {
        cAction::tsTimeStamp suTimeStamp;
        suTimeStamp.uiYear    = 2010;
        suTimeStamp.uiMonth   = 8;
        suTimeStamp.uiDay     = 2;
        suTimeStamp.uiHour    = 15;
        suTimeStamp.uiMinute  = 27;
        suTimeStamp.uiSecond  = 11;
        suTimeStamp.uiMSecond = 97;
        cAction  obAction( "ActionTest", "ActionTimeStamp", &suTimeStamp, 42, 3, cActionResult::OK, cActionUpload::NEVER );

        testCase( "Name Test", "ActionTest", obAction.name().toStdString() );

        cAction::tsTimeStamp tsStoredStamp = obAction.timeStampStruct();
        testCase( "TimeStampStruct Test", 27, tsStoredStamp.uiMinute );

        testCase( "TimeStamp Test", "ActionTimeStamp", obAction.timeStamp().toStdString() );

        testCase( "FileId Test", 42, obAction.fileId() );

        testCase( "LineNum Test", 3, obAction.lineNum() );

        testCase( "Result Test", cActionResult::OK, obAction.result() );

        testCase( "Upload Test", cActionUpload::NEVER, obAction.upload() );

        bool boAttribsEmpty = (obAction.attributesBegin() == obAction.attributesEnd() );
        testCase( "Attributes Container must be empty", true, boAttribsEmpty );

        obAction.addAttribute( QString::fromStdString( "Palin" ), QString::fromStdString( "Pontius Pilate" ) );
        obAction.addAttribute( QString::fromStdString( "Chapman" ), QString::fromStdString( "Biggus Dickus" ) );
        obAction.addAttribute( QString::fromStdString(  "Cleese" ), QString::fromStdString( "Reg" ) );
        int inCounter = 0;
        for( tiActionAttribs itAttrib = obAction.attributesBegin();
            itAttrib != obAction.attributesEnd();
            itAttrib++ )
        {
            switch( ++inCounter )
            {
            /* The captured texts are stored in a multimap that orders the stored value
               alphabetically based on the key. That is why the extracted order is not the
               same as the order in which they were added to the container */
            case 1: testCase( "Attribute 1 Name", "Chapman", itAttrib->first.toStdString() );
                testCase( "Attribute 1 Value", "Biggus Dickus", itAttrib->second.toStdString() ); break;
            case 2: testCase( "Attribute 2 Name", "Cleese", itAttrib->first.toStdString() );
                testCase( "Attribute 2 Value", "Reg", itAttrib->second.toStdString() ); break;
            case 3: testCase( "Attribute 3 Name", "Palin", itAttrib->first.toStdString() );
                testCase( "Attribute 3 Value", "Pontius Pilate", itAttrib->second.toStdString() ); break;
            }
        }

        testCase( "Value of attribute \"Chapman\"", "Biggus Dickus", obAction.attribute( "Chapman" ).toStdString() );

        testCase( "Value of attribute \"Palin\"", "Pontius Pilate", obAction.attribute( "Palin" ).toStdString() );

        testCase( "Attribute Count Test", 3, inCounter );

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_uiFailedNum++;
    }
}

void cLogAnalyserTest::testLogAnalyser() throw()
{
    printNote( "LOG ANALYSER TESTS" );

    try
    {
        cLogAnalyser  *poLA                    = NULL;
        QString        qsDirPrefix             = "multiple_files/test1";
        QString        qsActionListFileName    = g_poPrefs->outputDir() + "/" + qsDirPrefix + "/actionlist.txt";
        QString        qsActionSummaryFileName = g_poPrefs->outputDir() + "/" + qsDirPrefix + "/actionsummary.txt";

        poLA = new cLogAnalyser( qsDirPrefix, "test*.log.gz", "nonexisting.xml", NULL );
        poLA->analyse();

        testCase( "Non-existing XML Action Definition, Pattern count", 0, poLA->patternCount() );

        testCase( "Non-existing XML Action Definition, Action count", 0, poLA->patternCount() );

        delete poLA;
        poLA = NULL;

        poLA = new cLogAnalyser( qsDirPrefix, "nonexisting.log", "test/test_actions.xml", NULL );
        poLA->analyse();

        testCase( "Non-existing Input Log File, Pattern count", 0, poLA->patternCount() );

        testCase( "Non-existing Input Log File, Action count", 0, poLA->patternCount() );

        delete poLA;
        poLA = NULL;

        poLA = new cLogAnalyser( qsDirPrefix, "test*.log.gz", "test/test_actions.xml", NULL );
        poLA->analyse();

        testCase( "Non-existing OutputCreator, Pattern count", 4, poLA->patternCount() );

        testCase( "Non-existing OutputCreator, Action count", 4, poLA->patternCount() );

        delete poLA;
        poLA = NULL;

        cOutputCreator  *poOC        = NULL;
        poOC = new cOutputCreator( qsDirPrefix );

        poLA = new cLogAnalyser( qsDirPrefix, "test*.log.gz", "test/test_actions.xml", poOC );

        QFile::remove( qsActionSummaryFileName );
        QFile::remove( qsActionListFileName );

        poLA->analyse();
        poOC->generateActionSummary();

        QStringList slSummaryContent;
        slSummaryContent << "nbGrenades OK: 2 FAILED: 0 TOTAL: 2";
        slSummaryContent << "nbManeuvers OK: 4 FAILED: 0 TOTAL: 4";

        checkFileContents( qsActionSummaryFileName.toStdString(), slSummaryContent );

        poOC->generateActionList();

        QStringList slListContent;
        QString qsListLine = "2010-04-09 13:50:01.000 HOLY_HAND_GRENADE OK type=\"combat\" ";
        qsListLine += g_poPrefs->tempDir();
        qsListLine += "/test2.log:5";
        slListContent << qsListLine;

        qsListLine = "2010-04-09 13:15:01.000 HOLY_HAND_GRENADE OK type=\"combat\" ";
        qsListLine += g_poPrefs->tempDir();
        qsListLine += "/test1.log:1";
        slListContent << qsListLine;

        qsListLine = "2010-04-09 13:50:00.000 NEW_TARGET OK subtype=\"targeting\" target=\"White Furry Rabbit\" type=\"intel\" ";
        qsListLine += g_poPrefs->tempDir();
        qsListLine += "/test2.log:4";
        slListContent << qsListLine;

        qsListLine = "2010-04-09 13:35:00.000 NEW_TARGET OK subtype=\"targeting\" target=\"White Furry Rabbit\" type=\"intel\" ";
        qsListLine += g_poPrefs->tempDir();
        qsListLine += "/test2.log:2";
        slListContent << qsListLine;

        checkFileContents( qsActionListFileName.toStdString(), slListContent );

        delete poLA;
        delete poOC;

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_uiFailedNum++;
    }
}
