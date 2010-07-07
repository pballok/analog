#include "action.h"

cAction::cAction()
{
    m_qsName   = "";
    m_enResult = cActionResult::MIN;
    m_enUpload = cActionUpload::MIN;
}

cAction::cAction( QDomElement &p_obElem )
{

}

cAction::~cAction()
{
}
