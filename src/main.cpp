#include <QCoreApplication>
#include <QStringList>

#include <iostream>

#include <logger.h>
#include <consolewriter.h>
#include <filewriter.h>

#include "preferences.h"
#include "batchanalyser.h"


cLogger                 g_obLogger;
cPreferences           *g_poPrefs;

using namespace std;

class cParamError : public cSevException
{
public:
    cParamError() : cSevException( cSeverity::ERROR, "Parameter error." ) { }
    virtual ~cParamError() throw() { }
};

int main( int argc, char *argv[] )
{
    QCoreApplication  apMainApp( argc, argv );

    cConsoleWriter  obConsoleWriter;
    g_obLogger.registerWriter( &obConsoleWriter );

    cFileWriter obFileWriter( cSeverity::NONE, "log/lara.log", cFileWriter::BACKUP );
    g_obLogger.registerWriter( &obFileWriter );

    g_poPrefs  = new cPreferences( "lara", "0.3.1", &obConsoleWriter, &obFileWriter );

    g_obLogger << cSeverity::INFO
               << g_poPrefs->appName().toStdString() << " Version " << g_poPrefs->version().toStdString() << " started."
               << cLogMessage::EOM;

    int inRet = 0;
    try
    {
        if( argc == 1 ) throw cParamError();

        cBatchAnalyser  obAnalyser( QString::fromAscii( argv[1] ), "data/lara_batch.xsd" );
        obAnalyser.analyse();
    }
    catch( cParamError & )
    {
        cerr << "Usage: lara <batch definition file>" << endl;
        cerr << "          <batch definition file>: XML file containing the list of logs to analyse." << endl;
    }
    catch( cSevException &e )
    {
        g_obLogger << cSeverity::ERROR << "WHOA... Just caught an unhandled exception!" << cLogMessage::EOM;
        g_obLogger << e;

        inRet = 1;
    }

    g_obLogger << cSeverity::INFO
               << g_poPrefs->appName().toStdString() << " Version " << g_poPrefs->version().toStdString() << " ended."
               << cLogMessage::EOM;

    delete g_poPrefs;

    return inRet;
}
