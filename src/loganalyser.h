#ifndef LOGANALYSER_H
#define LOGANALYSER_H

#include <QString>
#include <map>

#include <sevexception.h>

#include "logdatasource.h"
#include "actiondeflist.h"
#include "action.h"
#include "outputcreator.h"

//! \brief Performs the full Log Analysis of the given Input Logs
/*! The full Log Analysis means that this class first prepares all the specified Input Logs
 *  (using cLogDataSource), reads in the Action Definitions (using cActionDefList), then
 *  after the analysis is complete, it will also genereate the outputs (using
 *  cOutputCreator).
 *
 *  There can be several Log Analysis runs during a single LARA run (as opposed to Batch
 *  Analysis, because there can be only one of them). cLogAnalyser objects are created by
 *  cBatchAnalyser, one for each <tt>analysis</tt> defined in the XML configuration file.
 *
 *  First step of the analysis is using the <tt>pcregrep</tt> command to find occurrences of
 *  the defined Patterns (functions findPatterns() and storePattern()). The list of found
 *  Patterns is then used to create a list of Actions (functions
 *  identifySingleLinerActions(), storeActions() and storeAttributes()). The final step is to
 *  calculate the results of the Count Actions (function countActions()).
 */
class cLogAnalyser
{
public:
    //! Structure to hold a Pattern that was found in one of the Input Logs
    typedef struct
    {
        //! Unique id of the file where the Pattern was found (see cOutputCreator::fileId())
        unsigned int          uiFileId;
        //! Line number within the Input Log where the Pattern was found
        unsigned long         ulLineNum;
        //! Time-stamp string as it was found in the Input Log
        QString               qsTimeStamp;
        //! Converted time-stamp as a structure so it can be used for calculations
        cAction::tsTimeStamp  suTimeStamp;
        //! List of Captured Attriutes
        tmActionAttribs       maCapturedAttribs;
    } tsFoundPattern;

    //! MultiMap container type for holding all the Found Patterns.
    typedef std::multimap<QString, tsFoundPattern> tmFoundPatternList;
    //! Iterator type for accessing the list of Found Patterns.
    typedef tmFoundPatternList::const_iterator     tiFoundPatternList;

    //! \brief Default constructor to initialise member variables
    /*! It creates the full path to the Input Files using the Input Diretory defined in the
     *  Preferences and the p_qsPrefix parameters. This full Input Path can be used to create
     *  a cLogDataSource instance. An empty cActionDefList is also created, but the
     *  cOutputCreator instance is not created here, it is received as a parameter from the
     *  cBatchAnalyser (since the cOutputCreator is shared between the different cLogAnalyser
     *  instances).
     *  \param p_qsPrefix Directory Prefix as it appears in the XML configuration file
     *  \param p_qsFiles  Input Files as it appears in the XML configuration file
     *  \param p_qsActions Name of the Action Definition XML file
     *  \param p_poOC Pointer to the cOutputCreator instance
     */
    cLogAnalyser( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions, cOutputCreator *p_poOC ) throw();
    ~cLogAnalyser() throw();

    //! \brief Main function of the cLogAnalyser class, performs the full log analysis.
    /*! The full log analysis consists of the following steps:
     *  \li Finding and storing the defined Patterns in all the Input Logs (findPatterns()
     *  and storePatterns())
     *  \li Identify Actions using the stored Patterns (identifySingleLinerActions())
     *  \li Determine the results of CountActions (countActions())
     *  \li Store all the identified Actions in the OutputCreator (storeActions())
     *  \li Store all the Batch Attributes in the OutputCreator (storeAttributes())
     */
    void          analyse()      throw( cSevException );

    //! \brief Returns with the number of Patterns found in the Input Log Files.
    /*! This function is for the Unit Tests, to check if the correct number of Patterns were
     *  found. The returned value is actually the size of the internal container holding the
     *  stored Patterns (m_maFoundPatterns), filled in the storePatterns() function.
     */
    unsigned int  patternCount() throw();

    //! \brief Returns with the number of identified Actions.
    /*! This function is for the Unit Tests, to check if the correct number of Actions were
     *  identified. The returned value is actually the size of the internal container holding
     *  the identified Actions (m_mmActionList), filled in the identifySingleLinerActions()
     *  function.
     */
    unsigned int  actionCount()  throw();

private:
    //! The Data Source that provides access to all the Input Log Files
    cLogDataSource      *m_poDataSource;
    //! The list of Action Definitions
    cActionDefList      *m_poActionDefList;
    //! Map container holding the Patterns found in all the Input Log Files
    tmFoundPatternList   m_maFoundPatterns;
    //! MultiMap container holding the identified Actions
    tmActionList         m_mmActionList;
    //! Pointer to the cOutputCreator object that is shared between different Log Analysers.
    cOutputCreator      *m_poOC;

    //! \brief Finds the occurrences of the defined Regular Expressions within the Input Logs
    /*! This function runs a <tt>pcregrep</tt> command on the given Input Log for ecah
     *  defined Regular Expression to find matching Log lines. All the matching lines are
     *  stored as Patterns using the storePattern() function.
     *  \param p_qsFileName Name of the Input Log File to search for Patterns
     */
    void findPatterns( const QString &p_qsFileName ) throw();

    //! \brief Stores a given Log line as a "Found Pattern" to be processed later.
    /*! Storing a Pattern means filling in a tsFoundPattern type struct and store it in the
     *  m_maFoundPatterns container. The time-stamp of the Log Line is extracted using the
     *  time-stamp regular expression returned by cActionDefList::timeStampRegExp(). If any
     *  attributes are defined within the Pattern, their value is also captured and stored.
     *  \param p_uiFileId Id of the Input Log File where the Pattern was found
     *  \param p_itPattern Iterator (pointer) to the cPattern definition
     *  \param p_qsLogLine The full Log Line as found in the Input Log File
     *  \param p_poInsertPos Iterator to the position where the new Found Pattern should be
     *         inserted.
     */
    void storePattern( const unsigned int p_uiFileId, cActionDefList::tiPatternList p_itPattern,
                       const QString &p_qsLogLine, tmFoundPatternList::iterator  *p_poInsertPos ) throw( cSevException );

    //! \brief Identifies Singe Liner Actions based on the list of Found Patterns
    /*! This function walks through the whole list of Single Liner Action Definitions
     *  defined in m_poActionDefList and for each Action Definition, it looks through the
     *  list of Found Patterns in m_maFoundPatterns. For each matching Found Pattern a new
     *  cAction is created and all the captured and fixed attributes of that Pattern is
     *  copied into the new Action which is then added to the list of Identified Actions in
     *  m_mmActionList.
     */
    void identifySingleLinerActions() throw();

    //! \brief Counts the OK and FAILED Actions with the given name
    /*! This function looks up all the Identified Actions with the given name, and counts
     *  how many of them has OK and how many has FAILED result. The results are added to the
     *  list of CountActions in the cOutputCreator under the name given in the p_qsCountName
     *  parameter.
     *
     *  If the p_qsAttribName parameter is not empty, each Action will not count as 1 in the
     *  results, but instead the value of that Attribute will be added to the total. For
     *  example if there are two Actions and the specified Attribute value is 10 for each,
     *  the result of the CountAction will be 20 and not 2. If the Attribute doesn't exist,
     *  the Action will be counted simply as 1.
     *  /param p_qsCountName The name of the CountAction. The calculated results will be
     *         saved under this name in the cOutputCreator.
     *  /param p_qsActionName Name of the Actions to be counted.
     *  /param p_qsAttribName If not empty, each Action will be counted as the value of this
     *         Attribute.
     */
    void countActions( const QString &p_qsCountName,
                       const QString &p_qsActionName,
                       const QString &p_qsAttribName ) throw();

    //! \brief Adds each Identified Action to the cOutputCreator.
    /*! It runs after all the required Log Analysis has finished. It walks through the whole
     *  list of Identified Actions and adds them one by one to the cOutputCreator (m_poOC)
     */
    void storeActions()    throw( cSevException );

    //! \brief Adds the captured Batch Attributes and their values to cOutputCreator
    /*! Looks through the list of Batch Attribute definitions in the cActionDefList
     *  (m_poActionDefList) and if there is a matching Found Pattern, the value of the
     *  Attribute is captured using the Regular Expression of the Pattern. The name and value
     *  of the Attribute is then added to the cOutputCreator (m_poOC) so they can appear in
     *  the generated outputs.
     */
    void storeAttributes() throw();
};

#endif // LOGANALYSER_H
