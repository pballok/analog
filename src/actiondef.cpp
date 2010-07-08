#include "action.h"

cAction::cAction()
{
    m_qsName   = "";
    m_enResult = cActionResult::MIN;
    m_enUpload = cActionUpload::MIN;
}

cAction::cAction( QDomElement *p_poElem )
{
    m_qsName = p_poElem->attribute( "name", "" );
    m_enResult = cActionResult::fromStr( p_poElem->attribute( "result", "MIN" ).toAscii() );
    m_enUpload = cActionUpload::fromStr( p_poElem->attribute( "upload", "MIN" ).toAscii() );

}

cAction::~cAction()
{
}

QString cAction::name()   const throw()
{
    return m_qsName;
}

cActionResult::teResult cAction::result() const throw()
{
    return m_enResult;
}

cActionUpload::teUpload cAction::upload() const throw()
{
    return m_enUpload;
}
