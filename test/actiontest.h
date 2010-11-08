#ifndef ACTIONTEST_H
#define ACTIONTEST_H

#include "unittest.h"

class cActionTest : public cUnitTest
{
public:
    cActionTest()                     throw();
    virtual ~cActionTest()            throw();

    virtual void run()                throw();

private:
    void         testAction()         throw();
    void         testSingleLinerDef() throw();
    void         testCountActions()   throw();
    void         testPatterns()       throw();
    void         testActionDefList()  throw();
};

#endif // ACTIONTEST_H
