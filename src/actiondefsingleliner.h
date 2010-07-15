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

    QString  pattern() const throw();

private:
    QString  m_qsPattern;
};

#endif // ACTIONDEFSINGLELINER_H
