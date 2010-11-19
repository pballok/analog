#ifndef BATCHANALYSER_H
#define BATCHANALYSER_H

#include <QString>
#include <QDomDocument>
#include <vector>

class cBatchAnalyser
{
public:
    cBatchAnalyser( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw();
    ~cBatchAnalyser() throw();

    void analyse() throw();

private:
    typedef struct
    {
        QString  qsFiles;
        QString  qsActionDefFile;
    } tsInputLogDefinition;

    typedef std::vector<tsInputLogDefinition>  tvInputLogDefs;
    typedef tvInputLogDefs::const_iterator     tiInputLogDefs;

    typedef struct
    {
        QString         qsName;
        QString         qsDirPrefix;
        tvInputLogDefs  veInputLogs;
    } tsAnalyseDefinition;

    typedef std::vector<tsAnalyseDefinition>  tvAnalyseDefs;
    typedef tvAnalyseDefs::const_iterator     tiAnalyseDefs;

    QDomDocument   *m_poBatchDoc;
    tvAnalyseDefs   m_veAnalyseDefs;

    void validateBatchDef( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw( cSevException );
    void parseBatchDef() throw( cSevException );
};

#endif // BATCHANALYSER_H
