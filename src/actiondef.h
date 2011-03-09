#ifndef ACTIONDEF_H
#define ACTIONDEF_H

#include <QString>
#include <QDomElement>
#include <map>

//! Convenience class to provide conversion functions for the ActionResult enum values
/*! Action Results are the possible result values of a cAction. The possible values are:
 *  \li <tt>OK</tt> The Action was successful
 *  \li <tt>FAILED</tt> The Action failed
 *
 *  This class is only an enhanced version of the
 *  simple enum type. In addition to defining the enum values, it provides conversion
 *  functions as well.
 */
class cActionResult
{
public:
    //! The basic enum type wrapped inside this class
    enum teResult
    {
        MIN = 0,
        OK,
        FAILED,
        MAX
    };

    //! Conversion function to convert an enum value to a string
    static const char *toStr( teResult p_enResult )
    {
        switch( p_enResult )
        {
            case OK:     return "OK";     break;
            case FAILED: return "FAILED"; break;
            default:     return "INVALID";
        }
    }

    //! Conversion function that attempts to convert a string to an enum value
    static teResult fromStr( const char* p_poStr )
    {
        if( strcmp( p_poStr, "OK" ) == 0 )     return OK;
        if( strcmp( p_poStr, "FAILED" ) == 0 ) return FAILED;
        return MIN;
    }
};

//! Convenience class to provide conversion functions for the ActionUpload enum values
/*! Action Upload is a flag that specifies if a given cAction needs to be uploaded into the
 *  database or not. The possible values are:
 *  \li <tt>OK</tt> Upload this action only its Result is <tt>OK</tt>.
 *  \li <tt>FAILED</tt> Upload this action only its Result is <tt>FAILED</tt>.
 *  \li <tt>ALWAYS</tt> Always upload this Action, regardless of its Result.
 *  \li <tt>NEVER</tt> Never upload this Action, regardless of its Result.
 *
 *  This class is only an enhanced version of the simple enum type. In addition to defining
 *  the enum values, it provides conversion functions as well.
 */
class cActionUpload
{
public:
    //! The basic enum type wrapped inside this class
    enum teUpload
    {
        MIN = 0,
        OK,
        FAILED,
        ALWAYS,
        NEVER,
        MAX
    };

    //! Conversion function to convert an enum value to a string
    static const char *toStr( teUpload p_enUpload )
    {
        switch( p_enUpload )
        {
            case OK:     return "OK";     break;
            case FAILED: return "FAILED"; break;
            case ALWAYS: return "ALWAYS"; break;
            case NEVER:  return "NEVER";  break;
            default:     return "INVALID";
        }
    }

    //! Conversion function that attempts to convert a string to an enum value
    static teUpload fromStr( const char* p_poStr )
    {
        if( strcmp( p_poStr, "OK" ) == 0 )     return OK;
        if( strcmp( p_poStr, "FAILED" ) == 0 ) return FAILED;
        if( strcmp( p_poStr, "ALWAYS" ) == 0 ) return ALWAYS;
        if( strcmp( p_poStr, "NEVER" ) == 0 )  return NEVER;
        return MIN;
    }
};

typedef std::map<QString,QString>       tmFixedAttribs;
typedef tmFixedAttribs::const_iterator  tiFixedAttribs;

//! Base class for all the different Action Definition classes
/*! All Action Definitions have a unique identifier, an Upload flag and a list of Fixed
 *  Attributes. This Base Class declares these common members and their access functions.
 */
class cActionDef
{
public:
    //! \brief The default (empty) constructor.
    /*! It only calls the init() function to initialise the member variables with default
     *  values.
     */
    cActionDef();

    //! \brief Alternate constructor to initialize from XML Node
    /*! It initialises the member variables from the XML element received as parameter.
     *  \param p_poElem pointer to any action definition XML Node Element as defined in the
     *  lara_actions.xsd XML Schema.
     *  \sa cActionDef()
     */
    cActionDef( const QDomElement *p_poElem );

    //! \brief Destructor
    /*! An empty destructor.
     */
    virtual ~cActionDef();

    //! \brief Returns with the <tt>name</tt> attribute of the ActionDef.
    /*! The <tt>name</tt> attribute is a unique identifier. It will be used in the LARA
     *  outputs when the list of identified Actions is generated.
     *  \return The unique name of the ActionDef as a QString.
     */
    QString                  name()                 const throw();

    //! \brief Returns with the <tt>upload</tt> attribute of the ActionDef.
    /*! The <tt>upload</tt> attribute infulences whether Actions based on this ActionDef
     *  will be uploaded to the result database or not. For the list of possible values
     *  of this attribute, see cActionUpload
     *  \sa cActionUpload
     *  \return The value of the Upload attribute of the ActionDef as an enum.
     */
    cActionUpload::teUpload  upload()               const throw();

    //! \brief Returns with an iterator to the first Fixed Attribute of the ActionDef.
    /*! Each ActionDef can have any number of Fixed Attributes. These are fixed values, so
     *  they are not extracted from an input log line, their value is predefined in the XML
     *  file containing the Action Definition. Fixed Attributes are stored in an std::map
     *  with the name of the Attribute as the key and the predefined value as the attribute
     *  value.
     *  \return The <tt>begin</tt> iterator for the map holding the Fixed Attributes
     */
    tiFixedAttribs           fixedAttributesBegin() const throw();

    //! \brief Returns with an iterator to the past-the-end Fixed Attribute of the ActionDef.
    /*! \sa fixedAttributesBegin
     *  \return The <tt>end</tt> iterator for the map holding the Fixed Attributes
     */
    tiFixedAttribs           fixedAttributesEnd()   const throw();

protected:
    //! Holds the <tt>name</tt> attribute of the ActionDef
    /*! \sa name()
     */
    QString                  m_qsName;

    //! Holds the <tt>upload</tt> attribute of the ActionDef
    /*! \sa upload()
     */
    cActionUpload::teUpload  m_enUpload;

    //! Holds the list of the names and values of Fixed Attributes
    /*! \sa fixedAttributesBegin() fixedAttributesEnd()
     */
    tmFixedAttribs           m_maFixedAttribs;

    //! \brief Internal function to initialize member variables
    /*! This is just a simple function to initialize the member variables with their default
     *  values.
     */
    virtual void             init()   throw();
};

#endif // ACTIONDEF_H
