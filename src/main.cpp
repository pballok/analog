#include "qtlogger.h"
#include "qtmysqlconnection.h"
#include "preferences.h"
#include "wndmain.h"

#include <QApplication>
#include <QString>
#include <iostream>

cQTLogger             g_obLogger;
cQTMySQLConnection   *g_poDB;
cPreferences         *g_poPrefs;

int main( int argc, char *argv[] )
{
    QApplication  apMainApp( argc, argv );

    g_poDB     = new cQTMySQLConnection;

    g_poPrefs  = new cPreferences( QString::fromAscii( "laza" ) );
    g_poPrefs->setVersion( "0.0.1" );

    int r = 1;
    try
    {
        g_poDB->open();
        g_obLogger.setDBConnection( g_poDB );

        g_obLogger << cSeverity::INFO;
        g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " started.";
        g_obLogger << cQTLogger::EOM;

        cWndMain  obMainWindow;
        obMainWindow.show();

        r = apMainApp.exec();

        g_obLogger << cSeverity::INFO;
        g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " ended.";
        g_obLogger << cQTLogger::EOM;
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity();
        g_obLogger << e.what();
        g_obLogger << cQTLogger::EOM;
    }

    delete g_poDB;
    delete g_poPrefs;

    return r;
}
