#ifndef LOGANALYZER_H
#define LOGANALYZER_H

#include "logdatasource.h"

#include <QString>

using namespace std;

class cLogAnalyzer
{
public:
    cLogAnalyzer( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions );
    ~cLogAnalyzer();

private:
    cLogDataSource  *m_poDataSource;
};

#endif // LOGANALYZER_H
