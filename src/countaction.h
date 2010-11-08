#ifndef COUNTACTION_H
#define COUNTACTION_H

#include <QString>
#include <QDomElement>

class cCountAction
{
public:
    cCountAction();
    cCountAction( const QDomElement *p_poElem );
    ~cCountAction();

    QString  name() const throw();
    QString  action() const throw();

private:
    QString  m_qsName;
    QString  m_qsAction;
};

#endif // COUNTACTION_H
