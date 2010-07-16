#ifndef ACTION_H
#define ACTION_H

#include <QString>

#include "actiondef.h"

class cAction
{
public:
    cAction( const QString &p_qsName = "", const QString &p_qsTimeStamp = "",
             const unsigned int p_uiFileId = 0, const unsigned long p_ulLineNum = 0,
             const cActionResult::teResult p_enResult = cActionResult::MIN,
             const cActionUpload::teUpload p_enUpload = cActionUpload::MIN );
    ~cAction();

    QString                  name() const throw();
    QString                  timeStamp() const throw();
    unsigned int             fileId() const throw();
    unsigned long            lineNum() const throw();
    cActionResult::teResult  result() const throw();
    cActionUpload::teUpload  upload() const throw();

private:
    QString                  m_qsName;
    QString                  m_qsTimeStamp;
    unsigned int             m_uiFileId;
    unsigned long            m_ulLineNum;
    cActionResult::teResult  m_enResult;
    cActionUpload::teUpload  m_enUpload;
};

#endif // ACTION_H
