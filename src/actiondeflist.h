#ifndef ACTIONDEFLIST_H
#define ACTIONDEFLIST_H

#include <QString>
#include <QDomDocument>
#include <vector>

#include "actiondefsingleliner.h"
#include "pattern.h"
#include "sevexception.h"

using namespace std;

class cActionDefList
{
public:
    typedef vector<cPattern*>                  tvPatternList;
    typedef tvPatternList::const_iterator      tiPatternList;

    typedef vector<cActionDefSingleLiner*>     tvSingleLinerList;
    typedef tvSingleLinerList::const_iterator  tiSingleLinerList;

    cActionDefList( const QString &p_qsActionDefFile ) throw();
    ~cActionDefList() throw();

private:
    const QString      m_qsSchemaFileName;
    QDomDocument      *m_poActionsDoc;
    tvPatternList      m_vePatternList;
    tvSingleLinerList  m_veSingleLinerList;

    void validateActionDef( const QString &p_qsActionDefFile ) throw( cSevException );
    void parseActionDef() throw( cSevException );
};

#endif // ACTIONDEFLIST_H
