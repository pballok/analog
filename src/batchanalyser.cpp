#include <QFile>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "lara.h"
#include "batchanalyser.h"
#include "loganalyser.h"
#include "outputcreator.h"

using namespace std;

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
    for( unsigned int i = 0; i < m_veAnalyseDefs.size(); i++ )
    {
        tsAnalyseDefinition  suAnalysis = m_veAnalyseDefs.at( i );
        g_obLogger << cSeverity::INFO << "Starting to analyse " << suAnalysis.qsName.toStdString();

        QString qsFullDirPrefix = m_qsDirPrefix + "/" + suAnalysis.qsName;
        cOutputCreator  *poOC = new cOutputCreator( qsFullDirPrefix );

        for( tiAttributes itAttrib = suAnalysis.maAttributes.begin();
             itAttrib != suAnalysis.maAttributes.end();
             itAttrib++ )
        {
            poOC->addAttribute( itAttrib->first, itAttrib->second );
        }

        for( unsigned int l = 0; l < suAnalysis.veInputLogs.size(); l++ )
        {
            cLogAnalyser  obAnalyser( qsFullDirPrefix, suAnalysis.veInputLogs.at( l ).qsFiles, suAnalysis.veInputLogs.at( l ).qsActionDefFile, poOC );
            obAnalyser.analyse();
        }

        try
        {
            poOC->generateActionSummary();
            poOC->generateActionList();
            poOC->uploadActionSummary();
            poOC->uploadActionList();
        } catch( cSevException &e )
        {
            g_obLogger << e;
        }

        delete poOC;

        g_obLogger << cSeverity::INFO << "Finished analysing " << suAnalysis.qsName.toStdString();
    }
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

    m_qsDirPrefix = obRootElement.attribute( "dir_prefix", "" );

    for( QDomElement obElem = obRootElement.firstChildElement( "analysis" );
         !obElem.isNull();
         obElem = obElem.nextSiblingElement( "analysis" ) )
    {
        tsAnalyseDefinition  suAnalyseDef;
        suAnalyseDef.qsName = obElem.attribute( "name", "" );
        for( QDomElement obLogElem = obElem.firstChildElement( "input_log" );
             !obLogElem.isNull();
             obLogElem = obLogElem.nextSiblingElement( "input_log" ) )
        {
            tsInputLogDefinition suInputLog;
            suInputLog.qsFiles = obLogElem.attribute( "files", "" );
            suInputLog.qsActionDefFile = obLogElem.attribute( "action_def" );
            suAnalyseDef.veInputLogs.push_back( suInputLog );
        }

        for( QDomElement obAttribElem = obElem.firstChildElement( "attribute" );
             !obAttribElem.isNull();
             obAttribElem = obAttribElem.nextSiblingElement( "attribute" ) )
        {
            suAnalyseDef.maAttributes.insert( pair<QString,QString>( obAttribElem.attribute( "name" ), obAttribElem.attribute( "value" ) ) );
        }

        m_veAnalyseDefs.push_back( suAnalyseDef );
    }
}
