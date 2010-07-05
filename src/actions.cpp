#include "actions.h"

#include <QDomDocument>
#include <QFile>

#include "qtframework.h"

cActions::cActions( const QString &p_qsActionDefFile )
        throw()
{
    cTracer  obTracer( "cActions::cActions", p_qsActionDefFile.toStdString() );

    QFile        obActionsFile( p_qsActionDefFile );

    try
    {
        if( !obActionsFile.open( QIODevice::ReadOnly ) )
            throw cSevException( cSeverity::ERROR, "Cannot open Actions file: " + p_qsActionDefFile.toStdString() );

        QDomDocument obActionsDoc( "actions" );
        QString      qsErrorMsg  = "";
        int          inErrorLine = 0;

        if( !obActionsDoc.setContent( &obActionsFile, &qsErrorMsg, &inErrorLine ) )
        {
            obActionsFile.close();
            QString qsMsg = QString( "Parsing Actions file: %1 - Error in line %2: %3" ).arg( p_qsActionDefFile ).arg( inErrorLine ).arg( qsErrorMsg );

            throw cSevException( cSeverity::ERROR, qsMsg.toStdString() );
        }
    }
    catch( cSevException &e )
    {
        obActionsFile.close();

        g_obLogger << e.severity();
        g_obLogger << e.what();
        g_obLogger << cQTLogger::EOM;
    }
}

cActions::~cActions()
        throw()
{
    cTracer  obTracer( "cActions::~cActions" );
}
