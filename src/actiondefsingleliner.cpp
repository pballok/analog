#include "actiondefsingleliner.h"
#include "qtframework.h"

cActionDefSingleLiner::cActionDefSingleLiner() : cActionDef()
{
    cTracer  obTracer( "cActionDefSingleLiner::cActionDefSingleLiner" );

    m_qsPattern = "";
}

cActionDefSingleLiner::cActionDefSingleLiner( const QDomElement *p_poElem ) : cActionDef( p_poElem )
{
    cTracer  obTracer( "cActionDefSingleLiner::cActionDefSingleLiner", p_poElem->attribute( "name" ).toStdString() );

    m_qsPattern = p_poElem->attribute( "pattern", "" );
}

cActionDefSingleLiner::~cActionDefSingleLiner()
{
}

QString cActionDefSingleLiner::pattern() const throw()
{
    return m_qsPattern;
}
