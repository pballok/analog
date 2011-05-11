#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include <map>

#include "actiondef.h"

//! Map type for storing Attributes of an Actions
typedef std::map<QString,QString>        tmActionAttribs;
//! Const Iterator type for map container storing Attributes of an Action
typedef tmActionAttribs::const_iterator  tiActionAttribs;

//! \brief Represents an Action that has been successfully identified in the Input Logs
/*! An Action is basically the occurrence of the Pattern(s) defined in the Action Definition.
 *  During the Log Analysis, every time a Pattern is found in one of the Input Log Files, a
 *  new Action is created that has a time-stamp and a Result, refers to a specific Input Log
 *  File and line number, etc. If the Action Definition contains Attributes as well, the
 *  value of those Attributes are also determined (usually by capturing parts of the log
 *  line using the Regular Expression).
 */
class cAction
{
public:

    //! Structure to hold parts of a time-stamp so they can be converted to different formats
    typedef struct
    {
        //! The <tt>Year</tt> part of the time-stamp
        unsigned int uiYear;
        //! The <tt>Month</tt> part of the time-stamp
        unsigned int uiMonth;
        //! The <tt>Day</tt> part of the time-stamp
        unsigned int uiDay;
        //! The <tt>Hour</tt> part of the time-stamp
        unsigned int uiHour;
        //! The <tt>Minute</tt> part of the time-stamp
        unsigned int uiMinute;
        //! The <tt>Second</tt> part of the time-stamp
        unsigned int uiSecond;
        //! The <tt>Milisecond</tt> part of the time-stamp
        unsigned int uiMSecond;
    } tsTimeStamp;

    //! \brief Constructor that initialises all member variables
    /*! If the p_poTimeStamp parameter is not NULL, a private copy of the structure is made.
     *  \param p_qsName Name of the Action
     *  \param p_qsTimeStamp The time-stamp of the Action as it was captured from the Input Log
     *  \param p_poTimeStamp Pointer to a structure holding the time-stamp parts
     *  \param p_uiFileId Id of the Input Log File in which the Action was found
     *  \param p_ulLineNum Line number within the Input Log File where the Action was found
     *  \param p_enResult Result of the Action (OK or FAILED)
     *  \param p_enUpload Value of the Upload flag of this Action
     */
    cAction( const QString &p_qsName = "", const QString &p_qsTimeStamp = "",
             const tsTimeStamp* p_poTimeStamp = NULL,
             const unsigned int p_uiFileId = 0, const unsigned long p_ulLineNum = 0,
             const cActionResult::teResult p_enResult = cActionResult::MIN,
             const cActionUpload::teUpload p_enUpload = cActionUpload::MIN );

    //! \brief Destructor
    /*! An empty destructor.
     */
    ~cAction();

    //! \brief Returns the name of the Action
    /*! This name comes from the Action Definition. Action Definition names are unique, but
     *  since a Pattern of the Action Definition can appear in many times in the Input Logs,
     *  there can be any number of found Actions with the same name.
     *  \return the Name of the Action
     */
    QString                  name() const throw();

    //! \brief Returns the captured time-stamp of the Action
    /*! This is the time-stamp of the Action as a string, as it appeared in the Input Log.
     *  Since the format of the time-stamp can be different in each Input Log, this string is
     *  not suitable for comparing or ordering Actions, it is simply used in the generated
     *  output files so the found Actions can appear together with their original time-stamp
     *  format.
     *  \return The time-stamp of the Action as appeared in the Input Log
     */
    QString                  timeStamp() const throw();

    //! \brief Returns the time-stamp structure of the Action
    /*! The time-stamp structure holds the individual time-stamp parts as a numerical value.
     *  This time-stamp can be used to convert it to a single, numberial value (for
     *  comparison and ordering) or to create a time-stamp string with different formats
     *  (for example for the MySQL database engine, etc).
     *  \sa cAction::tsTimeStamp
     *  \return The time-stamp of the Action as a time-stamp structure
     */
    tsTimeStamp              timeStampStruct() const throw();

    //! \brief Returns the id of the Input File where the Action was found
    /*! Input Log Files are given a unique id by the cOutputCreator so each found Action can
     *  easily refer to the exact Input File it was found in. This reference is displayed
     *  in the generated output files to make it easier for people wanting to investigate
     *  the surroundings of the Action in the original Input Logs.
     *  \sa cOutputCreator::fileId()
     *  \return Id of the Input File where the Action was found
     */
    unsigned int             fileId() const throw();

    //! \brief Returns the line number within the Input Log File where the Action was found
    /*! This line number (along with the Input Log File name) is displayed in the generated
     *  output files to make it easier for people wanting to investigate the surroundings of
     *  the Action in the original Input Logs.
     *  \return Line Number within the Input File where the Action was found
     */
    unsigned long            lineNum() const throw();

    //! \brief Returns the Result of the Action
    /*! The Result can be either OK or FAILED. For Single Liner Actions, this result is
     *  pre-defined in the Action Definition, but in case of more complex Action Definitions
     *  the result can be influenced by the presence (or absence) of given Patterns.
     *  \sa cActionResult::teResult
     *  \return the Result of the Action as an enum
     */
    cActionResult::teResult  result() const throw();

    //! \brief Returns the Upload flag of the Action
    /*! The value of the Upload flag can be OK, FAILED, ALWAYS or NEVER. This flag influences
     *  whether the Action will be uploaded to the database by cOutputCreator or not. It has
     *  absolutely no effect on the text report generation.
     *  \sa cActionUpload::teUpload
     *  \return the value of the Upload flag
     */
    cActionUpload::teUpload  upload() const throw();

    //! \brief Adds an Attribute and its value to the Action
    /*! Actions can have attributes (as defined in their Action Definition). When an Action
     *  is found in the Input Logs, its Attributes are also filled in. Attributes that have
     *  fixed value (pre-defined in the Action Definition) simply have their value copied
     *  from the definition. Captured Attributes capture their values from the text of the
     *  Log Lines where the Action was found.
     *
     *  This function adds the given Attribute name and value pair to the internal container
     *  of Attributes. Since Attributes have unique names within a given Action, a
     *  <tt>map</tt> container is used.
     *  \sa cActionDef::fixedAttributesBegin
     *  \sa cPattern::capturedTexts
     *  \param p_qsAttribName Name of the Attribute
     *  \param p_qsAttribValue Value of the Attribute
     */
    void                     addAttribute( const QString &p_qsAttribName,
                                           const QString &p_qsAttribValue ) throw();


    //! \brief Returns with an iterator to the first Attribute of the Action.
    /*! Each Action can have any number of Attributes. They can be either fixed or captured
     *  values. Attributes are stored in an std::map container with the name of the Attribute
     *  as the key and the attribute value as the value.
     *  \sa addAttribute
     *  \return The <tt>begin</tt> iterator for the map holding the Attributes
     */
    tiActionAttribs          attributesBegin() const throw();

    //! \brief Returns with an iterator to the past-the-end Attribute of the Action.
    /*! \sa attributesBegin
     *  \sa addAttribute
     *  \return The <tt>end</tt> iterator for the map holding the Attributes
     */
    tiActionAttribs          attributesEnd() const throw();

    //! \brief Returns the value of the Attribute with the name specified as the parameter
    /*! Fetches the value of the specified Attribute from the map container. If the given
     *  Attribute is not found, it returns with an empty string.
     *  \sa addAttribute
     *  \return Value of the specified Attribute, or an empty string if it doesn't exist.
     */
    QString                  attribute( const QString &p_qsAttribName ) const throw();

private:
    //! Holds the name of the Action
    /*! \sa name()
     */
    QString                  m_qsName;

    //! Holds the time-stamp string of the Action
    /*! \sa timeStamp()
     */
    QString                  m_qsTimeStamp;

    //! Holds the time-stamp structure of the Action
    /*! \sa timeStampStruct()
     */
    tsTimeStamp              m_suTimeStamp;

    //! Holds the id of the Input Log where the Action was found
    /*! \sa fileId()
     */
    unsigned int             m_uiFileId;

    //! Holds the line number within the Input Log where the Action was found
    /*! \sa lineNum()
     */
    unsigned long            m_ulLineNum;

    //! Holds the Result of the Action
    /*! \sa result()
     */
    cActionResult::teResult  m_enResult;

    //! Holds the Upload flag of the Action
    /*! \sa upload()
     */
    cActionUpload::teUpload  m_enUpload;

    //! Map container to hold the Attributes of the Action
    /*! \sa attributesBegin()
     *  \sa attributesEnd()
     */
    tmActionAttribs          m_maAttribs;
};

//! Multimap type to store a list of Identified Actions
typedef std::multimap<QString, cAction>  tmActionList;
//! Const Iterator type for the miltimap container storing a list of Identified Actions
typedef tmActionList::const_iterator     tiActionList;

#endif // ACTION_H
