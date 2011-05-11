#ifndef OUTPUTCREATOR_H
#define OUTPUTCREATOR_H

#include <QString>
#include <QStringList>
#include <map>
#include <qtmysqlconnection.h>
#include <sevexception.h>

#include "logdatasource.h"
#include "action.h"

//! \brief Generates the LARA output (database upload and text file reports)
/*! There are two different types of LARA outputs, DataBase entries and text file reports in
 *  both plain text and html format. During Log Analysis the cOutputCreator collects and
 *  stores all the results in memory. After the analysis is finished, the outputs are
 *  generated.
 *
 *  Generated text reports consist of two files: an Action Summary (see
 *  generateActionSummary()) and an Action List (see generateActionList()). The results are
 *  also uploaded to database (see uploadActionSummary() and uploadActionList()) using the
 *  database connection details specified in the laratest.ini configuration file.
 */
class cOutputCreator
{
public:
    //! \brief Constructor that sets up a MySQL database connection.
    /*! Using the preferences stored in the LARA configuration file, a new MySQL database
     *  connection is created. The full path to the generated output files is also created
     *  using the Output Directory from the same configuration file.
     */
    cOutputCreator( const QString &p_qsDirPrefix );

    //! \brief Destructor that frees up allocated memory and closes the database connection.
    ~cOutputCreator();

    //! \brief Returns a unique file id for the given file name
    /*! In the generated output reports each identified Action refers to the Input Log File
     *  where it was found during analysis. To make this reference possible, each Input Log
     *  file is given a unique id so Actions can use this id to refer to the given file.
     *  This function first checks if the given file name is alreay in the list. If it is,
     *  then it already has an id assigned, and this id is returned. <em>I seriously doubt
     *  anyone will ever read this, but if you in fact got this far, and still know who
     *  wrote these lines, contact me and if you're the first one, I owe you a beer six-pack.
     *  </em> If the file is not yet in the list, a new id is generated and the file is
     *  appended to the list.
     *  \param p_qsFileName Name of the file whose id is requested
     *  \return The requested unique file id
     */
    unsigned int fileId( const QString & p_qsFileName )                 throw( cSevException );

    //! \brief Adds an Action to the list of found Actions
    /*! The list of found (identified) Actions contains all the Actions found during log
     *  log analysis. Note that although the Action is received as a pointer, the list will
     *  contain a new copy of an actual cAction instance, not just a pointer.
     *  \param m_poAction Pointer to the Action that needs to be added to the list
     */
    void         addAction( const cAction *p_poAction )                 throw( cSevException );

    //! \brief Adds a CountAction to the list of found CountActions
    /*! Each CountAction has two result fields, the nnumber of Failed, and the number of Ok
     *  Actions (see tsActionResCount). Each CountAction result pair is identified with a
     *  name. If the received CountAction name already exists in the list, the received Ok
     *  and Failed Action counts are added to the values already present in the list. If the
     *  name doesn't exist yet, a new result pair is created, and this new pair is placed in
     *  the list under the given name.
     * \param p_qsCountName Name of the CountAction result pair
     * \param p_ulOk The number of Ok Actions
     * \param p_ulFailed The number of Failed Actions
     */
    void         addCountAction( const QString &p_qsCountName,
                                 const unsigned long p_ulOk,
                                 const unsigned long p_ulFailed )       throw();

    //! \brief Adds an Attribute to the list of global Attributes
    /*! Global Attributes are not part of any Actions, they are defined as "batch attribute"
     *  in the XML configuration files. They can have both fixed or captured value that will
     *  be part of the generated Action Summary output and the 'cyclerconfigs' table in the
     *  database.
     *  \param p_qsName Name of the Attribute
     *  \param p_qsValue Value of the Attribute
     */
    void         addAttribute( const QString &p_qsName,
                               const QString &p_qsValue )               throw();

    //! \brief Adds an entry to the contents of the Combined Log output
    /*! The contents of Combined Log is collected in a multimap (m_mmCombilogEntries) where
     *  the time-stamp of each log line is used as the key. Since it is possible to have
     *  multiple log lines with the same time-stamp, a multimap is used instead of a simple
     *  map. The multimap container also makes sure that no matter in what order the lines
     *  are added, the final output will be ordered by their time-stamps. Each Combined Log
     *  line has a color as well, this color comes from the XML configuration file (each
     *  XML file can define a different color, leading to a multi-colored Combined Log).
     *  \param p_ulTime Time-stamp of the log line
     *  \param p_qsLogLine The log line to be entered in the Combined Log
     *  \param p_qsColor Color of the log line in \#XXXXXX format (X is a hexadecimal digit)
     */
    void         addCombilogEntry( const unsigned long long p_ulTime,
                                   const QString &p_qsLogLine,
                                   const QString &p_qsColor )           throw();

    //! \brief Generates the Action Summary text file.
    /*! The Action Summary text file contains the list of Input Log files that were processed
     *  during analysis, the global ("batch") Attributes together with their values and the
     *  results of all the Count Actions.
     */
    void         generateActionSummary()                          const throw( cSevException );

    //! \brief Uploads the Action Summary to database.
    /*! Action Summary results are uploaded to database into the <tt>cyclerconfigs</tt>
     *  table. CountAction results and Attributes are only uploaded if their names match with
     *  a column name in the <tt>cyclerconfigs</tt> table. The columns <tt>startDate</tt>,
     *  <tt>endDate</tt>, <tt>cellName</tt> and <tt>examName</tt> must have a value, so if
     *  there are no Attributes defined with these names, a default value is used.
     *  \return Value of the <tt>cyclerconfigId</tt> column of the new database record
     */
    unsigned long long uploadActionSummary()                            throw( cSevException );

    //! \brief Generates the Action List text file.
    /*! The Action List text file contains a detailed list of all the Action that has been
     *  found during analysis. Next to each Action the names and values of their Attributes
     *  are also listed, together with the name of the Input File and line number where they
     *  were found.
     */
    void         generateActionList()                             const throw( cSevException );

    //! \brief Uploads the Action List to database.
    /*! Action List is uploaded to database into the <tt>occurrences</tt> table. Each Action
     *  will be a separate record. Action Attributes are only uploaded if the Attribute name
     *  matches a column name in the <tt>occurrences</tt> table.
     */
    void         uploadActionList()                               const throw( cSevException );

    //! \brief Generates a Combined Log in html format
    /*! The Combined Log is a generated html file that contains lines from <em>all</em>
     *  Input Log files. Each Pattern that has been found in any of the Input Log files will
     *  be part of the Combined Log using the color defined in their respective XML
     *  configuration file. The Combined Log lines are ordered based on their time-stamp.
     */
    void         generateCombilog()                               const throw( cSevException );

private:

    //! Multimap container type to hold all the Actions found during log Analysis
    typedef std::multimap<unsigned long long, cAction> tmActionList;
    //! Const Iterator type for the multimap containing all the Actions
    typedef tmActionList::const_iterator               tiActionList;
    //! Multimap container to store all the Actions found during Log Analysis
    tmActionList        m_mmActionList;

    //! Structure to store tha CountAction result-pair
    typedef struct
    {
        //! Number of Actions with an "OK" result
        unsigned long ulOk;
        //! Number of Action with a "FAILED" result
        unsigned long ulFailed;
    } tsActionResCount;
    //! Map container type for storing CountAction results
    typedef std::map<QString, tsActionResCount*> tmActionCountList;
    //! Const Iterator type for the map container holding the CountAction results
    typedef tmActionCountList::const_iterator    tiActionCountList;
    //! Map container to store CountAction results
    tmActionCountList   m_maActionCounts;

    //! Map container type for storing global (Batch) Attributes
    typedef std::map<QString,QString>            tmAttributes;
    //! Const Iterator type for the map container holding the global (Batch) Attributes
    typedef tmAttributes::const_iterator         tiAttributes;
    //! Map container to store global (Batch) Attributes
    tmAttributes        m_maAttributes;

    //! Structure to hold the text and the color of a Combined Log entry.
    typedef struct
    {
        //! Text of the Combined Log entry
        QString qsLogLine;
        //! Background color of the Combined Log entry
        QString qsColor;
    } tsCombilogEntry;
    //! Multimap container type to hold all Combined Log entries
    typedef std::multimap<unsigned long long, tsCombilogEntry> tmCombilogEntries;
    //! Const Iterator type for the multimap container holding the Combined Log entries
    typedef tmCombilogEntries::const_iterator                  tiCombilogEntries;
    //! Multimap container to store all Combined Log entries
    tmCombilogEntries   m_mmCombilogEntries;

    //! The Database connection needed to upload results to the MySQL database.
    cQTMySQLConnection *m_poDB;
    //! Name of the Output Directory where the generated text files will be placed
    QString             m_qsOutDir;
    //! List of all Input Log files that were processed during Log Analysis
    QStringList         m_slInputFiles;
    //! Record id of the uploaded Action Summary (in <tt>cyclerconfigs</tt>), needed to upload the Action List (to <tt>occurrences</tt>).
    unsigned long long  m_ulBatchId;
};

#endif // OUTPUTCREATOR_H
