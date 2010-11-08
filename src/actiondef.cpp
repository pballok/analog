#include "actiondef.h"

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

void cActionDef::init()   throw()
{
    m_qsName   = "";
    m_enUpload = cActionUpload::MIN;
}
