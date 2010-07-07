#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include <QString>
#include <QDomDocument>

#include "sevexception.h"


class cActionList
{
public:
    cActionList( const QString &p_qsActionDefFile ) throw();
    ~cActionList() throw();

private:
    const QString  m_qsSchemaFileName;
    QDomDocument  *m_poActionsDoc;

    void validateActionDef( const QString &p_qsActionDefFile ) throw( cSevException );
    void readActions() throw( cSevException );
    void readSingleLiner( QDomElement *p_poElement ) throw( cSevException );
};

#endif // ACTIONS_H
