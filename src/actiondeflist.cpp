
#include <QFile>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "actiondeflist.h"
#include "qtframework.h"


cActionDefList::cActionDefList( const QString &p_qsActionDefFile )
        throw()
            : m_qsSchemaFileName( "data/laza.xsd" )

{
    cTracer  obTracer( "cActionDefList::cActionDefList", p_qsActionDefFile.toStdString() );

    m_poActionsDoc = new QDomDocument( "actions " );

    try
    {
        validateActionDef( p_qsActionDefFile );
        parseActionDef();
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity();
        g_obLogger << e.what();
        g_obLogger << cQTLogger::EOM;
    }
}

cActionDefList::~cActionDefList()
        throw()
{
    cTracer  obTracer( "cActionDefList::~cActionDefList" );

    delete m_poActionsDoc;

    for( tiPatternList i = m_vePatternList.begin();
         i != m_vePatternList.end();
         i++ )
        delete *i;

    for( tiSingleLinerList i = m_veSingleLinerList.begin();
         i != m_veSingleLinerList.end();
         i++ )
        delete *i;
}

void cActionDefList::validateActionDef( const QString &p_qsActionDefFile ) throw( cSevException )
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

void cActionDefList::parseActionDef() throw( cSevException )
{
    cTracer  obTracer( "cActionDefList::parseActionDef" );

    for( QDomElement obElem = m_poActionsDoc->documentElement().firstChildElement();
         !obElem.isNull();
         obElem = obElem.nextSiblingElement() )
    {
        if( obElem.tagName() == "pattern" )
        {
            cPattern *poPattern = new cPattern( &obElem );
            m_vePatternList.push_back( poPattern );
            continue;
        }

        if( obElem.tagName() == "single_liner" )
        {
            cActionDefSingleLiner  *poAction = new cActionDefSingleLiner( &obElem );
            m_veSingleLinerList.push_back( poAction );
            continue;
        }
    }
}
