#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <cstdlib>

#include "lara.h"
#include "logdatasource.h"

cLogDataSource::cLogDataSource( const QString &p_qsInputDir, const QString &p_qsFiles )
        throw()
{
    cTracer obTracer( &g_obLogger, "cLogDataSource::cLogDataSource",
                      QString( "inputdir: \"%1\", files: \"%2\"" ).arg( p_qsInputDir ).arg( p_qsFiles ).toStdString() );

    parseFileNames( p_qsInputDir, p_qsFiles );
    prepareFiles();
}

cLogDataSource::~cLogDataSource()
{
    cTracer  obTracer( &g_obLogger, "cLogDataSource::~cLogDataSource" );

    for( int i = 0; i < m_slTempFiles.size(); i++ )
    {
        QFile::remove( m_slTempFiles.at( i ) );
    }
}

QStringList cLogDataSource::logFileList() const throw()
{
    return m_slTempFiles;
}

QStringList cLogDataSource::origFileList() const throw()
{
    return m_slOrigFiles;
}

void cLogDataSource::parseFileNames( const QString &p_qsInputDir, const QString &p_qsFiles )
        throw()
{
    cTracer obTracer( &g_obLogger, "cLogDataSource::parseFileNames",
                      QString( "inputdir: \"%1\", files: \"%2\"" ).arg( p_qsInputDir ).arg( p_qsFiles ).toStdString() );

    // The parameter p_qsFiles is a simple string that can contain multiple file names,
    // separated by a ';' character, so first it needs to be split up into a list.
    QStringList slFilesWithWildCards = p_qsFiles.split( ';', QString::SkipEmptyParts );

    // The slFilesWithWildCards is a list of string items containing wild-cards.
    // Each of these must be appended to the p_qsInputDir string, and the wild-cards
    // must be resolved. This will potentially result in multiple real file names for
    // each item in the slFiles list. The result will be a new list that contains one
    // item for each real file (m_slOrigFiles).
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
            m_slOrigFiles.push_back( obDir.absoluteFilePath( slEntryList.at( j ) ) );
        }
    }
}

void cLogDataSource::prepareFiles()
        throw()
{
    cTracer  obTracer( &g_obLogger, "cLogDataSource::prepareFiles" );

    for( int i = 0; i < m_slOrigFiles.size(); i++ )
    {
        try
        {
            QString qsFileName = m_slOrigFiles.at( i );
            if( qsFileName.indexOf( ".zip", qsFileName.size() - 4, Qt::CaseInsensitive ) != -1 )
            {
                m_slTempFiles.push_back( unzipFile( qsFileName ) );
                continue;
            }

            if( qsFileName.indexOf( ".gz", qsFileName.size() - 3, Qt::CaseInsensitive ) != -1 )
            {
                m_slTempFiles.push_back( gunzipFile( qsFileName ) );
                continue;
            }

            if( qsFileName.indexOf( "sysError" ) != -1 )
            {
                m_slTempFiles.push_back( decodeFile( qsFileName ) );
                continue;
            }

            m_slTempFiles.push_back( copyFile( qsFileName ) );
        }
        catch( cSevException &e )
        {
            g_obLogger << e;
        }
    }
}

QString cLogDataSource::unzipFile( const QString &p_qsFileName )
        throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cLogDataSource::unzipFile", p_qsFileName.toStdString() );

    QString qsTempFileName = copyFile( p_qsFileName );
    QString qsCommand = QString( "unzip -o -d %1 %2" ).arg( g_poPrefs->tempDir() ).arg( qsTempFileName );
    if( system( qsCommand.toAscii() ) != 0 ) throw cSevException( cSeverity::ERROR, "Error in unzip command" );

    QFile::remove( qsTempFileName ); // Remove the .zip file since unzip leaves it there

    qsTempFileName.chop( 4 );  // Remove the ".zip" from file-name
    qsTempFileName.append( ".log" );

    obTracer << qsTempFileName.toStdString();

    return qsTempFileName;
}

QString cLogDataSource::gunzipFile( const QString &p_qsFileName )
        throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cLogDataSource::gunzipFile", p_qsFileName.toStdString() );

    QString qsTempFileName = copyFile( p_qsFileName );
    QString qsCommand = "gzip -d -q -f " + qsTempFileName;
    if( system( qsCommand.toAscii() ) != 0 ) throw cSevException( cSeverity::ERROR, "Error in gunzip command" );

    qsTempFileName.chop( 3 );  // Remove the ".gz" from file-name

    obTracer << qsTempFileName.toStdString();

    return qsTempFileName;
}

QString cLogDataSource::copyFile( const QString &p_qsFileName )
        throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cLogDataSource::copyFile", p_qsFileName.toStdString() );

    QString qsTempFileName = g_poPrefs->tempDir();
    if( (qsTempFileName.at( qsTempFileName.length() - 1 ) != '/') &&
        (qsTempFileName.at( qsTempFileName.length() - 1 ) != '\\') )
    {
        qsTempFileName.append( QDir::separator() );
    }
    qsTempFileName.append( p_qsFileName.section( QRegExp( "[/\\\\]" ), -1, -1 ) );

    QFile::remove( qsTempFileName );
    if( !QFile::copy( p_qsFileName, qsTempFileName ) )
    {
        throw cSevException( cSeverity::ERROR, "Cannot copy file " + p_qsFileName.toStdString() + " to " + qsTempFileName.toStdString() );
    }

    obTracer << qsTempFileName.toStdString();

    return qsTempFileName;
}

QString cLogDataSource::decodeFile( const QString &p_qsFileName ) throw( cSevException )
{
    cTracer  obTracer( &g_obLogger, "cLogDataSource::decodeFile", p_qsFileName.toStdString() );

    QString qsTempFileName = copyFile( p_qsFileName );
    QString qsDecodedFileName = qsTempFileName + ".decoded";

    QFile   obCodedFile( qsTempFileName );
    if( !obCodedFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        throw cSevException( cSeverity::ERROR, QString( "%1: %2" ).arg( qsTempFileName ).arg( obCodedFile.errorString() ).toStdString() );
    }

    QFile   obDecodedFile( qsDecodedFileName );
    if( !obDecodedFile.open( QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text ) )
    {
        obCodedFile.close();
        throw cSevException( cSeverity::ERROR, QString( "%1: %2" ).arg( qsDecodedFileName ).arg( obDecodedFile.errorString() ).toStdString() );
    }

    QTextStream srCodedStream( &obCodedFile );
    QTextStream srDecodedStream( &obDecodedFile );
    bool boFirstLine = true;
    for( QString qsCodedLine = srCodedStream.readLine();
         !qsCodedLine.isNull();
         qsCodedLine = srCodedStream.readLine() )
    {
        QStringList slCodedTags = qsCodedLine.split( ',' );
        bool boFirstTag = true;
        for( int i = 0; i < slCodedTags.size(); i++ )
        {
            if( boFirstTag ) boFirstTag = false;
            else srDecodedStream << ",";

            //only need to decode the 5. 9. 10. and 11. tags
            if( boFirstLine || ( i != 5 && i != 9 && i != 10 && i != 11 ) )
            {
                srDecodedStream << slCodedTags.at( i );
            }
            else
            {
                srDecodedStream << decodeString( slCodedTags.at( i ) );
            }
        }
        srDecodedStream << "\n";
        srDecodedStream.flush();

        if( boFirstLine ) boFirstLine = false;
    }

    obCodedFile.close();
    QFile::remove( qsTempFileName );

    obDecodedFile.close();

    obTracer << qsTempFileName.toStdString();

    return qsDecodedFileName;
}

QString cLogDataSource::decodeString( const QString &p_qsInput ) throw()
{
    QByteArray     baLine = QByteArray::fromBase64( p_qsInput.toAscii() );

    unsigned char  poKeyArray[8] = {115,3,23,8,120,6,22,111};
    QString        qsDecodedString = "";

    char poDecodedChar[2] = " ";
    for( int i = 0; i < baLine.length(); i++ )
    {
        poDecodedChar[0] = baLine.at( i ) ^ poKeyArray[i%8];
        qsDecodedString.append( poDecodedChar );
    }

    return qsDecodedString;
}
