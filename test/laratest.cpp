#include <QCoreApplication>
#include <QStringList>

#include <logger.h>
#include <consolewriter.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "actiondeftest.h"
#include "batchanalysertest.h"
#include "loganalysertest.h"

using namespace std;

cLogger  g_obLogger;

int main( int argc, char *argv[] )
{
    QCoreApplication  apMainApp( argc, argv );

    cConsoleWriter  obConsoleWriter;
    obConsoleWriter.setMinSeverity( cSeverity::WARNING );
    g_obLogger.registerWriter( &obConsoleWriter );

    cout << "This is L.A.R.A. Unit Test Run." << endl;
    time_t  ttTime = time( NULL );
    cout << "Time: " << asctime( localtime( &ttTime ) ) << endl;

    QStringList slAllTests;
    slAllTests << "actiondef" << "batchanalyser" << "loganalyser";

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

    for( int inTest = 0; inTest < slTestsToRun.size(); inTest++ )
    {
        if( slTestsToRun[inTest] == "actiondef" )
        {
            cActionDefTest obTest;
            obTest.run();
            continue;
        }

        if( slTestsToRun[inTest] == "batchanalyser" )
        {
            cBatchAnalyserTest obTest;
            obTest.run();
            continue;
        }

        if( slTestsToRun[inTest] == "loganalyser" )
        {
            cLogAnalyserTest obTest;
            obTest.run();
            continue;
        }

        cout << "Invalid test name: " << slTestsToRun[inTest].toStdString() << endl;
        cout << "    Test name can be one of: " << slAllTests.join( ", " ).toStdString() << endl << endl;
    }

    return 0;
}
