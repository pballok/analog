#include "actiondef.h"

cActionDef::cActionDef()
{
    m_qsName   = "";
    m_enResult = cActionResult::MIN;
    m_enUpload = cActionUpload::MIN;
}

cActionDef::cActionDef( QDomElement *p_poElem )
{
    m_qsName = p_poElem->attribute( "name", "" );
    m_enResult = cActionResult::fromStr( p_poElem->attribute( "result", "MIN" ).toAscii() );
    m_enUpload = cActionUpload::fromStr( p_poElem->attribute( "upload", "MIN" ).toAscii() );

}

cActionDef::~cActionDef()
{
}

QString cActionDef::name()   const throw()
{
    return m_qsName;
}

cActionResult::teResult cActionDef::result() const throw()
{
    return m_enResult;
}

cActionUpload::teUpload cActionDef::upload() const throw()
{
    return m_enUpload;
}
