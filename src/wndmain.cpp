#include <QMessageBox>

#include "wndmain.h"
#include "dlgpreferences.h"
#include "qtframework.h"

cWndMain::cWndMain( QWidget *parent )
    : QMainWindow( parent )
{
    cTracer obTrace( "cWndMain::cWndMain" );

    setupUi( this );

    updateTitle();
}

cWndMain::~cWndMain()
{
    cTracer obTrace( "cWndMain::~cWndMain" );
}

void cWndMain::updateTitle()
{
    cTracer obTrace( "cWndMain::updateTitle" );

    QString  qsTitle = g_poPrefs->getAppName();
    qsTitle += " ";
    qsTitle += g_poPrefs->getVersion();

    setWindowTitle( qsTitle );
}

void cWndMain::on_action_Preferences_triggered()
{
    cTracer obTrace( "cWndMain::on_action_Preferences_triggered" );

    cDlgPreferences  obDlgPrefs( this );

    obDlgPrefs.exec();
}
