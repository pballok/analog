#include <QStringList>
#include <QFile>

#include <logger.h>
#include <preferences.h>

#include <logdatasource.h>

#include "datasourcetest.h"

extern cLogger       g_obLogger;
extern cPreferences *g_poPrefs;

cDataSourceTest::cDataSourceTest() throw() : cUnitTest( "Data Source" )
{
}

cDataSourceTest::~cDataSourceTest() throw()
{
}

void cDataSourceTest::run() throw()
{
    testDataSource();
}

void cDataSourceTest::testDataSource() throw()
{
    printNote( "DATA SOURCE TESTS" );

    try
    {
        cLogDataSource  *poDS = new cLogDataSource( g_poPrefs->inputDir(), "multiple_files/test1/test*.gz" );

        QStringList  slLogFiles = poDS->logFileList();
        testCase( "Gzipped files: Prepared Input Log Count", 2, slLogFiles.size() );
        testCase( "Gzipped files: Prepared Log 1 File Name", QString("%1/test1.log" ).arg( g_poPrefs->tempDir() ).toStdString(), slLogFiles.at( 0 ).toStdString() );
        testCase( "Gzipped files: Prepared Log 2 File Name", QString("%1/test2.log" ).arg( g_poPrefs->tempDir() ).toStdString(), slLogFiles.at( 1 ).toStdString() );

        testCase( "Gzipped files: Prepared Log 1 File exists", true, QFile::exists( slLogFiles.at( 0 ) ) );
        testCase( "Gzipped files: Prepared Log 2 File exists", true, QFile::exists( slLogFiles.at( 1 ) ) );

        QStringList  slOrigFiles = poDS->origFileList();
        testCase( "Gzipped files: Original Input Log Count", 2, slOrigFiles.size() );
        testCase( "Gzipped files: Original Log 1 File Name", QString("%1/multiple_files/test1/test1.log.gz" ).arg( g_poPrefs->inputDir() ).toStdString(), slOrigFiles.at( 0 ).toStdString() );
        testCase( "Gzipped files: Original Log 2 File Name", QString("%1/multiple_files/test1/test2.log.gz" ).arg( g_poPrefs->inputDir() ).toStdString(), slOrigFiles.at( 1 ).toStdString() );

        delete poDS;

        testCase( "Gzipped files: Prepared Log 1 File exists after delete", false, QFile::exists( slLogFiles.at( 0 ) ) );
        testCase( "Gzipped files: Prepared Log 2 File exists after delete", false, QFile::exists( slLogFiles.at( 1 ) ) );

        poDS = new cLogDataSource( g_poPrefs->inputDir(), "multiple_files/test1/test*.log" );

        slLogFiles = poDS->logFileList();
        testCase( "Copied files: Prepared Input Log Count", 1, slLogFiles.size() );
        testCase( "Copied files: Prepared Log 1 File Name", QString("%1/test.log" ).arg( g_poPrefs->tempDir() ).toStdString(), slLogFiles.at( 0 ).toStdString() );

        testCase( "Copied files: Prepared Log 1 File exists", true, QFile::exists( slLogFiles.at( 0 ) ) );

        slOrigFiles = poDS->origFileList();
        testCase( "Copied files: Original Input Log Count", 1, slOrigFiles.size() );
        testCase( "Copied files: Original Log 1 File Name", QString("%1/multiple_files/test1/test.log" ).arg( g_poPrefs->inputDir() ).toStdString(), slOrigFiles.at( 0 ).toStdString() );

        delete poDS;

        testCase( "Copied files: Prepared Log 1 File exists after delete", false, QFile::exists( slLogFiles.at( 0 ) ) );

        poDS = new cLogDataSource( g_poPrefs->inputDir(), "nonexisting_file_name" );

        slLogFiles = poDS->logFileList();
        testCase( "Non-existing files: Prepared Input Log Count", 0, slLogFiles.size() );

        slOrigFiles= poDS->origFileList();
        testCase( "Non-existing files: Original Input Log Count", 0, slOrigFiles.size() );

        delete poDS;

        poDS = new cLogDataSource( "nonexisting_path", "multiple_files/test1/test*.gz" );

        slLogFiles = poDS->logFileList();
        testCase( "Non-existing path: Prepared Input Log Count", 0, slLogFiles.size() );

        slOrigFiles= poDS->origFileList();
        testCase( "Non-existing path: Original Input Log Count", 0, slOrigFiles.size() );

        delete poDS;

    } catch( cSevException &e )
    {
        g_obLogger << e;
        m_uiFailedNum++;
    }
}
