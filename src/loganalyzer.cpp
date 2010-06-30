#include "loganalyzer.h"
#include "qtframework.h"

cLogAnalyzer::cLogAnalyzer( const string &p_stPrefix, const string &p_stFiles, const string &p_stActions )
{
    cTracer  obTracer( "cLogAnalyser::cLogAnalyser", "prefix: \"" + p_stPrefix + "\", files: \"" + p_stFiles + "\", actions: \"" + p_stActions + "\"" );

    m_stPrefix = p_stPrefix;
    m_stFiles = p_stFiles;
    m_stActions = p_stActions;
}

cLogAnalyzer::~cLogAnalyzer()
{
}
