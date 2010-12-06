#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>

#include <consolewriter.h>
#include <sevexception.h>

class cPreferences
{
public:
    cPreferences( const QString &p_qsAppName, const QString &p_qsVersion, cConsoleWriter *p_poConsoleWriter );
    ~cPreferences();

    QString                    appName() const;
    QString                    version() const;
    void                       setConsoleLogLevel( const cSeverity::teSeverity p_enLevel );
    cSeverity::teSeverity      consoleLogLevel() const;
    QString                    inputDir() const;
    QString                    outputDir() const;
    QString                    tempDir() const;
    QString                    dbHost() const;
    QString                    dbSchema() const;
    QString                    dbUser() const;
    QString                    dbPassword() const;

    void                       load() throw(cSevException);
    void                       save() const throw(cSevException);

private:
    QString                    m_qsAppName;
    QString                    m_qsFileName;
    QString                    m_qsVersion;
    QString                    m_qsInputDir;
    QString                    m_qsOutputDir;
    QString                    m_qsTempDir;
    QString                    m_qsDBHost;
    QString                    m_qsDBSchema;
    QString                    m_qsDBUser;
    QString                    m_qsDBPwd;

    cConsoleWriter*            m_poConsoleWriter;
};

#endif
