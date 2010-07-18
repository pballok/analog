#ifndef PATTERN_H
#define PATTERN_H

#include <QString>
#include <QStringList>
#include <QDomElement>
#include <QRegExp>

class cPattern
{
public:
    cPattern();
    cPattern( const QDomElement *p_poElem );
    ~cPattern();

    QString      name() const throw();
    QString      pattern() const throw();
    QStringList  captures() const throw();
    QStringList  capturedTexts( const QString &p_qsLogLine ) const throw();

private:

    QString      m_qsName;
    QRegExp      m_obRegExp;
    QStringList  m_slCaptures;
};

#endif // PATTERN_H
