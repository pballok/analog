#include <iostream>
#include <iomanip>

#include "unittest.h"

using namespace std;

cUnitTest::cUnitTest( const std::string p_stTestName ) throw()
{
    m_stName        = p_stTestName;
    m_boResult      = true;
    m_uiTestCaseNum = 0;

    cout << "Starting Unit Test \"" << m_stName << "\"" << endl;
}

cUnitTest::~cUnitTest() throw()
{
    cout << "Unit Test \"" << m_stName << "\"";
    if( m_boResult ) cout << " PASSED" << endl;
    else cout << " FAILED" << endl;
    cout << endl;
}

void cUnitTest::testCase( const string p_stText, const bool p_boExpected, const bool p_boObserved ) throw()
{
    cout << "Test Case " << ++m_uiTestCaseNum << ": " << p_stText << " -- ";
    cout << "expected: " << (p_boExpected ? "TRUE" : "FALSE" ) << " observed: " << (p_boObserved ? "TRUE" : "FALSE" );
    testCaseResult( p_boExpected == p_boObserved );
}

void cUnitTest::testCase( const string p_stText, const int p_inExpected, const int p_inObserved ) throw()
{
    cout << "Test Case " << ++m_uiTestCaseNum << ": " << p_stText << " -- ";
    cout << "expected: " << p_inExpected << " observed: " << p_inObserved;
    testCaseResult( p_inExpected == p_inObserved );
}

void cUnitTest::testCase( const string p_stText, const string p_stExpected, const string p_stObserved ) throw()
{
    cout << "Test Case " << ++m_uiTestCaseNum << ": " << p_stText << " -- ";
    cout << "expected: \"" << p_stExpected << "\" observed: \"" << p_stObserved << "\"";
    testCaseResult( p_stExpected == p_stObserved );
}

void cUnitTest::testCaseResult( const bool p_boPassed )
{
    if( p_boPassed ) cout << " -- PASSED" << endl;
    else
    {
        cout << " -- FAILED" << endl;
        m_boResult = false;
    }
}
