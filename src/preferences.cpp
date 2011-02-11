#include <QSettings>

#include "lara.h"
#include "preferences.h"

cPreferences::cPreferences( const QString &p_qsAppName, const QString &p_qsVersion,
                            cConsoleWriter *p_poConsoleWriter, cFileWriter *p_poFileWriter  )
    : m_qsAppName( p_qsAppName ),
      m_qsVersion( p_qsVersion ),
      m_poConsoleWriter( p_poConsoleWriter ),
      m_poFileWriter( p_poFileWriter )
{
    m_qsInputDir  = "";
    m_qsOutputDir = "";
    m_qsTempDir   = "";
    m_qsFileName  = QString( "./%1.ini" ).arg( p_qsAppName );
    m_qsDBHost    = "";
    m_qsDBSchema  = "";
    m_qsDBUser    = "";
    m_qsDBPwd     = "";

    try
    {
        load();
    } catch( cSevException &e )
    {
        g_obLogger << e;
    }
}

cPreferences::~cPreferences()
{
}

QString cPreferences::appName() const
{
    return m_qsAppName;
}

QString cPreferences::version() const
{
    return m_qsVersion;
}

void cPreferences::setConsoleLogLevel( const cSeverity::teSeverity p_enLevel )
{
    m_poConsoleWriter->setMinSeverity( p_enLevel );
}

cSeverity::teSeverity cPreferences::consoleLogLevel() const
{
    return m_poConsoleWriter->minSeverity();
}

void cPreferences::setFileLogLevel( const cSeverity::teSeverity p_enLevel )
{
    m_poFileWriter->setMinSeverity( p_enLevel );
}

cSeverity::teSeverity cPreferences::fileLogLevel() const
{
    return m_poFileWriter->minSeverity();
}

QString cPreferences::inputDir() const
{
    return m_qsInputDir;
}

QString cPreferences::outputDir() const
{
    return m_qsOutputDir;
}

QString cPreferences::tempDir() const
{
    return m_qsTempDir;
}

QString cPreferences::dbHost() const
{
    return m_qsDBHost;
}

QString cPreferences::dbSchema() const
{
    return m_qsDBSchema;
}

QString cPreferences::dbUser() const
{
    return m_qsDBUser;
}

QString cPreferences::dbPassword() const
{
    return m_qsDBPwd;
}

void cPreferences::load() throw(cSevException)
{
    QSettings obPrefFile( m_qsFileName, QSettings::IniFormat );
    if( obPrefFile.status() != QSettings::NoError )
    {
        throw cSevException( cSeverity::WARNING, QString( "Failed to open preferences file: %1" ).arg( m_qsFileName ).toStdString() );
    }

    unsigned int uiConsoleLevel = obPrefFile.value( QString::fromAscii( "LogLevels/ConsoleLogLevel" ), cSeverity::ERROR ).toUInt();
    if( (uiConsoleLevel >= cSeverity::MAX) ||
        (uiConsoleLevel <= cSeverity::MIN) )
    {
        uiConsoleLevel = cSeverity::NONE;
        throw cSevException( cSeverity::WARNING, QString( "Invalid ConsoleLogLevel in preferences file: %1" ).arg( m_qsFileName ).toStdString() );
    }
    setConsoleLogLevel( (cSeverity::teSeverity)uiConsoleLevel );

    unsigned int uiFileLevel = obPrefFile.value( QString::fromAscii( "LogLevels/FileLogLevel" ), cSeverity::ERROR ).toUInt();
    if( (uiFileLevel >= cSeverity::MAX) ||
        (uiFileLevel <= cSeverity::MIN) )
    {
        uiFileLevel = cSeverity::NONE;
        throw cSevException( cSeverity::WARNING, QString( "Invalid FileLogLevel in preferences file: %1" ).arg( m_qsFileName ).toStdString() );
    }
    setFileLogLevel( (cSeverity::teSeverity)uiFileLevel );

    m_qsInputDir  = obPrefFile.value( QString::fromAscii( "Directories/InputDir" ), "." ).toString();
    m_qsOutputDir = obPrefFile.value( QString::fromAscii( "Directories/OutputDir" ), "." ).toString();
    m_qsTempDir   = obPrefFile.value( QString::fromAscii( "Directories/TempDir" ), "." ).toString();

    m_qsDBHost    = obPrefFile.value( QString::fromAscii( "DataBase/Host" ), "" ).toString();
    m_qsDBSchema  = obPrefFile.value( QString::fromAscii( "DataBase/Schema" ), "" ).toString();
    m_qsDBUser    = obPrefFile.value( QString::fromAscii( "DataBase/User" ), "" ).toString();
    m_qsDBPwd     = obPrefFile.value( QString::fromAscii( "DataBase/Password" ), "" ).toString();
}

