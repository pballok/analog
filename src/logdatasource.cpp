#include <QStringList>
#include <QFileInfoList>
#include <QDir>

#include "logdatasource.h"
#include "qtframework.h"

cLogDataSource::cLogDataSource( const QString &p_qsInputDir, const QString &p_qsFiles )
{
    string stParams = "inputdir: \"" + p_qsInputDir.toStdString();
    stParams += "\", files: \"" + p_qsFiles.toStdString();
    stParams += "\"";
    cTracer  obTracer( "cLogDataSource::cLogDataSource",  stParams );

    parseFileNames( p_qsInputDir, p_qsFiles );
}

cLogDataSource::~cLogDataSource()
{
}

void cLogDataSource::parseFileNames( const QString &p_qsInputDir, const QString &p_qsFiles )
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


    // Now each item in slRealFiles contain only a file name. These must be replaced
    // with a full, absolute path.
    for( int i = 0; i < slRealFiles.size(); i++ )
    {
        g_obLogger << slRealFiles.at( i ).toStdString() << cQTLogger::EOM;
    }
}
