#ifndef OUTPUTCREATOR_H
#define OUTPUTCREATOR_H

#include <QString>
#include <QStringList>
#include <map>
#include <qtmysqlconnection.h>
#include <sevexception.h>

#include "logdatasource.h"
#include "action.h"

class cOutputCreator
{
public:
    cOutputCreator( const QString &p_qsDirPrefix );
    ~cOutputCreator();

    unsigned int fileId( const QString & p_qsFileName )                 throw( cSevException );
    void         addAction( const cAction *m_poAction )                 throw( cSevException );
    void         addCountAction( const QString &p_qsCountName,
                                 const unsigned long p_ulOk,
                                 const unsigned long p_ulFailed )       throw();
    void         addAttribute( const QString &p_qsName,
                               const QString &p_qsValue )               throw();
    void         addCombilogEntry( const unsigned long long p_ulTime,
                                   const QString &p_qsLogLine,
                                   const QString &p_qsColor )           throw();
    void         generateActionSummary()                          const throw( cSevException );
    void         uploadActionSummary()                                  throw( cSevException );
    void         generateActionList()                             const throw( cSevException );
    void         uploadActionList()                               const throw( cSevException );

private:

    tmActionList        m_mmActionList;

    typedef struct
    {
        unsigned long ulOk;
        unsigned long ulFailed;
    } tsActionResCount;
    typedef std::map<QString, tsActionResCount*> tmActionCountList;
    typedef tmActionCountList::const_iterator    tiActionCountList;
    tmActionCountList   m_maActionCounts;

    typedef std::map<QString,QString>            tmAttributes;
    typedef tmAttributes::const_iterator         tiAttributes;
    tmAttributes        m_maAttributes;

    typedef struct
    {
        QString qsLogLine;
        QString qsColor;
    } tsCombilogEntry;
    typedef std::multimap<unsigned long long, tsCombilogEntry> tmCombilogEntries;
    typedef tmCombilogEntries::const_iterator                  tiCombilogEntries;
    tmCombilogEntries   m_mmCombilogEntries;

    cQTMySQLConnection *m_poDB;
    QString             m_qsOutDir;
    QStringList         m_slInputFiles;
    unsigned long long  m_ulBatchId;
};

#endif // OUTPUTCREATOR_H
