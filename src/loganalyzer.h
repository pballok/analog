#ifndef LOGANALYZER_H
#define LOGANALYZER_H

#include "logdatasource.h"
#include "actiondeflist.h"

#include <QString>
#include <map>

using namespace std;

class cLogAnalyzer
{
public:
    typedef struct
    {
        unsigned int        uiFileId;
        unsigned long       ulLineNum;
        QString             qsTimeStamp;
        unsigned long long  ulTimeStamp;
    } tsFoundPattern;

    typedef multimap<QString, tsFoundPattern>   tmFoundPatternList;
    typedef tmFoundPatternList::const_iterator  tiFoundPatternList;

    cLogAnalyzer( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions ) throw();
    ~cLogAnalyzer() throw();

    void analyze() throw( cSevException );

private:
    cLogDataSource      *m_poDataSource;
    cActionDefList      *m_poActionDefList;
    tmFoundPatternList   m_maFoundPatterns;

    void findPatterns( const unsigned int p_uiFileId, const QString &p_qsFileName ) throw( cSevException );
    void storePattern( const unsigned int p_uiFileId, const QString &p_qsActionName, const QString &p_qsLogLine,
                       tmFoundPatternList::iterator  *p_poInsertPos ) throw( cSevException );
    void identifySingleLinerActions() throw();
};

#endif // LOGANALYZER_H
