#include <logger.h>

#include "action.h"

#include "loganalysertest.h"

extern cLogger g_obLogger;

cLogAnalyserTest::cLogAnalyserTest() throw() : cUnitTest( "Log Analyser" )
{
}

cLogAnalyserTest::~cLogAnalyserTest() throw()
{
}

void cLogAnalyserTest::run() throw()
{
    testAction();
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
        m_boResult = false;
    }
}

