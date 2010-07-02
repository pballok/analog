#ifndef LOGDATASOURCE_H
#define LOGDATASOURCE_H

#include <QString>

using namespace std;

class cLogDataSource
{
public:
    cLogDataSource( const QString &p_qsInputDir, const QString &p_qsFiles );
    ~cLogDataSource();

private:
    void parseFileNames( const QString &p_qsInputDir, const QString &p_qsFiles );
};

#endif // LOGDATASOURCE_H
