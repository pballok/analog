
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
}

cActionDefList::tiPatternList cActionDefList::patternBegin() const throw()
{
    return m_vePatternList.begin();
}

cActionDefList::tiPatternList cActionDefList::patternEnd() const throw()
{
    return m_vePatternList.end();
}

cActionDefList::tiSingleLinerList cActionDefList::singleLinerBegin() const throw()
{
    return m_veSingleLinerList.begin();
}

cActionDefList::tiSingleLinerList cActionDefList::singleLinerEnd() const throw()
{
    return m_veSingleLinerList.end();
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

    QDomElement obRootElement = m_poActionsDoc->documentElement();
    m_obTimeStampRegExp.setPattern( obRootElement.attribute( "timestamp_regexp", "" ) );
    for( int i = cTimeStampPart::MIN + 1; i < cTimeStampPart::MAX; i++ )
    {
        m_poTimeStampParts[i - 1] = cTimeStampPart::fromStr( obRootElement.attribute( QString( "param_%1" ).arg( i ), "MIN" ).toAscii() );
    }

    for( QDomElement obElem = obRootElement.firstChildElement();
         !obElem.isNull();
         obElem = obElem.nextSiblingElement() )
    {
        if( obElem.tagName() == "pattern" )
        {
            m_vePatternList.push_back( cPattern( &obElem ) );
            continue;
        }

        if( obElem.tagName() == "single_liner" )
        {
            m_veSingleLinerList.push_back( cActionDefSingleLiner( &obElem ) );
            continue;
        }
    }
}
