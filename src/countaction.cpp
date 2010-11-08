#include "lara.h"
#include "countaction.h"

cCountAction::cCountAction()
{
    cTracer  obTracer( &g_obLogger, "cCountAction::cCountAction" );

    m_qsName   = "";
    m_qsAction = "";
}

cCountAction::cCountAction( const QDomElement *p_poElem )
{
    cTracer  obTracer( &g_obLogger, "cCountAction::cCountAction", p_poElem->attribute( "name" ).toStdString() );

    m_qsName   = p_poElem->attribute( "name", "" );
    m_qsAction = p_poElem->attribute( "action", "");
}

cCountAction::~cCountAction()
{
}

QString cCountAction::name() const throw()
{
    return m_qsName;
}

QString cCountAction::action() const throw()
{
    return m_qsAction;
}

