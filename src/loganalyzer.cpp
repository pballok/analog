#include <QDir>

#include "loganalyzer.h"
#include "qtframework.h"

cLogAnalyzer::cLogAnalyzer( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions )
        throw()
{
    string stParams = "prefix: \"" + p_qsPrefix.toStdString();
    stParams += "\", files: \"" + p_qsFiles.toStdString();
    stParams += "\", actions: \"" + p_qsActions.toStdString();
    stParams += "\"";
    cTracer  obTracer( "cLogAnalyser::cLogAnalyser", stParams );

    QString qsInputDir = g_poPrefs->getInputDir();
    qsInputDir += QDir::separator();
    qsInputDir += p_qsPrefix;
    qsInputDir += QDir::separator();
    qsInputDir = QDir::cleanPath( qsInputDir );

    m_poDataSource = new cLogDataSource( qsInputDir, p_qsFiles );

    m_poActionDefList = new cActionDefList( p_qsActions );
}

cLogAnalyzer::~cLogAnalyzer()
        throw()
{
    cTracer  obTracer( "cLogAnalyser::~cLogAnalyser" );

    delete m_poActionDefList;
    delete m_poDataSource;
}
