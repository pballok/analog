#include "lara.h"
#include "action.h"

cAction::cAction( const QString &p_qsName, const QString &p_qsTimeStamp,
                  const unsigned int p_uiFileId, const unsigned long p_ulLineNum,
                  const cActionResult::teResult p_enResult, const cActionUpload::teUpload p_enUpload )
{
    cTracer  obTracer( &g_obLogger, "cAction::cAction", p_qsName.toStdString() );

    m_qsName      = p_qsName;
    m_qsTimeStamp = p_qsTimeStamp;
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

void cAction::addCapturedText( const QString &p_qsTextName, const QString &p_qsTextValue ) throw()
{
    m_maCapturedTexts.insert( pair<QString,QString>( p_qsTextName, p_qsTextValue ) );
}

tiActionCapturedTexts cAction::capturedTextsBegin() const throw()
{
    return m_maCapturedTexts.begin();
}

tiActionCapturedTexts cAction::capturedTextsEnd() const throw()
{
    return m_maCapturedTexts.end();
}
