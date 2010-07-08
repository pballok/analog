#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include <QString>
#include <QDomDocument>
#include <vector>

#include "actionsingleliner.h"
#include "sevexception.h"

using namespace std;

class cActionList
{
public:
    typedef vector<cActionSingleLiner*>  tvSingleLinerList;
    typedef tvSingleLinerList::iterator  tiSingleLinerList;

    cActionList( const QString &p_qsActionDefFile ) throw();
    ~cActionList() throw();

private:
    const QString      m_qsSchemaFileName;
    QDomDocument      *m_poActionsDoc;
    tvSingleLinerList  m_veSingleLinerList;

    void validateActionDef( const QString &p_qsActionDefFile ) throw( cSevException );
    void readActions() throw( cSevException );
    void readSingleLiner( QDomElement *p_poElement ) throw( cSevException );
};

#endif // ACTIONS_H
