#ifndef LOGANALYSER_H
#define LOGANALYSER_H

#include <QString>
#include <map>

#include <sevexception.h>

#include "logdatasource.h"
#include "actiondeflist.h"
#include "action.h"

class cLogAnalyser
{
public:
    typedef struct
    {
        unsigned int           uiFileId;
        unsigned long          ulLineNum;
        QString                qsTimeStamp;
        unsigned long long     ulTimeStamp;
        tmActionCapturedTexts  maCaptures;
    } tsFoundPattern;

    typedef multimap<QString, tsFoundPattern>   tmFoundPatternList;
    typedef tmFoundPatternList::const_iterator  tiFoundPatternList;

    cLogAnalyser( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions ) throw();
    ~cLogAnalyser() throw();

    void analyse() throw( cSevException );

private:
    cLogDataSource      *m_poDataSource;
    cActionDefList      *m_poActionDefList;
    tmFoundPatternList   m_maFoundPatterns;
    tmActionList         m_maActions;

    void findPatterns( const unsigned int p_uiFileId, const QString &p_qsFileName ) throw( cSevException );
    void storePattern( const unsigned int p_uiFileId, cActionDefList::tiPatternList p_itPattern,
                       const QString &p_qsLogLine, tmFoundPatternList::iterator  *p_poInsertPos ) throw( cSevException );
    void identifySingleLinerActions() throw();
};

#endif // LOGANALYSER_H
