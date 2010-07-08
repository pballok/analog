#include "actiondefsingleliner.h"

cActionDefSingleLiner::cActionDefSingleLiner() : cActionDef()
{
    m_qsPattern = "";
}

cActionDefSingleLiner::cActionDefSingleLiner( QDomElement *p_poElem ) : cActionDef( p_poElem )
{
    m_qsPattern = p_poElem->attribute( "pattern", "" );
}

cActionDefSingleLiner::~cActionDefSingleLiner()
{
}

QString cActionDefSingleLiner::pattern() const throw()
{
    return m_qsPattern;
}
