#ifndef LOGDATASOURCE_H
#define LOGDATASOURCE_H

#include <QString>
#include <QStringList>

#include "sevexception.h"

using namespace std;

class cLogDataSource
{
public:
    cLogDataSource( const QString &p_qsInputDir, const QString &p_qsFiles );
    ~cLogDataSource();

private:
    QStringList parseFileNames( const QString &p_qsInputDir, const QString &p_qsFiles ) throw();
    void prepareFiles( const QStringList &p_slFiles ) throw();
    void unzipFile( const QString &p_stFileName ) throw( cSevException );
    void gunzipFile( const QString &p_stFileName ) throw( cSevException );
    void copyFile( const QString &p_stFileName ) throw( cSevException );

    QStringList m_slTempFiles;
};

#endif // LOGDATASOURCE_H
