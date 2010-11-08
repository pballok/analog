#include <QDomDocument>
#include <QDomElement>

#include "action.h"
#include "actiondefsingleliner.h"
#include "actiondeflist.h"
#include "actiontest.h"

cActionTest::cActionTest() throw() : cUnitTest( "Action" )
{
}

cActionTest::~cActionTest() throw()
{
}

void cActionTest::run() throw()
{
    testAction();
    testSingleLinerDef();
    testCountActions();
    testPatterns();
    testActionDefList();
}

void cActionTest::testAction() throw()
{
    cAction  obAction( "ActionTest", "ActionTimeStamp", 42, 3, cActionResult::OK, cActionUpload::NEVER );

    testCase( "Name Test", "ActionTest", obAction.name().toStdString() );

    testCase( "TimeStamp Test", "ActionTimeStamp", obAction.timeStamp().toStdString() );

    testCase( "FileId Test", 42, obAction.fileId() );

    testCase( "LineNum Test", 3, obAction.lineNum() );

    testCase( "Result Test", cActionResult::OK, obAction.result() );

    testCase( "Upload Test", cActionUpload::NEVER, obAction.upload() );

    bool boCapturedEmpty = (obAction.capturedTextsBegin() == obAction.capturedTextsEnd() );
    testCase( "CapturedText Container must be empty", true, boCapturedEmpty );

    obAction.addCapturedText( QString::fromStdString( "Palin" ), QString::fromStdString( "Pontius Pilate" ) );
    obAction.addCapturedText( QString::fromStdString( "Chapman" ), QString::fromStdString( "Biggus Dickus" ) );
    obAction.addCapturedText( QString::fromStdString(  "Cleese" ), QString::fromStdString( "Reg" ) );
    int inCounter = 0;
    for( tiActionCapturedTexts itCapturedText = obAction.capturedTextsBegin();
         itCapturedText != obAction.capturedTextsEnd();
         itCapturedText++ )
    {
        switch( ++inCounter )
        {
            /* The captured texts are stored in a multimap that orders the stored value
               alphabetically based on the key. That is why the extracted order is not the
               same as the order in which they were added to the container */
            case 1: testCase( "Captured Text 2 Name", "Chapman", itCapturedText->first.toStdString() );
                    testCase( "Captured Text 2 Value", "Biggus Dickus", itCapturedText->second.toStdString() ); break;
            case 2: testCase( "Captured Text 3 Name", "Cleese", itCapturedText->first.toStdString() );
                    testCase( "Captured Text 3 Value", "Reg", itCapturedText->second.toStdString() ); break;
            case 3: testCase( "Captured Text 1 Name", "Palin", itCapturedText->first.toStdString() );
                    testCase( "Captured Text 1 Value", "Pontius Pilate", itCapturedText->second.toStdString() ); break;
        }
    }

    testCase( "Captured Text Count Test", 3, inCounter );
}

void cActionTest::testSingleLinerDef() throw()
{
    cActionDefSingleLiner *poSingleLiner;

    poSingleLiner = new cActionDefSingleLiner;

    testCase( "SingleLiner empty constructor Name", "", poSingleLiner->name().toStdString() );

    testCase( "SingleLiner empty constructor Upload", cActionUpload::MIN, poSingleLiner->upload() );

    testCase( "SingleLiner empty constructor Pattern", "", poSingleLiner->pattern().toStdString() );

    testCase( "SingleLiner empty constructor Result", cActionResult::MIN, poSingleLiner->result() );

    delete poSingleLiner;
    poSingleLiner = new cActionDefSingleLiner( NULL );

    testCase( "SingleLiner NULL Dom Element Name", "", poSingleLiner->name().toStdString() );

    testCase( "SingleLiner NULL Dom Element Upload", cActionUpload::MIN, poSingleLiner->upload() );

    testCase( "SingleLiner NULL Dom Element Pattern", "", poSingleLiner->pattern().toStdString() );

    testCase( "SingleLiner NULL Dom Element Result", cActionResult::MIN, poSingleLiner->result() );

    delete poSingleLiner;
    QDomDocument obDomDoc( "ActionTest" );
    QDomElement obDomElem = obDomDoc.createElement( "single_liner" );
    obDomElem.setAttribute( "name", "TestSingleLiner" );
    obDomElem.setAttribute( "pattern", "Test Pattern" );
    obDomElem.setAttribute( "result", "OK" );
    obDomElem.setAttribute( "upload", "ALWAYS" );

    poSingleLiner = new cActionDefSingleLiner( &obDomElem );

    testCase( "SingleLiner Correct Dom Element Name", "TestSingleLiner", poSingleLiner->name().toStdString() );

    testCase( "SingleLiner Correct Dom Element Upload", cActionUpload::ALWAYS, poSingleLiner->upload() );

    testCase( "SingleLiner Correct Dom Element Pattern", "Test Pattern", poSingleLiner->pattern().toStdString() );

    testCase( "SingleLiner Correct Dom Element Result", cActionResult::OK, poSingleLiner->result() );

    delete poSingleLiner;
    obDomElem.removeAttribute( "pattern" );
    poSingleLiner = new cActionDefSingleLiner( &obDomElem );

    testCase( "SingleLiner Missing Attribute Name", "TestSingleLiner", poSingleLiner->name().toStdString() );

    testCase( "SingleLiner Missing Attribute Pattern", "", poSingleLiner->pattern().toStdString() );

    delete poSingleLiner;
}

void cActionTest::testCountActions() throw()
{
}

void cActionTest::testPatterns() throw()
{
}

void cActionTest::testActionDefList() throw()
{
    cActionDefList obActionDefList( "test_actions.xml", "../data/lara.xsd" );

    unsigned int uiPatternCount = 0;
    for( cActionDefList::tiPatternList itPattern = obActionDefList.patternBegin();
         itPattern != obActionDefList.patternEnd();
         itPattern++ )
    {
        switch( ++uiPatternCount )
        {
            case 1: testCase( "ActionDefList Pattern 1 Name", "PAT_HOLY_HAND_GRENADE", itPattern->name().toStdString() );
                    testCase( "ActionDefList Pattern 1 Regexp", "Throwing the Holy Hand Grenade", itPattern->pattern().toStdString() );
                    break;
            case 2: testCase( "ActionDefList Pattern 2 Name", "PAT_TARGET_SPOTTED", itPattern->name().toStdString() );
                    testCase( "ActionDefList Pattern 2 Regexp", "Spotted a (.*)$", itPattern->pattern().toStdString() );
                    break;
        }
    }

    testCase( "ActionDefList Pattern count", 2, uiPatternCount );

    unsigned int uiSingleLinerCount = 0;
    for( cActionDefList::tiSingleLinerList itSingleLiner = obActionDefList.singleLinerBegin();
         itSingleLiner != obActionDefList.singleLinerEnd();
         itSingleLiner++ )
    {
        switch( ++uiSingleLinerCount )
        {
            case 1: testCase( "ActionDefList SingleLiner 1 Name", "HOLY_HAND_GRENADE", itSingleLiner->name().toStdString() );
                    testCase( "ActionDefList SingleLiner 1 Pattern", "PAT_HOLY_HAND_GRENADE", itSingleLiner->pattern().toStdString() );
                    testCase( "ActionDefList SingleLiner 1 Result", cActionResult::OK, itSingleLiner->result() );
                    testCase( "ActionDefList SingleLiner 1 Upload", cActionUpload::NEVER, itSingleLiner->upload() );
                    break;
            case 2: testCase( "ActionDefList SingleLiner 2 Name", "NEW_TARGET", itSingleLiner->name().toStdString() );
                    testCase( "ActionDefList SingleLiner 2 Pattern", "PAT_TARGET_SPOTTED", itSingleLiner->pattern().toStdString() );
                    testCase( "ActionDefList SingleLiner 2 Result", cActionResult::OK, itSingleLiner->result() );
                    testCase( "ActionDefList SingleLiner 2 Upload", cActionUpload::NEVER, itSingleLiner->upload() );
                    break;
        }
    }

    testCase( "ActionDefList SingleLiner count", 2, uiSingleLinerCount );

    unsigned int uiCountActionCount = 0;
    for( cActionDefList::tiCountActionList itCountAction = obActionDefList.countActionBegin();
         itCountAction != obActionDefList.countActionEnd();
         itCountAction++ )
    {
        switch( ++uiCountActionCount )
        {
            case 1: testCase( "ActionDefList Count Action 1 Name", "nbTargets", itCountAction->name().toStdString() );
                    break;
        }
    }

    testCase( "ActionDefList Count Action count", 1, uiCountActionCount );

    testCase( "ActionDefList Timestamp Regexp", "(\\d*)-(\\d*)-(\\d*) (\\d*):(\\d*):(\\d*)\\.(\\d*)", obActionDefList.timeStampRegExp().pattern().toStdString() );

    testCase( "ActionDefList Valid TimestampPart", cTimeStampPart::DAY, obActionDefList.timeStampPart( 2 ) );

    testCase( "ActionDefList Invalid Timestamp Part", cTimeStampPart::MIN, obActionDefList.timeStampPart( 42 ) );

    cActionDefList obBadActionDefList( "bad_actions.xml", "../data/lara.xsd" );

    testCase( "Bad ActionDefList Timestamp Regexp", "", obBadActionDefList.timeStampRegExp().pattern().toStdString() );
}
