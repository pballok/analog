#ifndef ACTIONDEFSINGLELINER_H
#define ACTIONDEFSINGLELINER_H

#include <QString>
#include <QDomElement>

#include "actiondef.h"

class cActionDefSingleLiner : public cActionDef
{
public:
    cActionDefSingleLiner();
    cActionDefSingleLiner( const QDomElement *p_poElem );
    ~cActionDefSingleLiner();

    QString                  pattern() const throw();
    cActionResult::teResult  result()  const throw();

protected:
    QString                  m_qsPattern;
    cActionResult::teResult  m_enResult;

    virtual void             init()    throw();
};

#endif // ACTIONDEFSINGLELINER_H
