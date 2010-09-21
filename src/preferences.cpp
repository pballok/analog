#include <QSettings>

#include "lara.h"
#include "preferences.h"

cPreferences::cPreferences( const QString &p_qsAppName, const QString &p_qsVersion, cConsoleWriter *p_poConsoleWriter  )
    : m_qsAppName( p_qsAppName ),
      m_qsVersion( p_qsVersion ),
      m_poConsoleWriter( p_poConsoleWriter )
{
    m_qsInputDir  = "";
    m_qsOutputDir = "";
    m_qsTempDir   = "";
    m_qsFileName  = QString( "./%1.ini" ).arg( p_qsAppName );

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

QString cPreferences::inputDir() const
{
    return m_qsInputDir;
}

void cPreferences::setInputDir( const QString &p_qsDir )
{
    m_qsInputDir = p_qsDir;
}

QString cPreferences::outputDir() const
{
    return m_qsOutputDir;
}

void cPreferences::setOutputDir( const QString &p_qsDir )
{
    m_qsOutputDir = p_qsDir;
}

QString cPreferences::tempDir() const
{
    return m_qsTempDir;
}

void cPreferences::setTempDir( const QString &p_qsDir )
{
    m_qsTempDir = p_qsDir;
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

    m_qsInputDir = obPrefFile.value( QString::fromAscii( "Directories/InputDir" ), "." ).toString();
    m_qsOutputDir = obPrefFile.value( QString::fromAscii( "Directories/OutputDir" ), "." ).toString();
    m_qsTempDir = obPrefFile.value( QString::fromAscii( "Directories/TempDir" ), "." ).toString();
}

void cPreferences::save() const throw(cSevException)
{
    QSettings  obPrefFile( m_qsFileName, QSettings::IniFormat );
    if( obPrefFile.status() != QSettings::NoError )
    {
        throw cSevException( cSeverity::WARNING, QString( "Failed to write to preferences file: %1" ).arg( m_qsFileName ).toStdString() );
    }

    unsigned int  uiConLevel = consoleLogLevel();
    obPrefFile.setValue( QString::fromAscii( "LogLevels/ConsoleLogLevel" ), uiConLevel );

    obPrefFile.setValue( QString::fromAscii( "Directories/InputDir" ), m_qsInputDir );
    obPrefFile.setValue( QString::fromAscii( "Directories/OutputDir" ), m_qsOutputDir );
    obPrefFile.setValue( QString::fromAscii( "Directories/TempDir" ), m_qsTempDir );
}
