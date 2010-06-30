#include "qtlogger.h"
#include "preferences.h"
#include "loganalyzer.h"

#include <QCoreApplication>
#include <QStringList>

#include <iostream>

cQTLogger             g_obLogger;
cPreferences         *g_poPrefs;

void printUsage()
{
    cerr << "Usage: laza -h -p <dir prefix> -f <input files> -a <actions file>" << endl;
    cerr << "          -h: Displays this helps message then exits." << endl;
    cerr << "          -p: directory prefix that is used to construct the full path to the input files" << endl;
    cerr << "          -f: input file names" << endl;
    cerr << "          -a: name of the XML file describing the actions" << endl;
}

int main( int argc, char *argv[] )
{
    QCoreApplication  apMainApp( argc, argv );

    g_poPrefs  = new cPreferences( QString::fromAscii( "laza" ) );
    g_poPrefs->setVersion( "0.0.1" );

    int inRet = 0;
    try
    {
        g_obLogger << cSeverity::INFO;
        g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " started.";
        g_obLogger << cQTLogger::EOM;

        string stDirPrefix = "";
        string stLogFiles  = "";
        string stActions   = "";

        int inIdx = 0;
        QStringList obArgs = QCoreApplication::arguments();

        inIdx = obArgs.indexOf( "-p" );
        if( inIdx != -1 && inIdx < obArgs.size() - 1 ) stDirPrefix = obArgs.at( inIdx + 1 ).toStdString();

        inIdx = obArgs.indexOf( "-f" );
        if( inIdx != -1 && inIdx < obArgs.size() - 1 ) stLogFiles = obArgs.at( inIdx + 1 ).toStdString();

        inIdx = obArgs.indexOf( "-a" );
        if( inIdx != -1 && inIdx < obArgs.size() - 1 ) stActions = obArgs.at( inIdx + 1 ).toStdString();

        if( obArgs.indexOf( "-h" ) != -1 || stDirPrefix == "" || stLogFiles == "" || stActions == "" ) printUsage();

        cLogAnalyzer  obAnalyzer( stDirPrefix, stLogFiles, stActions );

        g_obLogger << cSeverity::INFO;
        g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " ended.";
        g_obLogger << cQTLogger::EOM;
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity();
        g_obLogger << e.what();
        g_obLogger << cQTLogger::EOM;

        inRet = 1;
    }

    delete g_poPrefs;

    return inRet;
}
