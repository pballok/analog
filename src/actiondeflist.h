#ifndef ACTIONDEFLIST_H
#define ACTIONDEFLIST_H

#include <QString>
#include <QDomDocument>
#include <QRegExp>
#include <vector>

#include "actiondefsingleliner.h"
#include "pattern.h"
#include "sevexception.h"

using namespace std;

class cTimeStampPart
{
public:
    enum teTimeStampPart
    {
        MIN = 0,
        YEAR,
        MONTH,
        DAY,
        HOUR,
        MINUTE,
        SECOND,
        MSECOND,
        MAX
    };

    static const char *toStr( teTimeStampPart p_enPart )
    {
        switch( p_enPart )
        {
            case YEAR:    return "YEAR";    break;
            case MONTH:   return "MONTH";   break;
            case DAY:     return "DAY";     break;
            case HOUR:    return "HOUR";    break;
            case MINUTE:  return "MINUTE";  break;
            case SECOND:  return "SECOND";  break;
            case MSECOND: return "MSCEOND"; break;
            default:      return "INVALID";
        }
    }

    static teTimeStampPart fromStr( const char* p_poStr )
    {
        if( strcmp( p_poStr, "YEAR" ) == 0 )    return YEAR;
        if( strcmp( p_poStr, "MONTH" ) == 0 )   return MONTH;
        if( strcmp( p_poStr, "DAY" ) == 0 )     return DAY;
        if( strcmp( p_poStr, "HOUR" ) == 0 )    return HOUR;
        if( strcmp( p_poStr, "MINUTE" ) == 0 )  return MINUTE;
        if( strcmp( p_poStr, "SECOND" ) == 0 )  return SECOND;
        if( strcmp( p_poStr, "MSCEOND" ) == 0 ) return MSECOND;
        return MIN;
    }
};

class cActionDefList
{
public:
    typedef vector<cPattern>                   tvPatternList;
    typedef tvPatternList::const_iterator      tiPatternList;

    typedef vector<cActionDefSingleLiner>      tvSingleLinerList;
    typedef tvSingleLinerList::const_iterator  tiSingleLinerList;

    cActionDefList( const QString &p_qsActionDefFile ) throw();
    ~cActionDefList() throw();

    tiPatternList      patternBegin() const throw();
    tiPatternList      patternEnd() const throw();
    tiSingleLinerList  singleLinerBegin() const throw();
    tiSingleLinerList  singleLinerEnd() const throw();

private:
    const QString                    m_qsSchemaFileName;
    QDomDocument                    *m_poActionsDoc;
    QRegExp                          m_obTimeStampRegExp;
    cTimeStampPart::teTimeStampPart  m_poTimeStampParts[cTimeStampPart::MAX - 1];
    tvPatternList                    m_vePatternList;
    tvSingleLinerList                m_veSingleLinerList;

    void validateActionDef( const QString &p_qsActionDefFile ) throw( cSevException );
    void parseActionDef() throw( cSevException );
};

#endif // ACTIONDEFLIST_H
