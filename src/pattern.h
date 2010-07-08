#ifndef PATTERN_H
#define PATTERN_H

#include <QString>
#include <QDomElement>
#include <QRegExp>

class cPattern
{
public:
    cPattern();
    cPattern( const QDomElement *p_poElem );
    ~cPattern();

    QString  name() const throw();
    QString  pattern() const throw();

private:

    QString  m_qsName;
    QRegExp  m_obRegExp;
};

#endif // PATTERN_H
