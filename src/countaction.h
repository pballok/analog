#ifndef COUNTACTION_H
#define COUNTACTION_H

#include <QString>
#include <QDomElement>
#include <vector>

class cCountAction
{
public:

    typedef std::vector<QString>              tvActionsToCount;
    typedef tvActionsToCount::const_iterator  tiActionsToCount;

    cCountAction();
    cCountAction( const QDomElement *p_poElem );
    ~cCountAction();

    QString           name()                const throw();

    tiActionsToCount  actionsToCountBegin() const throw();
    tiActionsToCount  actionsToCountEnd()   const throw();

private:
    QString           m_qsName;
    tvActionsToCount  m_veActionsToCount;

    void             init()                 throw();
};

#endif // COUNTACTION_H
