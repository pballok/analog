#include <iostream>
#include <iomanip>
#include <sstream>

#include "qtlogger.h"


cQTLogger::cQTLogger()
{
    init();
}

cQTLogger::~cQTLogger()
{
}

void cQTLogger::init( void ) throw ()
{
    m_enMinConsoleSeverityLevel = cSeverity::NONE;
    m_enNextSeverityLevel       = cSeverity::NONE;
}

void cQTLogger::setMinSeverityLevels(
    const cSeverity::teSeverity p_enConsoleLevel = cSeverity::DEBUG )
    throw()
{
    m_enMinConsoleSeverityLevel = p_enConsoleLevel;
}

void cQTLogger::getMinSeverityLevels(
    cSeverity::teSeverity *p_poConsoleLevel ) const
    throw()
{
    *p_poConsoleLevel = m_enMinConsoleSeverityLevel;
}

void cQTLogger::logMessage( const cSeverity::teSeverity  p_enLevel,
                            const string                &p_stMessage )
     throw()
{
    try
    {
        if( p_enLevel <= m_enMinConsoleSeverityLevel )
            logToConsole( p_enLevel, p_stMessage );
    }
    catch( cSevException &e )
    {
        logToConsole( e.severity(), e.what() );
    }
}

void cQTLogger::logToConsole( const cSeverity::teSeverity  p_enLevel,
                              const string                &p_stMessage )
     throw()
{
    time_t     ttTime;
    struct tm *poTm;
    time( &ttTime );
    poTm = localtime( &ttTime );

    cerr << setw(2) << setfill('0') << poTm->tm_mday << ".";
    cerr << setw(2) << setfill('0') << poTm->tm_mon + 1 << ".";
    cerr << poTm->tm_year + 1900 << " ";
    cerr << poTm->tm_hour << ":";
    cerr << setw(2) << setfill('0') << poTm->tm_min << ":";
    cerr << setw(2) << setfill('0') << poTm->tm_sec << " ";
    cerr << cSeverity::toStr( p_enLevel );
    if( p_stMessage != "" ) cerr << " " << p_stMessage;
    cerr << endl << flush;
}
