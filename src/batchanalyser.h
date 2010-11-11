#ifndef BATCHANALYSER_H
#define BATCHANALYSER_H

#include <QString>
#include <QDomDocument>

class cBatchAnalyser
{
public:
    cBatchAnalyser( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw();
    ~cBatchAnalyser() throw();

    void analyse() throw();

private:
    QDomDocument                    *m_poBatchDoc;

    void validateBatchDef( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw( cSevException );
    void parseBatchDef() throw( cSevException );
};

#endif // BATCHANALYSER_H
