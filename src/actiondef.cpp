#include "actiondef.h"

using namespace std;

cActionDef::cActionDef()
{
    init();
}

cActionDef::cActionDef( const QDomElement *p_poElem )
{
    init();

    if( p_poElem )
    {
        m_qsName = p_poElem->attribute( "name", "" );
        m_enUpload = cActionUpload::fromStr( p_poElem->attribute( "upload", "MIN" ).toAscii() );
    }

    for( QDomElement obElem = p_poElem->firstChildElement( "fixed_attrib" );
        !obElem.isNull();
        obElem = obElem.nextSiblingElement( "fixed_attrib" ) )
    {
        if( obElem.attribute( "name", "" ) != "" )
        {
            m_maFixedAttribs.insert( pair<QString,QString>(obElem.attribute( "name", "" ), obElem.attribute( "value", "" ) ) );
        }
    }

}

cActionDef::~cActionDef()
{
}

QString cActionDef::name()   const throw()
{
    return m_qsName;
}

cActionUpload::teUpload cActionDef::upload() const throw()
{
    return m_enUpload;
}

tiFixedAttribs cActionDef::fixedAttributesBegin() const throw()
{
    return m_maFixedAttribs.begin();
}

tiFixedAttribs cActionDef::fixedAttributesEnd()   const throw()
{
    return m_maFixedAttribs.end();
}

void cActionDef::init()   throw()
{
    m_qsName   = "";
    m_enUpload = cActionUpload::MIN;
}
