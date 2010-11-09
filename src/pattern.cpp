#include "lara.h"
#include "pattern.h"

cPattern::cPattern()
{
    cTracer  obTracer( &g_obLogger, "cPattern::cPattern" );

    init();
}

cPattern::cPattern( const QDomElement *p_poElem )
{
    init();

    if( p_poElem )
    {
        m_qsName = p_poElem->attribute( "name" );
        m_obRegExp.setPattern( p_poElem->attribute( "regexp" ) );

        for( QDomElement obElem = p_poElem->firstChildElement( "capture" );
        !obElem.isNull();
        obElem = obElem.nextSiblingElement( "capture" ) )
        {
            m_slCaptures.push_back( obElem.attribute( "name" ) );
        }
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

QStringList cPattern::captures() const throw()
{
    return m_slCaptures;
}

QStringList cPattern::capturedTexts( const QString &p_qsLogLine ) const throw()
{
    m_obRegExp.indexIn( p_qsLogLine );
    return m_obRegExp.capturedTexts();
}

void cPattern::init() throw()
{
    m_qsName = "";
    m_obRegExp.setPattern( "" );
}
