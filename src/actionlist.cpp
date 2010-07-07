#include "actionlist.h"

#include <QFile>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "qtframework.h"

cActionList::cActionList( const QString &p_qsActionDefFile )
        throw()
            : m_qsSchemaFileName( "data/laza.xsd" )

{
    cTracer  obTracer( "cActionList::cActionList", p_qsActionDefFile.toStdString() );

    m_poActionsDoc = new QDomDocument( "actions " );

    try
    {
        validateActionDef( p_qsActionDefFile );
        readActions();
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity();
        g_obLogger << e.what();
        g_obLogger << cQTLogger::EOM;
    }
}

cActionList::~cActionList()
        throw()
{
    cTracer  obTracer( "cActionList::~cActionList" );

    delete m_poActionsDoc;
}

void cActionList::validateActionDef( const QString &p_qsActionDefFile ) throw( cSevException )
{
    cTracer  obTracer( "cActionList::validateActionDef", p_qsActionDefFile.toStdString() );

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

void cActionList::readActions() throw( cSevException )
{
    cTracer  obTracer( "cActionList::readActions" );

    for( QDomElement obElem = m_poActionsDoc->documentElement().firstChildElement();
         !obElem.isNull();
         obElem = obElem.nextSiblingElement() )
    {
        if( obElem.tagName() == "single_liner" )
        {
            readSingleLiner( &obElem );
            continue;
        }
    }
}

void cActionList::readSingleLiner( QDomElement *p_poElement ) throw( cSevException )
{
    cTracer  obTracer( "cActionList::readSingleLiner" );

    obTracer << p_poElement->attribute( "name" ).toStdString();
}
