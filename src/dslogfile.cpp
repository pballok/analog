#include "dslogfile.h"

cDSLogFile::cDSLogFile() : QObject()
{
    m_obFile.setFileName( "" );
}

cDSLogFile::cDSLogFile( const QString &p_qsFileName ): QObject()
{
    openFile( p_qsFileName );
}

void cDSLogFile::openFile( const QString &p_qsFileName )
{
    m_obFile.setFileName( p_qsFileName );
}

QString cDSLogFile::line( unsigned int p_uiLine ) const
{
    return QString( "This is line %1" ).arg( p_uiLine );
}
