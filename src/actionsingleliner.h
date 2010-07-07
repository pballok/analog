#ifndef ACTIONSINGLELINER_H
#define ACTIONSINGLELINER_H

#include <QString>

#include "action.h"

class cActionSingleLiner : public cAction
{
public:
    cActionSingleLiner();
    ~cActionSingleLiner();

private:
    QString  m_qsPattern;
};

#endif // ACTIONSINGLELINER_H
