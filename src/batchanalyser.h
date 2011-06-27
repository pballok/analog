#ifndef BATCHANALYSER_H
#define BATCHANALYSER_H

#include <QString>
#include <QDomDocument>
#include <vector>
#include <map>

//! \brief Performs a Batch Analysis as defined in the XML Batch configuration file
/*! A Batch Analysis usually means multiple Log Analysis. One Batch has its own input and
 *  output directory, and all Log Analysis read and write those directories and their
 *  subdirectories. Batches are defined in a separate XML configuration file, called the
 *  Batch Definition file. This is the XML file that is passed to the LARA executable as a
 *  command line parameter. The Batch Analyser will start a separate Log Analysis for each
 *  <tt>analysis</tt> tag defined in the Batch XML file.
 */
class cBatchAnalyser
{
public:
    //! \brief Default constructor to initialise member variables
    /*! The constructor reads in the Batch Definition from the XML configuration file. As a
     *  first step, the XML file is validated agains the given XML Schema file. If the XML
     *  file is valid, its content is parsed and the Batch Definitions are stored in
     *  m_veAnalyseDefs.
     *  \param p_qsBatchDefFile Name of the Batch Definition XML file
     *  \param p_qsSchemaFile Name of the XML Schema file used to validate the Batch
     *         Definition XML file
     */
    cBatchAnalyser( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw();
    //! \brief Destructor
    ~cBatchAnalyser() throw();

    //! \brief Performs the full Batch Analysis
    /*! Since a Batch Analysis consists of several Log Analysis, this function walks through
     *  each Analysis Definition, and performs the following steps for each Analysis:
     *  \li Create a new cOutputCreator (each Log Analysis has its own)
     *  \li If there are Batch Attributes, add them to the cOutputCreator
     *  \li Create a cLogAnalyser and run it
     *  \li Generate outputs using cOutputCreator functions
     */
    void analyse() throw();

private:
    //! \brief Holds Input Log Names and the XML file name used to analyse those logs.
    typedef struct
    {
        //! Name of the Input Log Files to be analysed (can contain '*' or '?' characters).
        QString  qsFiles;
        //! Name of the XML Action Definition file used to analyse the Input Log Files
        QString  qsActionDefFile;
    } tsInputLogDefinition;

    //! Vector container type to hold Input Log definitions
    typedef std::vector<tsInputLogDefinition>  tvInputLogDefs;
    //! Const iterator type for the vector holding Input Log definitions
    typedef tvInputLogDefs::const_iterator     tiInputLogDefs;
    //! Map container type to hold Batch Attributes
    typedef std::map<QString,QString>          tmAttributes;
    //! Const iterator type for the map holding Batch Attributes
    typedef tmAttributes::const_iterator       tiAttributes;
    //! Struct to hold one Analysis definition (as defined in the XML Batch Definition file)
    typedef struct
    {
        //! Name of the Analysis definition
        QString         qsName;
        //! List of Input Logs that needs to be analysed
        tvInputLogDefs  veInputLogs;
        //! Map to hold the Attributes and their values.
        tmAttributes    maAttributes;
    } tsAnalyseDefinition;

    //! Vector container type to hold Analysis definitions
    typedef std::vector<tsAnalyseDefinition>  tvAnalyseDefs;
    //! Const iterator type for the vector holding the Analysis definitions
    typedef tvAnalyseDefs::const_iterator     tiAnalyseDefs;

    //! DomDocument holding the contents of the XML Batch Definition file
    QDomDocument   *m_poBatchDoc;

    //! Vector holding the Analysis definitions
    tvAnalyseDefs   m_veAnalyseDefs;

    //! Directory Prefix as defined in the <tt>dir_prefix</tt> attribute in the XML file
    QString         m_qsDirPrefix;

    //! \brief Performs a syntax check (Validation) of the Batch Definition XML file.
    /*! Validation is performed using an XML Schema file received as a parameter. Only the
     *  validaton is done, the contents of the file is parsed by the parseBatchDef()
     *  function.
     *  \param p_qsBatchDefFile name of the XML Batch Definition file
     *  \param p_qsSchemaFile name of the XML Schema file needed for XML validation.
     */
    void validateBatchDef( const QString &p_qsBatchDefFile, const QString &p_qsSchemaFile ) throw( cSevException );

    //! \brief Parse and read the contents of the Batch Definition XML file
    /*! Parsing is called after a successful validation (validateBatchDef()) and reads the
     *  contents into memory. Each <tt>analysis</tt> tag is stored in the m_veAnalyseDefs
     *  vector.
     */
    void parseBatchDef() throw( cSevException );
};

#endif // BATCHANALYSER_H
