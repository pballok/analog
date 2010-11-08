#include "lara.h"
#include "countaction.h"

cCountAction::cCountAction()
{
    cTracer  obTracer( &g_obLogger, "cCountAction::cCountAction" );

    m_qsName   = "";
}

cCountAction::cCountAction( const QDomElement *p_poElem )
{
    cTracer  obTracer( &g_obLogger, "cCountAction::cCountAction", p_poElem->attribute( "name" ).toStdString() );

    m_qsName   = p_poElem->attribute( "name", "" );

    for( QDomElement obActionElem = p_poElem->firstChildElement();
         !obActionElem.isNull();
         obActionElem = p_poElem->nextSiblingElement() )
    {
        if( obActionElem.tagName() == "action" )
        {
            m_veActionsToCount.push_back( obActionElem.attribute( "name" ) );
        }
    }
}

cCountAction::~cCountAction()
{
}

QString cCountAction::name() const throw()
{
    return m_qsName;
}

cCountAction::tiActionsToCount cCountAction::actionsToCountBegin() const throw()
{
    return m_veActionsToCount.begin();
}

cCountAction::tiActionsToCount cCountAction::actionsToCountEnd() const throw()
{
    return m_veActionsToCount.end();
}
