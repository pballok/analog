#ifndef OUTPUTCREATOR_H
#define OUTPUTCREATOR_H

#include "logdatasource.h"
#include "action.h"

class cOutputCreator
{
public:
    cOutputCreator( cLogDataSource *p_poDataSource, tmActionList *p_poActionList );
    ~cOutputCreator();

private:
    cLogDataSource  *m_poDataSource;
    tmActionList    *m_poActionList;
};

#endif // OUTPUTCREATOR_H
