#include "logtablemodel.h"

cLogTableModel::cLogTableModel( QObject *p_poParent ) : QAbstractTableModel( p_poParent )
{
    m_obFile.setFileName( "" );
    m_uiNumLines = 0;
}

cLogTableModel::cLogTableModel( const QString &p_qsFileName, QObject *p_poParent ): QAbstractTableModel( p_poParent )
{
    openFile( p_qsFileName );
}

void cLogTableModel::openFile( const QString &p_qsFileName )
{
    m_obFile.setFileName( p_qsFileName );
}

QString cLogTableModel::line( unsigned int p_uiLine ) const
{
    return QString( "This is line %1" ).arg( p_uiLine );
}
