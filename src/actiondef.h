#ifndef ACTIONDEF_H
#define ACTIONDEF_H

#include <QString>
#include <QDomElement>

class cActionResult
{
public:
    enum teResult
    {
        MIN = 0,
        OK,
        FAILED,
        MAX
    };

    static const char *toStr( teResult p_enResult )
    {
        switch( p_enResult )
        {
            case OK:     return "OK";     break;
            case FAILED: return "FAILED"; break;
            default:     return "INVALID";
        }
    }

    static teResult fromStr( const char* p_poStr )
    {
        if( strcmp( p_poStr, "OK" ) == 0 )     return OK;
        if( strcmp( p_poStr, "FAILED" ) == 0 ) return FAILED;
        return MIN;
    }
};

class cActionUpload
{
public:
    enum teUpload
    {
        MIN = 0,
        OK,
        FAILED,
        ALWAYS,
        NEVER,
        MAX
    };

    static const char *toStr( teUpload p_enUpload )
    {
        switch( p_enUpload )
        {
            case OK:     return "OK";     break;
            case FAILED: return "FAILED"; break;
            case ALWAYS: return "ALWAYS"; break;
            case NEVER:  return "NEVER";  break;
            default:     return "INVALID";
        }
    }

    static teUpload fromStr( const char* p_poStr )
    {
        if( strcmp( p_poStr, "OK" ) == 0 )     return OK;
        if( strcmp( p_poStr, "FAILED" ) == 0 ) return FAILED;
        if( strcmp( p_poStr, "ALWAYS" ) == 0 ) return ALWAYS;
        if( strcmp( p_poStr, "NEVER" ) == 0 )  return NEVER;
        return MIN;
    }
};

class cActionDef
{
public:
    cActionDef();
    cActionDef( const QDomElement *p_poElem );
    virtual ~cActionDef();

    QString                  name()   const throw();
    cActionUpload::teUpload  upload() const throw();


protected:
    QString                  m_qsName;
    cActionUpload::teUpload  m_enUpload;

    virtual void             init()   throw();
};

#endif // ACTIONDEF_H
