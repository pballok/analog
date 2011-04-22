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
/*! The full Log Analysis means that this class will first prepares all the specified Input
 *  Logs (using cLogDataSource), reads in the Action Definitions (using cActionDefList), then
 *  after the analysis is complete, it will also genereate the outputs (using
 *  cOutputCreator).
 *
 *  First step of the analysis is using the <tt>pcregrep</tt> command to find occurrences of
 *  the defined Patterns (functions findPattern() and storePattern()). The list of found
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

    //! Default constructor to initialise member variables
    /*! It creates the full path to the Input Files using the Input Diretory defined in the
     *  Preferences and the p_qsPrefix parameters. This full Input Path can be used to create
     *  a cLogDataSource instance. An empty cActionDefList is also created, the
     *  cOutputCreator instance is received as a parameter, not created here. MIERT?
these are all used by the cLogAnalyser to perform the full log analysis.
     */
    cLogAnalyser( const QString &p_qsPrefix, const QString &p_qsFiles, const QString &p_qsActions, cOutputCreator *p_poOC ) throw();
    ~cLogAnalyser() throw();

    void          analyse()      throw( cSevException );
    unsigned int  patternCount() throw();
    unsigned int  actionCount()  throw();

private:
    cLogDataSource      *m_poDataSource;
    cActionDefList      *m_poActionDefList;
    tmFoundPatternList   m_maFoundPatterns;
    tmActionList         m_mmActionList;
    cOutputCreator      *m_poOC;

    void findPatterns( const QString &p_qsFileName ) throw();
    void storePattern( const unsigned int p_uiFileId, cActionDefList::tiPatternList p_itPattern,
                       const QString &p_qsLogLine, tmFoundPatternList::iterator  *p_poInsertPos ) throw( cSevException );
    void identifySingleLinerActions() throw();
    void countActions( const QString &p_qsCountName,
                       const QString &p_qsActionName,
                       const QString &p_qsAttribName ) throw();
    void storeActions()    throw( cSevException );
    void storeAttributes() throw();
};

#endif // LOGANALYSER_H
