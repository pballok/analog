#ifndef ACTIONDEFTEST_H
#define ACTIONDEFTEST_H

#include "unittest.h"

class cActionDefTest : public cUnitTest
{
public:
    cActionDefTest()                  throw();
    virtual ~cActionDefTest()         throw();

    virtual void run()                throw();

private:
    void         testSingleLinerDef() throw();
    void         testCountActions()   throw();
    void         testPatterns()       throw();
    void         testActionDefList()  throw();
};

#endif // ACTIONDEFTEST_H
