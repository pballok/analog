#ifndef UNITTEST_H
#define UNITTEST_H

#include <string>

class cUnitTest
{
public:
    cUnitTest( const std::string p_stTestName = "" ) throw();
    virtual ~cUnitTest() throw();

    virtual void run() throw() = 0;
    void testCase( const std::string p_stText, const bool p_boExpected, const bool p_boObserved ) throw();
    void testCase( const std::string p_stText, const int p_inExpected, const int p_inObserved ) throw();
    void testCase( const std::string p_stText, const std::string p_stExpected, const std::string p_stObserved ) throw();

    void printNote( const std::string p_stText ) throw();

protected:
    std::string   m_stName;
    bool          m_boResult;
    unsigned int  m_uiTestCaseNum;

    void testCaseResult( const bool p_boPassed );
};

#endif
