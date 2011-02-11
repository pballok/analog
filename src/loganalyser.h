#ifndef LOGANALYSER_H
#define LOGANALYSER_H

#include <QString>
#include <map>

#include <sevexception.h>

#include "logdatasource.h"
#include "actiondeflist.h"
#include "action.h"
#include "outputcreator.h"

class cLogAnalyser
{
public:
    typedef struct
    {
        unsigned int          uiFileId;
        unsigned long         ulLineNum;
        QString               qsTimeStamp;
        cAction::tsTimeStamp  suTimeStamp;
        tmActionAttribs       maCapturedAttribs;
    } tsFoundPattern;

    typedef std::multimap<QString, tsFoundPattern> tmFoundPatternList;
    typedef tmFoundPatternList::const_iterator     tiFoundPatternList;

    cLogAnalyser( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions, cOutputCreator *p_poOC ) throw();
    ~cLogAnalyser() throw();

    void analyse() throw( cSevException );

private:
    cLogDataSource      *m_poDataSource;
    cActionDefList      *m_poActionDefList;
    tmFoundPatternList   m_maFoundPatterns;
    tmActionList         m_mmActionList;
    cOutputCreator      *m_poOC;

    void findPatterns( const QString &p_qsFileName ) throw();
    void storePattern( const unsigned int p_uiFileId, cActionDefList::tiPatternList p_itPattern,
                       const QString &p_qsLogLine, tmFoundPatternList::iterator  *p_poInsertPos ) throw( cSevException );
    void identifySingleLinerActions() throw();
    void countActions( const QString &p_qsCountName,
                       const QString &p_qsActionName,
                       const QString &p_qsAttribName ) throw();
    void storeActions()    throw( cSevException );
    void storeAttributes() throw();
};

#endif // LOGANALYSER_H
