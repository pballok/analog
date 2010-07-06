#ifndef ACTIONS_H
#define ACTIONS_H

#include <QString>
#include <QDomDocument>

#include "sevexception.h"

class cActions
{
public:
    cActions( const QString &p_qsActionDefFile ) throw();
    ~cActions() throw();

private:
    const QString  m_qsSchemaFileName;
    QDomDocument  *m_poActionsDoc;

    void validateActionDef( const QString &p_qsActionDefFile ) throw( cSevException );
};

#endif // ACTIONS_H
