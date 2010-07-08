#ifndef ACTIONSINGLELINER_H
#define ACTIONSINGLELINER_H

#include <QString>
#include <QDomElement>

#include "action.h"

class cActionSingleLiner : public cAction
{
public:
    cActionSingleLiner();
    cActionSingleLiner( QDomElement *p_poElem );
    ~cActionSingleLiner();

    QString  pattern() const throw();

private:
    QString  m_qsPattern;
};

#endif // ACTIONSINGLELINER_H
