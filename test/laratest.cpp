#include <QCoreApplication>
#include <QStringList>
#include <QDateTime>

#include <logger.h>
#include <consolewriter.h>
#include <filewriter.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "preferences.h"

#include "actiondeftest.h"
#include "datasourcetest.h"
#include "outputcreatortest.h"
#include "loganalysertest.h"
//#include "batchanalysertest.h"

using namespace std;

cLogger          g_obLogger;
cPreferences    *g_poPrefs;

int main( int argc, char *argv[] )
{
    QCoreApplication  apMainApp( argc, argv );

    cConsoleWriter  obConsoleWriter;
    g_obLogger.registerWriter( &obConsoleWriter );

    cFileWriter obFileWriter( cSeverity::NONE, "log/laratest.log", cFileWriter::BACKUP );
    g_obLogger.registerWriter( &obFileWriter );

    g_poPrefs  = new cPreferences( "laratest", "1.0", &obConsoleWriter, &obFileWriter );

    cout << "This is L.A.R.A. Unit Test Run." << endl;
    cout << "Time: " << QDateTime::currentDateTime().toString( "yyyy-MMM-dd hh:mm:ss" ).toStdString() << endl;

    QStringList slAllTests;
    slAllTests << "actiondef"<< "datasource" << "outputcreator" << "loganalyser" << "batchanalyser" ;

    /* Determine list of Tests to run */
    QStringList slTestsToRun;
    if( argc == 1 )
    {
        slTestsToRun << slAllTests;
    }
    else
    {
        slTestsToRun << QCoreApplication::arguments();
        slTestsToRun.removeFirst();
    }
    cout << "Running Tests: " << slTestsToRun.join( ", " ).toStdString() << endl << endl;

    /* Run the Tests */
    unsigned int poTotalTestCases[slTestsToRun.size()];
    unsigned int poFailedTestCases[slTestsToRun.size()];
    for( int inTest = 0; inTest < slTestsToRun.size(); inTest++ )
    {
        cUnitTest *poTest = NULL;

        if( slTestsToRun[inTest] == "actiondef" )          poTest = new cActionDefTest;
        else if( slTestsToRun[inTest] == "datasource" )    poTest = new cDataSourceTest;
        else if( slTestsToRun[inTest] == "outputcreator" ) poTest = new cOutputCreatorTest;
        else if( slTestsToRun[inTest] == "loganalyser" )   poTest = new cLogAnalyserTest;
        else
        {
            cout << "Invalid test name: " << slTestsToRun[inTest].toStdString() << endl;
            cout << "    Test name can be one of: " << slAllTests.join( ", " ).toStdString() << endl << endl;
        }

        if( poTest )
        {
            poTest->run();

            poTotalTestCases[inTest] = poTest->totalTestCaseNum();
            poFailedTestCases[inTest] = poTest->failedTestCaseNum();

            delete poTest;
            poTest = NULL;
        }
        else
        {
            poTotalTestCases[inTest] = 1;
            poFailedTestCases[inTest] = 1;
        }
    }

    /* Print result summary */
    cout << "***** Unit Test Summary" << endl;
    unsigned int uiSummaryTotal  = 0;
    unsigned int uiSummaryFailed = 0;
    for( int inTest = 0; inTest < slTestsToRun.size(); inTest++ )
    {
        cout << slTestsToRun[inTest].toStdString() << ": ";
        if( poFailedTestCases[inTest] )
            cout << " FAILED (" << poFailedTestCases[inTest] << " out of " << poTotalTestCases[inTest] << " Test Cases FAILED)" << endl;
        else
            cout << " PASSED (All " << poTotalTestCases[inTest] << " Test Cases PASSED)" << endl;
        uiSummaryTotal += poTotalTestCases[inTest];
        uiSummaryFailed += poFailedTestCases[inTest];
    }
    cout << "-----------------------------------------" << endl;
    cout << "Overall Result: ";
    if( uiSummaryFailed )
        cout << " FAILED (" << uiSummaryFailed << " out of " << uiSummaryTotal << " Test Cases FAILED)" << endl;
    else
        cout << " PASSED (All " << uiSummaryTotal << " Test Cases PASSED)" << endl;

    cout << endl;

    delete g_poPrefs;

    return 0;
}
