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
                                 const unsigned int p_uiDBLevel,
                                 const unsigned int p_uiGUILevel,
                                 bool p_boSaveNow )
{
    g_obLogger.setMinSeverityLevels( (cSeverity::teSeverity)p_uiConLevel,
                                     (cSeverity::teSeverity)p_uiDBLevel,
                                     (cSeverity::teSeverity)p_uiGUILevel );

    if( p_boSaveNow )
    {
        QSettings  obPrefFile( m_qsFileName, QSettings::IniFormat );
        obPrefFile.setValue( QString::fromAscii( "LogLevels/ConsoleLogLevel" ), p_uiConLevel );
        obPrefFile.setValue( QString::fromAscii( "LogLevels/DBLogLevel" ), p_uiDBLevel );
        obPrefFile.setValue( QString::fromAscii( "LogLevels/GUILogLevel" ), p_uiGUILevel );
    }
}

void cPreferences::getLogLevels( unsigned int *p_poConLevel,
                                 unsigned int *p_poDBLevel,
                                 unsigned int *p_poGUILevel ) const
{
    cSeverity::teSeverity  enConLevel = cSeverity::DEBUG;
    cSeverity::teSeverity  enDBLevel  = cSeverity::DEBUG;
    cSeverity::teSeverity  enGUILevel = cSeverity::DEBUG;
    g_obLogger.getMinSeverityLevels( &enConLevel, &enDBLevel, &enGUILevel );

    if( p_poConLevel ) *p_poConLevel = enConLevel;
    if( p_poDBLevel )  *p_poDBLevel  = enDBLevel;
    if( p_poGUILevel ) *p_poGUILevel = enGUILevel;
}

void cPreferences::setDBAccess( const QString &p_qsHost, const QString &p_qsDB,
                                const QString &p_qsUser, const QString &p_qsPwd,
                                const bool p_boSaveNow )
{
    g_poDB->setHostName( p_qsHost );
    g_poDB->setDatabaseName( p_qsDB );
    g_poDB->setUserName( p_qsUser );
    g_poDB->setPassword( p_qsPwd );

    if( p_boSaveNow )
    {
        QSettings  obPrefFile( m_qsFileName, QSettings::IniFormat );
        obPrefFile.setValue( QString::fromAscii( "DB/Host" ), g_poDB->getHostName() );
        obPrefFile.setValue( QString::fromAscii( "DB/Name" ), g_poDB->getDatabaseName() );
        obPrefFile.setValue( QString::fromAscii( "DB/User" ), g_poDB->getUserName() );
        obPrefFile.setValue( QString::fromAscii( "DB/Password" ), g_poDB->getPassword() );
    }
}

void cPreferences::getDBAccess( QString *p_poHost, QString *p_poDB,
                                QString *p_poUser, QString *p_poPwd ) const
{
    if( p_poHost ) *p_poHost = g_poDB->getHostName();
    if( p_poDB )   *p_poDB   = g_poDB->getDatabaseName();
    if( p_poUser ) *p_poUser = g_poDB->getUserName();
    if( p_poPwd )  *p_poPwd  = g_poDB->getPassword();
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

        unsigned int uiDBLevel = obPrefFile.value( QString::fromAscii( "LogLevels/DBLogLevel" ), cSeverity::ERROR ).toUInt();
        if( (uiDBLevel >= cSeverity::MAX) &&
            (uiDBLevel <= cSeverity::MIN) )
        {
            uiDBLevel = cSeverity::DEBUG;

            g_obLogger << cSeverity::WARNING;
            g_obLogger << "Invalid DBLogLevel in preferences file: " << m_qsFileName.toStdString();
            g_obLogger << cQTLogger::EOM;
        }

        unsigned int uiGUILevel = obPrefFile.value( QString::fromAscii( "LogLevels/GUILogLevel" ), cSeverity::ERROR ).toUInt();
        if( (uiGUILevel >= cSeverity::MAX) &&
            (uiGUILevel <= cSeverity::MIN) )
        {
            uiGUILevel = cSeverity::DEBUG;

            g_obLogger << cSeverity::WARNING;
            g_obLogger << "Invalid GUILogLevel in preferences file: " << m_qsFileName.toStdString();
            g_obLogger << cQTLogger::EOM;
        }

        setLogLevels( uiConsoleLevel, uiDBLevel, uiGUILevel );

        QString qsDBHost     = obPrefFile.value( QString::fromAscii( "DB/Host" ), "" ).toString();
        QString qsDBName     = obPrefFile.value( QString::fromAscii( "DB/Name" ), "" ).toString();
        QString qsDBUser     = obPrefFile.value( QString::fromAscii( "DB/User" ), "" ).toString();
        QString qsDBPassword = obPrefFile.value( QString::fromAscii( "DB/Password" ), "" ).toString();
        g_poDB->setHostName( qsDBHost );
        g_poDB->setDatabaseName( qsDBName );
        g_poDB->setUserName( qsDBUser );
        g_poDB->setPassword( qsDBPassword );

        m_qsDefInputDir = obPrefFile.value( QString::fromAscii( "Directories/InputDir" ), "" ).toString();
        m_qsDefOutputDir = obPrefFile.value( QString::fromAscii( "Directories/OutputDir" ), "" ).toString();
    }
}

void cPreferences::save() const
{
    QSettings  obPrefFile( m_qsFileName, QSettings::IniFormat );

    unsigned int  uiConLevel, uiDBLevel, uiGUILevel;
    getLogLevels( &uiConLevel, &uiDBLevel, &uiGUILevel );
    obPrefFile.setValue( QString::fromAscii( "LogLevels/ConsoleLogLevel" ), uiConLevel );
    obPrefFile.setValue( QString::fromAscii( "LogLevels/DBLogLevel" ), uiDBLevel );
    obPrefFile.setValue( QString::fromAscii( "LogLevels/GUILogLevel" ), uiGUILevel );

    obPrefFile.setValue( QString::fromAscii( "DB/Host" ), g_poDB->getHostName() );
    obPrefFile.setValue( QString::fromAscii( "DB/Name" ), g_poDB->getDatabaseName() );
    obPrefFile.setValue( QString::fromAscii( "DB/User" ), g_poDB->getUserName() );
    obPrefFile.setValue( QString::fromAscii( "DB/Password" ), g_poDB->getPassword() );

    obPrefFile.setValue( QString::fromAscii( "Directories/InputDir" ), m_qsDefInputDir );
    obPrefFile.setValue( QString::fromAscii( "Directories/OutputDir" ), m_qsDefOutputDir );
}
