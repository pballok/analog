#include "lara.h"
#include "countaction.h"

cCountAction::cCountAction()
{
    cTracer  obTracer( &g_obLogger, "cCountAction::cCountAction" );

    init();
}

cCountAction::cCountAction( const QDomElement *p_poElem )
{
    init();

    if( p_poElem )
    {
        m_qsName   = p_poElem->attribute( "name", "" );

        for( QDomElement obActionElem = p_poElem->firstChildElement( "action" );
             !obActionElem.isNull();
             obActionElem = obActionElem.nextSiblingElement( "action" ) )
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

void cCountAction::init() throw()
{
    m_qsName = "";
}
