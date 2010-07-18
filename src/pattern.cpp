#include "pattern.h"
#include "qtframework.h"

cPattern::cPattern()
{
    cTracer  obTracer( "cPattern::cPattern" );

    m_qsName = "";
    m_obRegExp.setPattern( "" );
}

cPattern::cPattern( const QDomElement *p_poElem )
{
    cTracer  obTracer( "cPattern::cPattern", p_poElem->attribute( "name" ).toStdString() );

    m_qsName = p_poElem->attribute( "name" );
    m_obRegExp.setPattern( p_poElem->attribute( "regexp" ) );

    for( QDomElement obElem = p_poElem->firstChildElement( "capture" );
         !obElem.isNull();
         obElem = obElem.nextSiblingElement( "capture" ) )
    {
        m_slCaptures.push_back( obElem.attribute( "name" ) );
    }
}

cPattern::~cPattern()
{
}

QString cPattern::name() const throw()
{
    return m_qsName;
}

QString cPattern::pattern() const throw()
{
    return m_obRegExp.pattern();
}
