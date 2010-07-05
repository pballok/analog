#ifndef LOGDATASOURCE_H
#define LOGDATASOURCE_H

#include <QString>
#include <QStringList>

#include "sevexception.h"

using namespace std;

class cLogDataSource
{
public:
    cLogDataSource( const QString &p_qsInputDir, const QString &p_qsFiles ) throw();
    ~cLogDataSource() throw();

private:
    QStringList parseFileNames( const QString &p_qsInputDir, const QString &p_qsFiles ) throw();
    void prepareFiles( const QStringList &p_slFiles ) throw();
    QString unzipFile( const QString &p_stFileName ) throw( cSevException );
    QString gunzipFile( const QString &p_stFileName ) throw( cSevException );
    QString copyFile( const QString &p_stFileName ) throw( cSevException );

    QStringList m_slTempFiles;
};

#endif // LOGDATASOURCE_H
