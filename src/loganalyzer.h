#ifndef LOGANALYZER_H
#define LOGANALYZER_H

#include "logdatasource.h"
#include "actions.h"

#include <QString>

using namespace std;

class cLogAnalyzer
{
public:
    cLogAnalyzer( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions ) throw();
    ~cLogAnalyzer() throw();

private:
    cLogDataSource  *m_poDataSource;
    cActions        *m_poActions;
};

#endif // LOGANALYZER_H
