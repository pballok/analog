#include <QFile>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "lara.h"
#include "batchanalyser.h"

cBatchAnalyser::cBatchAnalyser( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw()
{
    cTracer  obTracer( &g_obLogger, "cBatchAnalyser::cBatchAnalyser", p_qsBatchDefFile.toStdString() );

    m_poBatchDoc = new QDomDocument( "batch" );

    try
    {
        validateBatchDef( p_qsBatchDefFile, p_qsSchemaFile );
        parseBatchDef();
    }
    catch( cSevException &e )
    {
        g_obLogger << e;
    }
}

cBatchAnalyser::~cBatchAnalyser()
        throw()
{
    cTracer  obTracer( &g_obLogger, "cBatchAnalyser::~cBatchAnalyser" );

    delete m_poBatchDoc;
}

void cBatchAnalyser::analyse() throw()
{

}

void cBatchAnalyser::validateBatchDef( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cBatchAnalyser::validateBatchDef", p_qsBatchDefFile.toStdString() );

    QFile obBatchFile( p_qsBatchDefFile );

    try
    {
        if( !obBatchFile.open( QIODevice::ReadOnly ) )
        {
            throw cSevException( cSeverity::ERROR, QString( "Cannot open Batch file: %1" ).arg( p_qsBatchDefFile ).toStdString() );
        }

        QXmlSchema obSchema;
        obSchema.load( p_qsSchemaFile );

        if( !obSchema.isValid() )
        {
            throw cSevException( cSeverity::ERROR, QString( "Schema %1 is not valid" ).arg( p_qsSchemaFile ).toStdString() );
        }

        QXmlSchemaValidator obValidator( obSchema );
        if( !obValidator.validate( &obBatchFile, QUrl::fromLocalFile( p_qsBatchDefFile ) ) )
        {
            throw cSevException( cSeverity::ERROR,
                                 QString( "Batch definition file %1 is not valid according to Schema %2" ).arg( p_qsBatchDefFile ).arg( p_qsSchemaFile ).toStdString() );
        }

        QString      qsErrorMsg  = "";
        int          inErrorLine = 0;
        obBatchFile.seek( 0 );
        if( !m_poBatchDoc->setContent( &obBatchFile, &qsErrorMsg, &inErrorLine ) )
        {
            throw cSevException( cSeverity::ERROR,
                                 QString( "Parsing Batch file: %1 - Error in line %2: %3" ).arg( p_qsBatchDefFile ).arg( inErrorLine ).arg( qsErrorMsg ).toStdString() );
        }

        obBatchFile.close();
    }
    catch( cSevException &e )
    {
        obBatchFile.close();

        throw e;
    }
}

void cBatchAnalyser::parseBatchDef() throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cBatchAnalyser::parseBatchDef" );

    QDomElement obRootElement = m_poBatchDoc->documentElement();

    for( QDomElement obElem = obRootElement.firstChildElement();
         !obElem.isNull();
         obElem = obElem.nextSiblingElement() )
    {
        if( obElem.tagName() == "analysis" )
        {
            continue;
        }
    }
}
