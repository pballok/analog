#ifndef ACTION_H
#define ACTION_H

#include <QString>

class cAction
{
public:
    cAction();
    ~cAction();

    QString  name() const throw();
    void     setName( const QString &p_qsName ) throw();

private:
    QString  m_qsName;
    // Occurrance Time
    // File id
    // Line number
    // result
    // upload
};

#endif // ACTION_H
