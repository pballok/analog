#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>

#include "dlgpreferences.h"
#include "qtframework.h"

cDlgPreferences::cDlgPreferences( QWidget *p_poParent )
    : QDialog( p_poParent )
{
    cTracer obTrace( "cDlgPreferences::cDlgPreferences" );

    setupUi( this );

    unsigned int  uiConLevel, uiDBLevel, uiGUILevel;
    g_poPrefs->getLogLevels( &uiConLevel, &uiDBLevel, &uiGUILevel );
    sliConsoleLogLevel->setValue( uiConLevel );
    sliDBLogLevel->setValue( uiDBLevel );
    sliGUILogLevel->setValue( uiGUILevel );

    ledInput->setText( g_poPrefs->getDefInputDir() );
    ledOutput->setText( g_poPrefs->getDefOutputDir() );
}

void cDlgPreferences::accept()
{
    g_poPrefs->setLogLevels( sliConsoleLogLevel->value(),
                             sliDBLogLevel->value(),
                             sliGUILogLevel->value() );

    g_poPrefs->setDefInputDir( ledInput->text() );
    g_poPrefs->setDefOutputDir( ledOutput->text() );

    g_poPrefs->save();

    QDialog::accept();
}

void cDlgPreferences::on_sliConsoleLogLevel_valueChanged( int p_inValue )
{
    lblConsoleLogLevelValue->setText( cSeverity::toStr( (cSeverity::teSeverity)p_inValue ) );
}

void cDlgPreferences::on_sliDBLogLevel_valueChanged( int p_inValue )
{
    lblDBLogLevelValue->setText( cSeverity::toStr( (cSeverity::teSeverity)p_inValue ) );
}

void cDlgPreferences::on_sliGUILogLevel_valueChanged( int p_inValue )
{
    lblGUILogLevelValue->setText( cSeverity::toStr( (cSeverity::teSeverity)p_inValue ) );
}

void cDlgPreferences::on_psbInput_clicked( bool )
{
    QFileDialog  obDlgFileOpen( this, "Default Input Directory" );
    obDlgFileOpen.setFileMode( QFileDialog::Directory );
    if( obDlgFileOpen.exec() )
    {
        ledInput->setText( obDlgFileOpen.selectedFiles().at( 0 ) );
    }
}

void cDlgPreferences::on_psbOutput_clicked( bool )
{
    QFileDialog  obDlgFileOpen( this, "Default Output Directory" );
    obDlgFileOpen.setFileMode( QFileDialog::Directory );
    if( obDlgFileOpen.exec() )
    {
        ledOutput->setText( obDlgFileOpen.selectedFiles().at( 0 ) );
    }
}
