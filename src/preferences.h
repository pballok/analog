#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>

class cPreferences
{
public:
    cPreferences();
    cPreferences( const QString &p_qsFileName );
    ~cPreferences();

    void                       setAppName( const QString &p_qsFileName );
    QString                    getAppName() const;
    void                       setVersion( const QString &p_qsVersion );
    QString                    getVersion() const;
    void                       setLogLevels( const unsigned int p_uiConLevel,
                                             bool p_boSaveNow = false );
    void                       getLogLevels( unsigned int *p_poConLevel = NULL ) const;
    void                       setInputDir( const QString &p_qsDir );
    QString                    getInputDir() const;
    void                       setOutputDir( const QString &p_qsDir );
    QString                    getOutputDir() const;
    void                       setTempDir( const QString &p_qsDir );
    QString                    getTempDir() const;

    void                       load();
    void                       save() const;

private:
    QString                    m_qsAppName;
    QString                    m_qsFileName;
    QString                    m_qsVersion;
    QString                    m_qsInputDir;
    QString                    m_qsOutputDir;
    QString                    m_qsTempDir;

    void init();
};

#endif
