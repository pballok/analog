#include <logger.h>

#include "batchanalyser.h"

#include "batchanalysertest.h"

extern cLogger g_obLogger;

cBatchAnalyserTest::cBatchAnalyserTest() throw() : cUnitTest( "Batch Analyser" )
{
}

cBatchAnalyserTest::~cBatchAnalyserTest() throw()
{
}

void cBatchAnalyserTest::run() throw()
{
    testBatchAnalyser();
}

void cBatchAnalyserTest::testBatchAnalyser() throw()
{
    printNote( "BATCH ANALYSER TESTS" );

    try
    {
        cBatchAnalyser  obBatchAnalyser( "test/testbatch.xml", "data/lara_batch.xsd" );

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_boResult = false;
    }
}
