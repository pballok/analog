#ifndef BATCHANALYSER_H
#define BATCHANALYSER_H

#include <QString>
#include <QDomDocument>
#include <vector>

class cBatchAnalyser
{
public:
    typedef struct
    {
        QString     qsName;
        QString     qsDirPrefix;
        QString     qsFiles;
        QString     qsActionDefFile;
    } tsAnalyseDefinition;

    typedef std::vector<tsAnalyseDefinition>  tvAnalyseDefs;
    typedef tvAnalyseDefs::const_iterator     tiAnalyseDefs;

    cBatchAnalyser( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw();
    ~cBatchAnalyser() throw();

    void analyse() throw();

private:
    QDomDocument   *m_poBatchDoc;
    tvAnalyseDefs   m_veAnalyseDefs;

    void validateBatchDef( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw( cSevException );
    void parseBatchDef() throw( cSevException );
};

#endif // BATCHANALYSER_H
