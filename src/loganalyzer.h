#ifndef LOGANALYZER_H
#define LOGANALYZER_H

#include "logdatasource.h"
#include "actiondeflist.h"

#include <QString>

using namespace std;

class cLogAnalyzer
{
public:
    cLogAnalyzer( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions ) throw();
    ~cLogAnalyzer() throw();

    void analyze() throw( cSevException );

private:
    cLogDataSource  *m_poDataSource;
    cActionDefList  *m_poActionDefList;

    void findPatterns( const QString &p_qsFileName ) throw( cSevException );
};

#endif // LOGANALYZER_H
