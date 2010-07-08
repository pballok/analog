#ifndef ACTIONDEFLIST_H
#define ACTIONDEFLIST_H

#include <QString>
#include <QDomDocument>
#include <vector>

#include "actiondefsingleliner.h"
#include "sevexception.h"

using namespace std;

class cActionDefList
{
public:
    typedef vector<cActionDefSingleLiner*>  tvSingleLinerList;
    typedef tvSingleLinerList::iterator     tiSingleLinerList;

    cActionDefList( const QString &p_qsActionDefFile ) throw();
    ~cActionDefList() throw();

private:
    const QString      m_qsSchemaFileName;
    QDomDocument      *m_poActionsDoc;
    tvSingleLinerList  m_veSingleLinerList;

    void validateActionDef( const QString &p_qsActionDefFile ) throw( cSevException );
    void parseActionDef() throw( cSevException );
    void readSingleLiner( QDomElement *p_poElement ) throw( cSevException );
};

#endif // ACTIONDEFLIST_H
