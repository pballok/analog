#include "actions.h"

#include <QFile>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "qtframework.h"

cActions::cActions( const QString &p_qsActionDefFile )
        throw()
            : m_qsSchemaFileName( "data/laza.xsd" )

{
    cTracer  obTracer( "cActions::cActions", p_qsActionDefFile.toStdString() );

    m_poActionsDoc = new QDomDocument( "actions " );

    try
    {
        validateActionDef( p_qsActionDefFile );
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity();
        g_obLogger << e.what();
        g_obLogger << cQTLogger::EOM;
    }
}

cActions::~cActions()
        throw()
{
    cTracer  obTracer( "cActions::~cActions" );

    delete m_poActionsDoc;
}

void cActions::validateActionDef( const QString &p_qsActionDefFile ) throw( cSevException )
{
    cTracer  obTracer( "cActions::validateActionDef", p_qsActionDefFile.toStdString() );

    QFile obActionsFile( p_qsActionDefFile );

    try
    {
        if( !obActionsFile.open( QIODevice::ReadOnly ) )
        {
            QString qsMsg = QString( "Cannot open Actions file: %1" ).arg( p_qsActionDefFile );
            throw cSevException( cSeverity::ERROR, qsMsg.toStdString() );
        }

        QXmlSchema obSchema;
        obSchema.load( m_qsSchemaFileName );

        if( !obSchema.isValid() )
        {
            QString qsMsg =  QString( "Schema %1 is not valid" ).arg( m_qsSchemaFileName );
            throw cSevException( cSeverity::ERROR, qsMsg.toStdString() );
        }

        QXmlSchemaValidator obValidator( obSchema );
        if( !obValidator.validate( &obActionsFile, QUrl::fromLocalFile( p_qsActionDefFile ) ) )
        {
            QString qsMsg =  QString( "Action definition file %1 is not valid according to Schema %2" ).arg( p_qsActionDefFile ).arg( m_qsSchemaFileName );
            throw cSevException( cSeverity::ERROR, qsMsg.toStdString() );
        }

        QString      qsErrorMsg  = "";
        int          inErrorLine = 0;
        obActionsFile.seek( 0 );
        if( !m_poActionsDoc->setContent( &obActionsFile, &qsErrorMsg, &inErrorLine ) )
        {
            QString qsMsg = QString( "Parsing Actions file: %1 - Error in line %2: %3" ).arg( p_qsActionDefFile ).arg( inErrorLine ).arg( qsErrorMsg );
            throw cSevException( cSeverity::ERROR, qsMsg.toStdString() );
        }

        obActionsFile.close();
    }
    catch( cSevException &e )
    {
        obActionsFile.close();

        throw e;
    }
}
