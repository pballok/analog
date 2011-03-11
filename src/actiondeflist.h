#ifndef ACTIONDEFLIST_H
#define ACTIONDEFLIST_H

#include <QString>
#include <QDomDocument>
#include <QRegExp>
#include <QStringList>
#include <vector>

#include <sevexception.h>

#include "pattern.h"
#include "actiondefsingleliner.h"
#include "countaction.h"

//! Convenience class to provide conversion functions for the TimeStampPart enum values
/*! TimeStampPart is used to identify the different numerical values (for example year,
 *  month, etc) within a timestamp string. The possible enum values are:
 *  \li <tt>YEAR</tt> year
 *  \li <tt>MONTH</tt> month
 *  \li <tt>DAY</tt> day of the month
 *  \li <tt>HOUR</tt> hour
 *  \li <tt>MINUTE</tt> minute
 *  \li <tt>SECOND</tt> second
 *  \li <tt>MSECOND</tt> milisecond
 *
 *  This class is only an enhanced version of the
 *  simple enum type. In addition to defining the enum values, it provides conversion
 *  functions as well.
 */
class cTimeStampPart
{
public:
    //! The basic enum type wrapped inside this class
    enum teTimeStampPart
    {
        MIN = 0,
        YEAR,
        MONTH,
        DAY,
        HOUR,
        MINUTE,
        SECOND,
        MSECOND,
        MAX
    };

    //! Conversion function to convert an enum value to a string
    static const char *toStr( teTimeStampPart p_enPart )
    {
        switch( p_enPart )
        {
            case YEAR:    return "YEAR";    break;
            case MONTH:   return "MONTH";   break;
            case DAY:     return "DAY";     break;
            case HOUR:    return "HOUR";    break;
            case MINUTE:  return "MINUTE";  break;
            case SECOND:  return "SECOND";  break;
            case MSECOND: return "MSECOND"; break;
            default:      return "INVALID";
        }
    }

    //! Conversion function that attempts to convert a string to an enum value
    static teTimeStampPart fromStr( const char* p_poStr )
    {
        if( strcmp( p_poStr, "YEAR" ) == 0 )    return YEAR;
        if( strcmp( p_poStr, "MONTH" ) == 0 )   return MONTH;
        if( strcmp( p_poStr, "DAY" ) == 0 )     return DAY;
        if( strcmp( p_poStr, "HOUR" ) == 0 )    return HOUR;
        if( strcmp( p_poStr, "MINUTE" ) == 0 )  return MINUTE;
        if( strcmp( p_poStr, "SECOND" ) == 0 )  return SECOND;
        if( strcmp( p_poStr, "MSECOND" ) == 0 ) return MSECOND;
        return MIN;
    }
};

//! \brief Stores a list of Action Definitions as they were read in from the XML file.
/*! This class stores all the defined Patterns and Actions. For each type of Actions
 *  (currently SingleLiner and Count Actions) there is a separate list. The lists are
 *  populated when when the XML configuration file is read, and then later used by the
 *  LogAnalyser when looking for Actions in the input logs.

 *  In addition to the Pattern and ActionDef lists, this class also holds the Time Stamp
 *  format used to parse the time stamps from the input log, and the list of Pattern names
 *  that defines the Batch Attributes.
 */
class cActionDefList
{
public:
    //! Container type to store Pattern definitions
    typedef std::vector<cPattern>              tvPatternList;
    //! Iterator type for the Pattern container
    typedef tvPatternList::const_iterator      tiPatternList;

    //! Container type to store SingleLiner Actions
    typedef std::vector<cActionDefSingleLiner> tvSingleLinerList;
    //! Iterator type for the SingleLiner Action container
    typedef tvSingleLinerList::const_iterator  tiSingleLinerList;

    //! Container type to store CountActions
    typedef std::vector<cCountAction>          tvCountActionList;
    //! Iterator type for the CountAction container
    typedef tvCountActionList::const_iterator  tiCountActionList;

    //! \brief Constructor that reads the definition list from an XML file
    /*! This constructor first validates the XML configuration file using the given XML
     *  Schema file. If the XML is valid, it is parsed and all the Pattern and Action
     *  definitions are stored in their respective containers.
     *  \param p_qsActionDefFile name (and path) of the XML file containing the definitions
     *  \param p_qsScheaFile name (and path) of the XML Schema file for validation
     */
    cActionDefList( const QString &p_qsActionDefFile, const QString &p_qsSchemaFile ) throw();

    //! Empty Destructor
    ~cActionDefList() throw();

    //! returns the Combilog Colour defined for the Actions defined in the lists
    /*! The CombiLog Colour is a string in representing a colour in RGB format using
     *  hexadecimal numbers. It is used by cOutputCreator when creating the CombiLog in html
     *  format, the actions defined in this list will appear with the defined colour in the
     *  CombiLog. It is in a "#XXXXXX" format, where each 'X' is a hexadecimal digit, and the
     *  6 digits together define a single colour using the standard html colour definition
     *  RGB format.
     */
    QString                          combilogColor() const throw();

    //! \brief Returns with an iterator to the first Pattern definition.
    /*! Each Action Definition XML file can have any number of Patterns defined, these are
     *  stored in a std::vector container. For more details on Patterns, see cPattern.
     *  \return The <tt>begin</tt> iterator for the vector holding the Pattern definitions
     */
    tiPatternList                    patternBegin() const throw();

    //! \brief Returns with an iterator to the past-the-end Pattern definition.
    /*! \sa patternBegin()
     *  \return The <tt>end</tt> iterator for the vector holding the Pattern definitions
     */
    tiPatternList                    patternEnd() const throw();

    //! \brief Returns with an iterator to the first SingleLiner Action definition.
    /*! Each Action Definition XML file can have any number of SingleLiner Actions defined,
     *  these are stored in a std::vector container. For more details on SingleLiner Actions,
     *  see cActionDefSingleLiner.
     *  \return The <tt>begin</tt> iterator for the vector holding the SingleLiner Action
     *          definitions
     */
    tiSingleLinerList                singleLinerBegin() const throw();

    //! \brief Returns with an iterator to the past-the-end SingleLiner Action definition.
    /*! \sa singleLinerBegin()
     *  \return The <tt>end</tt> iterator for the vector holding the SingleLiner Action
     *          definitions
     */
    tiSingleLinerList                singleLinerEnd() const throw();

    //! \brief Returns with an iterator to the first CountAction definition.
    /*! Each Action Definition XML file can have any number of CountActions defined,
     *  these are stored in a std::vector container. For more details on CountActions,
     *  see cCountAction.
     *  \return The <tt>begin</tt> iterator for the vector holding the CountAction
     *          definitions
     */
    tiCountActionList                countActionBegin() const throw();

    //! \brief Returns with an iterator to the past-the-end CountAction definition.
    /*! \sa countActionBegin()
     *  \return The <tt>end</tt> iterator for the vector holding the CountAction definitions
     */
    tiCountActionList                countActionEnd() const throw();

    //! \brief Returns the list of Pattern names used to generate the Batch Attributes
    /*! Each Action Definition XML file can have any number of Batch Attributes defined,
     *  these are stored in a QStringList. Batch Attributes are captured values (so their
     *  value is not pre-defined but determined during Log Analysis) and can be defined by
     *  referring to already defined Patterns. All the captured values defined in the given
     *  Pattern are added to the Batch Attributes list, and at the end all the Batch
     *  Attributes will appear in the generated outputs.
     *  \return List of Batch Attributes (in fact Pattern names) as a QStringList
     */
    QStringList                      batchAttributes() const throw();

    //! \brief Returns the regular expression used to capture Time Stamps from log lines
    /*! This regular expression must match on every long line (a Warning message is produced
     *  and the given log line is skipped if it doesn't match) otherwise the time-stamp of
     *  the Action couldn't be determined. Each part of the time stamp (Year, Month, Day,
     *  etc) is captured using the "capture" feature of regular expressions.
     */
    QRegExp                          timeStampRegExp() const throw();

    //! \brief Returns the time-stamp part that is captured from the log line with the given Index
    /*! There is a sequence that defines the order in which the timestamp parts are captured.
     *  For example if the time-stamp is in "YYY-MM-DD hh:mm:ss" format, the first captured
     *  number would be the Year, the second is the Month, etc. This sequence is defined in
     *  the XML configuration file, stored in an array when the XML file is read in, then
     *  used later during Log Analysis to parse the time-stamp strings.
     *
     *  The time-stamp parts are numbered starting with 0, so to get the time-stamp part that
     *  was captured FIRST, you'd have to use timeStampPart( 0 ).
     *  \sa timeStampRegExp()
     *  \param p_uiIndex the index of the time-stamp part you're interested in
     *  \return the requested time-stamp part as an enum
     */
    cTimeStampPart::teTimeStampPart  timeStampPart( const unsigned int p_uiIndex ) const throw();

private:
    //! Holds the contents of the XML configuration file fully parsed
    QDomDocument                    *m_poActionsDoc;

    //! Holds the TimeStamp Regular Expression
    /*! \sa timeStampRegExp()
     */
    QRegExp                          m_obTimeStampRegExp;

    //! Holds the capturing sequence of the time-stamp parts
    /*! \sa timeStampPart
     */
    cTimeStampPart::teTimeStampPart  m_poTimeStampParts[cTimeStampPart::MAX - 1];

    //! Holds the <tt>combilog_color</tt> attribute of the Analysis
    /*! \sa combilogColor()
     */
    QString                          m_qsCombilogColor;

    //! Holds the list of the defined Patterns
    /*! \sa patternBegin() patternEnd()
     */
    tvPatternList                    m_vePatternList;

    //! Holds the list of the defined SingleLiner Actions
    /*! \sa singleLinerBegin() singleLinerEnd()
     */
    tvSingleLinerList                m_veSingleLinerList;

    //! Holds the list of the defined CountActions
    /*! \sa countActionBegin() countActionEnd()
     */
    tvCountActionList                m_veCountActionList;

    //! Holds the list of the defined Batch Attributes
    /*! \sa batchAttributes()
     */
    QStringList                      m_slBatchAttributes;

    //! Validates the given XML file with the given XML Schema file
    /*! Validation is performed with Qt's QXmlSchemaValidator class. If the validation is
     *  successful, the content of the XML file is loaded into memory (m_poActionsDoc
     *  variable).
     */
    void validateActionDef( const QString &p_qsActionDefFile, const QString &p_qsSchemaFile ) throw( cSevException );

    //! Parses the input XML file and copies all definitions into their own containers.
    /*! This function is called after a successful validation (see validateActionDef()). It
     *  reads the XML elements from memory, creates the necessary objects
     *  (cActionDefSingleLiner, cCountAction, cPattern, etc) and places them into their own
     *  containers.
     */
    void parseActionDef() throw( cSevException );
};

#endif // ACTIONDEFLIST_H
