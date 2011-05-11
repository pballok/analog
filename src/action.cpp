#include "lara.h"
#include "action.h"

using namespace std;

cAction::cAction( const QString &p_qsName, const QString &p_qsTimeStamp,
                  const tsTimeStamp* p_poTimeStamp,
                  const unsigned int p_uiFileId, const unsigned long p_ulLineNum,
                  const cActionResult::teResult p_enResult, const cActionUpload::teUpload p_enUpload )
{
    cTracer  obTracer( &g_obLogger, "cAction::cAction", p_qsName.toStdString() );

    m_qsName      = p_qsName;
    m_qsTimeStamp = p_qsTimeStamp;
    if( p_poTimeStamp ) m_suTimeStamp = *p_poTimeStamp;
    else
    {
        m_suTimeStamp.uiYear    = 0;
        m_suTimeStamp.uiMonth   = 0;
        m_suTimeStamp.uiDay     = 0;
        m_suTimeStamp.uiHour    = 0;
        m_suTimeStamp.uiMinute  = 0;
        m_suTimeStamp.uiSecond  = 0;
        m_suTimeStamp.uiMSecond = 0;
    }
    m_uiFileId    = p_uiFileId;
    m_ulLineNum   = p_ulLineNum;
    m_enResult    = p_enResult;
    m_enUpload    = p_enUpload;
}

cAction::~cAction()
{
}

QString cAction::name() const throw()
{
    return m_qsName;
}

QString cAction::timeStamp() const throw()
{
    return m_qsTimeStamp;
}

cAction::tsTimeStamp cAction::timeStampStruct() const throw()
{
    return m_suTimeStamp;
}

unsigned int cAction::fileId() const throw()
{
    return m_uiFileId;
}

unsigned long cAction::lineNum() const throw()
{
    return m_ulLineNum;
}

cActionResult::teResult cAction::result() const throw()
{
    return m_enResult;
}

cActionUpload::teUpload cAction::upload() const throw()
{
    return m_enUpload;
}

void cAction::addAttribute( const QString &p_qsAttribName, const QString &p_qsAttribValue ) throw()
{
    m_maAttribs.insert( pair<QString,QString>( p_qsAttribName, p_qsAttribValue ) );
}

tiActionAttribs cAction::attributesBegin() const throw()
{
    return m_maAttribs.begin();
}

tiActionAttribs cAction::attributesEnd() const throw()
{
    return m_maAttribs.end();
}

QString cAction::attribute( const QString &p_qsAttribName ) const throw()
{
    tiActionAttribs itAttrib = m_maAttribs.find( p_qsAttribName );
    if( itAttrib != m_maAttribs.end() ) return itAttrib->second;
    else return "";
}
