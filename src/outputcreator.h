#ifndef OUTPUTCREATOR_H
#define OUTPUTCREATOR_H

#include <QString>
#include <QStringList>
#include <map>
#include <sevexception.h>

#include "logdatasource.h"
#include "action.h"

class cOutputCreator
{
public:
    cOutputCreator( const QString &p_qsDirPrefix );
    ~cOutputCreator();

    unsigned int fileId( const QString & p_qsFileName )           throw( cSevException );
    void         addAction( const cAction *m_poAction )           throw( cSevException );
    void         addCountAction( const QString &p_qsCountName,
                                 const unsigned long p_ulOk,
                                 const unsigned long p_ulFailed ) throw();
    void         addAttribute( const QString &p_qsName,
                               const QString &p_qsValue )         throw();
    void         generateActionSummary()                          const throw( cSevException );
    void         generateActionList()                             const throw( cSevException );

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

    QString             m_qsOutDir;
    QStringList         m_slInputFiles;
};

#endif // OUTPUTCREATOR_H
