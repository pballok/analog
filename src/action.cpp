#include "action.h"

cAction::cAction()
{
    m_qsName = "";
}

cAction::~cAction()
{
}

QString cAction::name() const throw()
{
    return m_qsName;
}

void cAction::setName( const QString &p_qsName ) throw()
{
    m_qsName = p_qsName;
}
