#ifndef BATCHANALYSERTEST_H
#define BATCHANALYSERTEST_H

#include "unittest.h"

class cBatchAnalyserTest : public cUnitTest
{
public:
    cBatchAnalyserTest()              throw();
    virtual ~cBatchAnalyserTest()     throw();

    virtual void run()                throw();

private:
};

#endif // BATCHANALYSERTEST_H
