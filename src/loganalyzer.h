#ifndef LOGANALYZER_H
#define LOGANALYZER_H

#include <string>

using namespace std;

class cLogAnalyzer
{
public:
    cLogAnalyzer( const string &p_stPrefix, const string &p_stFiles, const string &p_stActions );
    ~cLogAnalyzer();

private:
    string  m_stPrefix;
    string  m_stFiles;
    string  m_stActions;
};

#endif // LOGANALYZER_H
