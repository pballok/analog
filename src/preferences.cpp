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
    m_qsAppName      = "";
    m_qsFileName     = "";
    m_qsVersion      = "";
    m_qsInputDir     = "";
    m_qsOutputDir    = "";
    m_qsTempDir      = "";
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

QString cPreferences::getInputDir() const
{
    return m_qsInputDir;
}

void cPreferences::setInputDir( const QString &p_qsDir )
{
    m_qsInputDir = p_qsDir;
}

QString cPreferences::getOutputDir() const
{
    return m_qsOutputDir;
}

void cPreferences::setOutputDir( const QString &p_qsDir )
{
    m_qsOutputDir = p_qsDir;
}

QString cPreferences::getTempDir() const
{
    return m_qsTempDir;
}

void cPreferences::setTempDir( const QString &p_qsDir )
{
    m_qsTempDir = p_qsDir;
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

        m_qsInputDir = obPrefFile.value( QString::fromAscii( "Directories/InputDir" ), "." ).toString();
        m_qsOutputDir = obPrefFile.value( QString::fromAscii( "Directories/OutputDir" ), "." ).toString();
        m_qsTempDir = obPrefFile.value( QString::fromAscii( "Directories/TempDir" ), "." ).toString();
    }
}

void cPreferences::save() const
{
    QSettings  obPrefFile( m_qsFileName, QSettings::IniFormat );

    unsigned int  uiConLevel;
    getLogLevels( &uiConLevel );
    obPrefFile.setValue( QString::fromAscii( "LogLevels/ConsoleLogLevel" ), uiConLevel );

    obPrefFile.setValue( QString::fromAscii( "Directories/InputDir" ), m_qsInputDir );
    obPrefFile.setValue( QString::fromAscii( "Directories/OutputDir" ), m_qsOutputDir );
    obPrefFile.setValue( QString::fromAscii( "Directories/TempDir" ), m_qsTempDir );
}
