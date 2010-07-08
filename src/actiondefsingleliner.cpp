#include "actionsingleliner.h"

cActionSingleLiner::cActionSingleLiner() : cAction()
{
    m_qsPattern = "";
}

cActionSingleLiner::cActionSingleLiner( QDomElement *p_poElem ) : cAction( p_poElem )
{
    m_qsPattern = p_poElem->attribute( "pattern", "" );
}

cActionSingleLiner::~cActionSingleLiner()
{
}

QString cActionSingleLiner::pattern() const throw()
{
    return m_qsPattern;
}
