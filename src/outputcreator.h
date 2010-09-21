#ifndef OUTPUTCREATOR_H
#define OUTPUTCREATOR_H

#include <sevexception.h>

#include "logdatasource.h"
#include "action.h"

class cOutputCreator
{
public:
    cOutputCreator( cLogDataSource *p_poDataSource, tmActionList *p_poActionList, const QString &p_qsDirPrefix );
    ~cOutputCreator();

    void countActions() throw();
    void generateActionSummary() const throw( cSevException );

private:
    typedef struct
    {
        unsigned long ulOk;
        unsigned long ulFailed;
    } tsActionResCount;
    typedef map<QString, tsActionResCount*>     tmActionCountList;
    typedef tmActionCountList::const_iterator   tiActionCountList;

    cLogDataSource     *m_poDataSource;
    tmActionList       *m_poActionList;
    tmActionCountList   m_maActionCounts;

    QString             m_qsOutDir;
};

#endif // OUTPUTCREATOR_H
