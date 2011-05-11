#ifndef OUTPUTCREATORTEST_H
#define OUTPUTCREATORTEST_H

#include "unittest.h"

#include "outputcreator.h"

class cOutputCreatorTest : public cUnitTest
{
public:
    cOutputCreatorTest()              throw();
    virtual ~cOutputCreatorTest()     throw();

    virtual void run()                throw();

private:
    cOutputCreator *m_poOC;

    void         testTextFileResults()  throw();
    void         testDatabaseResults()  throw();
    void         testCombilogResults()  throw();
};

#endif // OUTPUTCREATORTEST_H
