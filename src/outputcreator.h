#ifndef OUTPUTCREATOR_H
#define OUTPUTCREATOR_H

#include <QString>
#include <QStringList>
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
    void         generateActionSummary()                          throw( cSevException );

private:
    typedef struct
    {
        unsigned long ulOk;
        unsigned long ulFailed;
    } tsActionResCount;
    typedef map<QString, tsActionResCount*>     tmActionCountList;
    typedef tmActionCountList::const_iterator   tiActionCountList;

    tmActionList        m_mmActionList;
    tmActionCountList   m_maActionCounts;

    QString             m_qsOutDir;
    QStringList         m_slInputFiles;
};

#endif // OUTPUTCREATOR_H
