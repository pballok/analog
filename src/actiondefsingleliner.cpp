#include "lara.h"
#include "actiondefsingleliner.h"

cActionDefSingleLiner::cActionDefSingleLiner() : cActionDef()
{
    init();
}

cActionDefSingleLiner::cActionDefSingleLiner( const QDomElement *p_poElem ) : cActionDef( p_poElem )
{
    init();

    if( p_poElem )
    {
        m_qsPattern = p_poElem->attribute( "pattern", "" );
        m_enResult  = cActionResult::fromStr( p_poElem->attribute( "result", "MIN" ).toAscii() );
    }
}

cActionDefSingleLiner::~cActionDefSingleLiner()
{
}

QString cActionDefSingleLiner::pattern() const throw()
{
    return m_qsPattern;
}

cActionResult::teResult cActionDefSingleLiner::result() const throw()
{
    return m_enResult;
}

void cActionDefSingleLiner::init() throw()
{
    m_qsPattern = "";
    m_enResult  = cActionResult::MIN;
}
