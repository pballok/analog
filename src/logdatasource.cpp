#include <QDir>
#include <QFile>
#include <QString>
#include <QStringList>

#include "logdatasource.h"
#include "qtframework.h"

cLogDataSource::cLogDataSource( const QString &p_qsInputDir, const QString &p_qsFiles )
{
    string stParams = "inputdir: \"" + p_qsInputDir.toStdString();
    stParams += "\", files: \"" + p_qsFiles.toStdString();
    stParams += "\"";
    cTracer  obTracer( "cLogDataSource::cLogDataSource",  stParams );

    QStringList slOriginalFiles = parseFileNames( p_qsInputDir, p_qsFiles );
    prepareFiles( slOriginalFiles );
}

cLogDataSource::~cLogDataSource()
{
    for( int i = 0; i < m_slTempFiles.size(); i++ )
    {
        QFile::remove( m_slTempFiles.at( i ) );
    }
}

QStringList cLogDataSource::parseFileNames( const QString &p_qsInputDir, const QString &p_qsFiles ) throw()
{
    string stParams = "inputdir: \"" + p_qsInputDir.toStdString();
    stParams += "\", files: \"" + p_qsFiles.toStdString();
    stParams += "\"";
    cTracer  obTracer( "cLogDataSource::parseFileNames",  stParams );

    // The parameter p_qsFiles is a simple string that can contain multiple file names,
    // separated by a ';' character, so first it needs to be split up into a list.
    QStringList slFilesWithWildCards = p_qsFiles.split( ';', QString::SkipEmptyParts );

    // The slFilesWithWildCards is a list of string items containing wild-cards.
    // Each of these must be appended to the p_qsInputDir string, and the wild-cards
    // must be resolved. This will potentially result in multiple real file names for
    // each item in the slFiles list. The result will be a new list that contains one
    // item for each real file (slRealFiles).
    QStringList  slRealFiles;
    QString      qsInputDir = p_qsInputDir;
    if( (qsInputDir.at( qsInputDir.length() - 1 ) != '/') && (qsInputDir.at( qsInputDir.length() - 1 ) != '\\') )
    {
        qsInputDir.append( QDir::separator() );
    }
    for( int i = 0; i < slFilesWithWildCards.size(); i++ )
    {
        // Each entry in slFilesWithWildCards can contain additional subdirectories, not only
        // file-names. Because of this, first the full path mast be constructed by appending
        // the file-name to the InputDir, then it has to be split again to two parts: a path
        // and a file-name. These are then passed to the QDir object to retrieve the list
        // of files matching the wild-cards specified in the original slFilesWithWildCards item.
        QString qsPath = qsInputDir + slFilesWithWildCards.at( i );
        QString qsFileFilter = qsPath.section( QRegExp( "[/\\\\]" ), -1, -1 );
        qsPath = qsPath.section( QRegExp( "[/\\\\]" ), 0, -2 );

        QDir obDir( qsPath, qsFileFilter );
        QStringList slEntryList  = obDir.entryList( QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot );
        for( int j = 0; j < slEntryList.size(); j++ )
        {
            slRealFiles.push_back( obDir.absoluteFilePath( slEntryList.at( j ) ) );
        }
    }

    return slRealFiles;
}

void cLogDataSource::prepareFiles( const QStringList &p_slFiles ) throw()
{
    cTracer  obTracer( "cLogDataSource::prepareFiles" );

    for( int i = 0; i < p_slFiles.size(); i++ )
    {
        try
        {
            if( p_slFiles.at( i ).indexOf( ".zip", p_slFiles.at( i ).size() - 4, Qt::CaseInsensitive ) != -1 )
            {
                unzipFile( p_slFiles.at( i ) );
                continue;
            }

            if( p_slFiles.at( i ).indexOf( ".gz", p_slFiles.at( i ).size() - 3, Qt::CaseInsensitive ) != -1 )
            {
                gunzipFile( p_slFiles.at( i ) );
                continue;
            }

            copyFile( p_slFiles.at( i ) );
        }
        catch( cSevException &e )
        {
            g_obLogger << e.severity();
            g_obLogger << e.what();
            g_obLogger << cQTLogger::EOM;
        }
    }
}

void cLogDataSource::unzipFile( const QString &p_stFileName ) throw( cSevException )
{

}

void cLogDataSource::gunzipFile( const QString &p_stFileName ) throw( cSevException )
{

}

void cLogDataSource::copyFile( const QString &p_stFileName ) throw( cSevException )
{
    cTracer  obTracer( "cLogDataSource::copyFile", p_stFileName.toStdString() );

    QString qsTempFileName = g_poPrefs->getTempDir();
    if( (qsTempFileName.at( qsTempFileName.length() - 1 ) != '/') &&
        (qsTempFileName.at( qsTempFileName.length() - 1 ) != '\\') )
    {
        qsTempFileName.append( QDir::separator() );
    }
    qsTempFileName.append( p_stFileName.section( QRegExp( "[/\\\\]" ), -1, -1 ) );

    QFile::remove( qsTempFileName );
    if( !QFile::copy( p_stFileName, qsTempFileName ) )
    {
        throw cSevException( cSeverity::ERROR, "Cannot copy file " + p_stFileName.toStdString() + " to " + qsTempFileName.toStdString() );
    }

    m_slTempFiles.push_back( qsTempFileName );

    obTracer << qsTempFileName.toStdString();
}
