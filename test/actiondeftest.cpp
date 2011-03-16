#include <QDomDocument>
#include <QDomElement>

#include <logger.h>

#include "actiondefsingleliner.h"
#include "countaction.h"
#include "pattern.h"
#include "actiondeflist.h"

#include "actiondeftest.h"

extern cLogger g_obLogger;

cActionDefTest::cActionDefTest() throw() : cUnitTest( "Action Definition" )
{
}

cActionDefTest::~cActionDefTest() throw()
{
}

void cActionDefTest::run() throw()
{
    testSingleLinerDef();
    testCountActions();
    testPatterns();
    testActionDefList();
}

void cActionDefTest::testSingleLinerDef() throw()
{
    printNote( "SINGLE LINER TESTS" );

    try
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

        testCase( "SingleLiner Correct DOM Element Name", "TestSingleLiner", poSingleLiner->name().toStdString() );

        testCase( "SingleLiner Correct DOM Element Upload", cActionUpload::ALWAYS, poSingleLiner->upload() );

        testCase( "SingleLiner Correct DOM Element Pattern", "Test Pattern", poSingleLiner->pattern().toStdString() );

        testCase( "SingleLiner Correct DOM Element Result", cActionResult::OK, poSingleLiner->result() );

        delete poSingleLiner;

        obDomElem.removeAttribute( "pattern" );
        poSingleLiner = new cActionDefSingleLiner( &obDomElem );

        testCase( "SingleLiner Missing Attribute Name", "TestSingleLiner", poSingleLiner->name().toStdString() );

        testCase( "SingleLiner Missing Attribute Pattern", "", poSingleLiner->pattern().toStdString() );

        delete poSingleLiner;

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_boResult = false;
    }
}

void cActionDefTest::testCountActions() throw()
{
    printNote( "COUNT ACTION TESTS" );

    try
    {
        cCountAction *poCountAction;

        poCountAction = new cCountAction;

        testCase( "CountAction empty constructor Name", "", poCountAction->name().toStdString() );

        testCase( "CountAction empty constructor Action Container empty", true, poCountAction->actionsToCountBegin() == poCountAction->actionsToCountEnd() );

        delete poCountAction;

        poCountAction = new cCountAction( NULL );

        testCase( "CountAction NULL DOM Element Name", "", poCountAction->name().toStdString() );

        testCase( "CountAction NULL DOM Element Action Container empty", true, poCountAction->actionsToCountBegin() == poCountAction->actionsToCountEnd() );

        delete poCountAction;

        QDomDocument obDomDoc( "ActionTest" );
        QDomElement obDomElem = obDomDoc.createElement( "count_action" );
        obDomElem.setAttribute( "name", "CountSpam" );
        QDomElement obAction1 = obDomDoc.createElement( "action" );
        obAction1.setAttribute( "name", "SPAM" );
        QDomElement obAction2 = obDomDoc.createElement( "action" );
        obAction2.setAttribute( "name", "SPAM_A_LOT" );
        obAction2.setAttribute( "attrib", "PIECES_OF_SPAM" );
        QDomElement obAction3 = obDomDoc.createElement( "action" );
        obAction3.setAttribute( "name", "SPAM_A_LOT_SPAM" );
        obDomElem.appendChild( obAction1 );
        obDomElem.appendChild( obAction2 );
        obDomElem.appendChild( obAction3 );
        poCountAction = new cCountAction( &obDomElem );

        testCase( "CountAction Correct DOM Element Name", "CountSpam", poCountAction->name().toStdString() );

        unsigned int uiActionCount = 0;
        for( cCountAction::tiActionsToCount itAction = poCountAction->actionsToCountBegin();
            itAction != poCountAction->actionsToCountEnd();
            itAction++ )
        {
            switch( ++uiActionCount )
            {
            case 1: testCase( "CountAction Correct DOM Element Action 1 Name", "SPAM", itAction->qsName.toStdString() ); break;
            case 2: testCase( "CountAction Correct DOM Element Action 2 Name", "SPAM_A_LOT", itAction->qsName.toStdString() );
                    testCase( "CountAction Correct DOM Element Action 2 Attrib", "PIECES_OF_SPAM", itAction->qsAttrib.toStdString() ); break;
            case 3: testCase( "CountAction Correct DOM Element Action 3 Name", "SPAM_A_LOT_SPAM", itAction->qsName.toStdString() ); break;
            }
        }

        testCase( "CountAction Correct DOM Element Action count", 3, uiActionCount );

        delete poCountAction;

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_boResult = false;
    }
}

void cActionDefTest::testPatterns() throw()
{
    printNote( "PATTERN TESTS" );

    try
    {
        cPattern  *poPattern;
        poPattern = new cPattern();

        testCase( "Pattern empty constructor Name", "", poPattern->name().toStdString() );

        testCase( "Pattern empty constructor Pattern", "", poPattern->pattern().toStdString() );

        testCase( "Pattern empty constructor Captures List empty", true, poPattern->captures().empty() );

        delete poPattern;

        poPattern = new cPattern( NULL );

        testCase( "Pattern NULL DOM Element Name", "", poPattern->name().toStdString() );

        testCase( "Pattern NULL DOM Element Pattern", "", poPattern->pattern().toStdString() );

        testCase( "Pattern NULL DOM Element Captures List empty", true, poPattern->captures().empty() );

        delete poPattern;

        QDomDocument obDomDoc( "ActionTest" );
        QDomElement obDomElem = obDomDoc.createElement( "pattern" );
        obDomElem.setAttribute( "name", "GRENADE_INSTRUCTIONS" );
        obDomElem.setAttribute( "regexp", "([\\d]*)[\\D]*([\\d]*)[\\D]*([\\d]*)" );
        QDomElement obCap1 = obDomDoc.createElement( "captured_attrib" );
        obCap1.setAttribute( "name", "NOT_COUNT" );
        QDomElement obCap2 = obDomDoc.createElement( "captured_attrib" );
        obCap2.setAttribute( "name", "NEITHER_COUNT" );
        QDomElement obCap3 = obDomDoc.createElement( "captured_attrib" );
        obCap3.setAttribute( "name", "EXCEPT_COUNT" );
        obDomElem.appendChild( obCap1 );
        obDomElem.appendChild( obCap2 );
        obDomElem.appendChild( obCap3 );

        poPattern = new cPattern( &obDomElem );

        testCase( "Pattern Correct DOM Element Name", "GRENADE_INSTRUCTIONS", poPattern->name().toStdString() );

        testCase( "Pattern Correct DOM Element Pattern", "([\\d]*)[\\D]*([\\d]*)[\\D]*([\\d]*)", poPattern->pattern().toStdString() );

        testCase( "Pattern Correct DOM Element Captures List size", 3, poPattern->captures().size() );

        QStringList slNumbers = poPattern->capturedTexts( "4 shalt thou not count, neither count thou 2, excepting that thou then proceed to 3." );

        testCase( "Pattern Correct DOM Element Captured Text List size", 4, slNumbers.size() );

        testCase( "Pattern Correct DOM Element Captured Attrib 1 Name", "NOT_COUNT", poPattern->captures().at( 0 ).toStdString() );

        testCase( "Pattern Correct DOM Element Captured Attrib 1 Text", "4", slNumbers.at( 1 ).toStdString() );

        testCase( "Pattern Correct DOM Element Captured Attrib 2 Name", "NEITHER_COUNT", poPattern->captures().at( 1 ).toStdString() );

        testCase( "Pattern Correct DOM Element Captured Attrib 2 Text", "2", slNumbers.at( 2 ).toStdString() );

        testCase( "Pattern Correct DOM Element Captured Attrib 3 Name", "EXCEPT_COUNT", poPattern->captures().at( 2 ).toStdString() );

        testCase( "Pattern Correct DOM Element Captured Attrib 3 Text", "3", slNumbers.at( 3 ).toStdString() );

        delete poPattern;

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_boResult = false;
    }
}

void cActionDefTest::testActionDefList() throw()
{
    printNote( "ACTION DEFINITION LIST TESTS" );

    try
    {
        cActionDefList obActionDefList( "test/test_actions.xml", "data/lara_actions.xsd" );

        unsigned int uiPatternCount = 0;
        for( cActionDefList::tiPatternList itPattern = obActionDefList.patternBegin();
            itPattern != obActionDefList.patternEnd();
            itPattern++ )
        {
            switch( ++uiPatternCount )
            {
                case 1: testCase( "ActionDefList Pattern 1 Name", "PAT_HUNT_NAME", itPattern->name().toStdString() );
                        break;
                case 2: testCase( "ActionDefList Pattern 2 Name", "PAT_HOLY_HAND_GRENADE", itPattern->name().toStdString() );
                        break;
                case 3: testCase( "ActionDefList Pattern 3 Name", "PAT_WASTED_GRENADE", itPattern->name().toStdString() );
                        break;
                case 4: testCase( "ActionDefList Pattern 4 Name", "PAT_TARGET_SPOTTED", itPattern->name().toStdString() );
                        break;
            }
        }

        testCase( "ActionDefList Pattern count", 4, uiPatternCount );

        unsigned int uiSingleLinerCount = 0;
        for( cActionDefList::tiSingleLinerList itSingleLiner = obActionDefList.singleLinerBegin();
            itSingleLiner != obActionDefList.singleLinerEnd();
            itSingleLiner++ )
        {
            switch( ++uiSingleLinerCount )
            {
                case 1: testCase( "ActionDefList SingleLiner 1 Name", "HOLY_HAND_GRENADE", itSingleLiner->name().toStdString() );
                        break;
                case 2: testCase( "ActionDefList SingleLiner 2 Name", "WASTED_GRENADE", itSingleLiner->name().toStdString() );
                        break;
                case 3: testCase( "ActionDefList SingleLiner 3 Name", "NEW_TARGET", itSingleLiner->name().toStdString() );
                        break;
            }
        }

        testCase( "ActionDefList SingleLiner count", 3, uiSingleLinerCount );

        unsigned int uiCountActionCount = 0;
        for( cActionDefList::tiCountActionList itCountAction = obActionDefList.countActionBegin();
            itCountAction != obActionDefList.countActionEnd();
            itCountAction++ )
        {
            switch( ++uiCountActionCount )
            {
                case 1: testCase( "ActionDefList CountAction 1 Name", "nbManeuvers", itCountAction->name().toStdString() );
                        break;
                case 2: testCase( "ActionDefList CountAction 2 Name", "nbGrenades", itCountAction->name().toStdString() );
                        break;
            }
        }

        testCase( "ActionDefList Count Action count", 2, uiCountActionCount );

        testCase( "ActionDefList Timestamp Regexp", "(\\d*)-(\\d*)-(\\d*) (\\d*):(\\d*):(\\d*)\\.(\\d*)", obActionDefList.timeStampRegExp().pattern().toStdString() );

        testCase( "ActionDefList Valid TimestampPart", cTimeStampPart::DAY, obActionDefList.timeStampPart( 2 ) );

        testCase( "ActionDefList Invalid Timestamp Part", cTimeStampPart::MIN, obActionDefList.timeStampPart( 42 ) );

        cActionDefList obBadActionDefList( "test/bad_actions.xml", "data/lara_actions.xsd" );

        testCase( "Bad ActionDefList Timestamp Regexp (XML validation ERROR above is EXPECTED)", "", obBadActionDefList.timeStampRegExp().pattern().toStdString() );

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_boResult = false;
    }
}
