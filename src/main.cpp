#include "qtlogger.h"
#include "preferences.h"
#include "loganalyzer.h"

#include <QCoreApplication>
#include <QStringList>

#include <iostream>

cQTLogger                 g_obLogger;
cPreferences             *g_poPrefs;

extern const unsigned long long  g_ulMSecPerYear   = 32140800000;
extern const unsigned long long  g_ulMSecPerMonth  = 2678400000;
extern const unsigned long long  g_ulMSecPerDay    = 86400000;
extern const unsigned long long  g_ulMSecPerHour   = 3600000;
extern const unsigned long long  g_ulMSecPerMinute = 60000;
extern const unsigned long long  g_ulMSecPerSec    = 1000;

class cParamError : public cSevException
{
public:
    cParamError() : cSevException( cSeverity::ERROR, "Parameter error." ) { }
    virtual ~cParamError() throw() { }
};

int main( int argc, char *argv[] )
{
    QCoreApplication  apMainApp( argc, argv );

    g_poPrefs  = new cPreferences( QString::fromAscii( "laza" ) );
    g_poPrefs->setVersion( "0.0.1" );

    g_obLogger << cSeverity::INFO;
    g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " started.";
    g_obLogger << cQTLogger::EOM;

    int inRet = 0;
    try
    {
        QString qsDirPrefix = "";
        QString qsLogFiles  = "";
        QString qsActions   = "";

        int inIdx = 0;
        QStringList obArgs = QCoreApplication::arguments();

        inIdx = obArgs.indexOf( "-p" );
        if( inIdx != -1 && inIdx < obArgs.size() - 1 ) qsDirPrefix = obArgs.at( inIdx + 1 );

        inIdx = obArgs.indexOf( "-f" );
        if( inIdx != -1 && inIdx < obArgs.size() - 1 ) qsLogFiles = obArgs.at( inIdx + 1 );

        inIdx = obArgs.indexOf( "-a" );
        if( inIdx != -1 && inIdx < obArgs.size() - 1 ) qsActions = obArgs.at( inIdx + 1 );

        if( obArgs.indexOf( "-h" ) != -1 || qsDirPrefix == "" || qsLogFiles == "" || qsActions == "" ) throw cParamError();

        cLogAnalyzer  obAnalyzer( qsDirPrefix, qsLogFiles, qsActions );
        obAnalyzer.analyze();
    }
    catch( cParamError &e )
    {
        cerr << "Usage: laza -h -p <dir prefix> -f <input files> -a <actions file>" << endl;
        cerr << "          -h: Displays this helps message then exits." << endl;
        cerr << "          -p: directory prefix that is used to construct the full path to the input files" << endl;
        cerr << "          -f: input file names" << endl;
        cerr << "          -a: name of the XML file describing the actions" << endl;
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity();
        g_obLogger << e.what();
        g_obLogger << cQTLogger::EOM;

        cerr << "FATAL ERROR: " << e.what() << endl;

        inRet = 1;
    }

    g_obLogger << cSeverity::INFO;
    g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " ended.";
    g_obLogger << cQTLogger::EOM;

    delete g_poPrefs;

    return inRet;
}
