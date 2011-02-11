#ifndef LOGDATASOURCE_H
#define LOGDATASOURCE_H

#include <QString>
#include <QStringList>

#include <sevexception.h>

class cLogDataSource
{
public:
    cLogDataSource( const QString &p_qsInputDir, const QString &p_qsFiles ) throw();
    ~cLogDataSource();

    QStringList logFileList() const throw();
    QStringList origFileList() const throw();

private:
    void    parseFileNames( const QString &p_qsInputDir, const QString &p_qsFiles ) throw();
    void    prepareFiles() throw();
    QString unzipFile( const QString &p_qsFileName ) throw( cSevException );
    QString gunzipFile( const QString &p_qsFileName ) throw( cSevException );
    QString copyFile( const QString &p_qsFileName ) throw( cSevException );
    QString decodeFile( const QString &p_qsFileName ) throw( cSevException );
    QString decodeString( const QString &p_qsInput ) throw();

    QStringList m_slTempFiles;
    QStringList m_slOrigFiles;
};

#endif // LOGDATASOURCE_H
