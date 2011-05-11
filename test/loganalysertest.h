#ifndef LOGANALYSERTEST_H
#define LOGANALYSERTEST_H

#include "unittest.h"

class cLogAnalyserTest : public cUnitTest
{
public:
    cLogAnalyserTest()                throw();
    virtual ~cLogAnalyserTest()       throw();

    virtual void run()                throw();

private:
    void         testAction()         throw();
    void         testLogAnalyser()    throw();
};

#endif // LOGANALYSERTEST_H
