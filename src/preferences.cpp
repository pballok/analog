#include "preferences.h"
#include "qtframework.h"

#include <QSettings>

cPreferences::cPreferences()
{
    init();
}

cPreferences::cPreferences( const QString &p_qsFileName )
{
    init();
    setAppName( p_qsFileName );
    load();
}

cPreferences::~cPreferences()
{
}

void cPreferences::init()
{
    m_qsAppName         = "";
    m_qsFileName        = "";
    m_qsVersion         = "";
    m_qsDefInputDir     = "";
    m_qsDefOutputDir    = "";
}

void cPreferences::setAppName( const QString &p_qsAppName )
{
    m_qsAppName = p_qsAppName;
    m_qsFileName = QString( "./%1.ini" ).arg( p_qsAppName );
}

QString cPreferences::getAppName() const
{
    return m_qsAppName;
}

void cPreferences::setVersion( const QString &p_qsVersion )
{
    m_qsVersion = p_qsVersion;
}

QString cPreferences::getVersion() const
{
    return m_qsVersion;
}

void cPreferences::setLogLevels( const unsigned int p_uiConLevel,
                                 bool p_boSaveNow )
{
    g_obLogger.setMinSeverityLevels( (cSeverity::teSeverity)p_uiConLevel );

    if( p_boSaveNow )
    {
        QSettings  obPrefFile( m_qsFileName, QSettings::IniFormat );
        obPrefFile.setValue( QString::fromAscii( "LogLevels/ConsoleLogLevel" ), p_uiConLevel );
    }
}

void cPreferences::getLogLevels( unsigned int *p_poConLevel ) const
{
    cSeverity::teSeverity  enConLevel = cSeverity::DEBUG;
    g_obLogger.getMinSeverityLevels( &enConLevel );

    if( p_poConLevel ) *p_poConLevel = enConLevel;
}

QString cPreferences::getDefInputDir() const
{
    return m_qsDefInputDir;
}

void cPreferences::setDefInputDir( const QString &p_qsDir )
{
    m_qsDefInputDir = p_qsDir;
}

QString cPreferences::getDefOutputDir() const
{
    return m_qsDefOutputDir;
}

void cPreferences::setDefOutputDir( const QString &p_qsDir )
{
    m_qsDefOutputDir = p_qsDir;
}

void cPreferences::load()
{
    QSettings obPrefFile( m_qsFileName, QSettings::IniFormat );

    if( obPrefFile.status() != QSettings::NoError )
    {
        g_obLogger << cSeverity::WARNING;
        g_obLogger << "Failed to load preferences from file: " << m_qsFileName.toStdString();
        g_obLogger << cQTLogger::EOM;
    }
    else
    {
        unsigned int uiConsoleLevel = obPrefFile.value( QString::fromAscii( "LogLevels/ConsoleLogLevel" ), cSeverity::ERROR ).toUInt();
        if( (uiConsoleLevel >= cSeverity::MAX) ||
            (uiConsoleLevel <= cSeverity::MIN) )
        {
            uiConsoleLevel = cSeverity::DEBUG;

            g_obLogger << cSeverity::WARNING;
            g_obLogger << "Invalid ConsoleLogLevel in preferences file: " << m_qsFileName.toStdString();
            g_obLogger << cQTLogger::EOM;
        }

        setLogLevels( uiConsoleLevel );

        m_qsDefInputDir = obPrefFile.value( QString::fromAscii( "Directories/InputDir" ), "" ).toString();
        m_qsDefOutputDir = obPrefFile.value( QString::fromAscii( "Directories/OutputDir" ), "" ).toString();
    }
}

void cPreferences::save() const
{
    QSettings  obPrefFile( m_qsFileName, QSettings::IniFormat );

    unsigned int  uiConLevel;
    getLogLevels( &uiConLevel );
    obPrefFile.setValue( QString::fromAscii( "LogLevels/ConsoleLogLevel" ), uiConLevel );

    obPrefFile.setValue( QString::fromAscii( "Directories/InputDir" ), m_qsDefInputDir );
    obPrefFile.setValue( QString::fromAscii( "Directories/OutputDir" ), m_qsDefOutputDir );
}
