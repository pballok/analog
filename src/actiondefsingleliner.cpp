#include "actiondefsingleliner.h"
#include "qtframework.h"

cActionDefSingleLiner::cActionDefSingleLiner() : cActionDef()
{
    cTracer  obTracer( "cActionDefSingleLiner::cActionDefSingleLiner" );

    m_qsPattern = "";
    m_enResult  = cActionResult::MIN;
}

cActionDefSingleLiner::cActionDefSingleLiner( const QDomElement *p_poElem ) : cActionDef( p_poElem )
{
    cTracer  obTracer( "cActionDefSingleLiner::cActionDefSingleLiner", p_poElem->attribute( "name" ).toStdString() );

    m_qsPattern = p_poElem->attribute( "pattern", "" );
    m_enResult  = cActionResult::fromStr( p_poElem->attribute( "result", "MIN" ).toAscii() );
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

