#ifndef ACTIONDEFSINGLELINER_H
#define ACTIONDEFSINGLELINER_H

#include <QString>
#include <QDomElement>

#include "actiondef.h"

//! Represents a Single Liner Action as defined in the XML configuration file.
/*! Single Liner Actions always consist of one single line in the input logs. They don't have
 *  log lines marking the start and the end of the Action, instead the single log line is
 *  both the start and the end of the action. Because of this, Single Liner Actions can only
 *  have one Pattern associated to them, and their result (see cActionResult) is always
 *  predefined in the XML configuration file.
 *
 *  Inherits cActionDef
 */
class cActionDefSingleLiner : public cActionDef
{
public:
    //! \brief The default (empty) constructor.
    /*! It only calls the init() function to initialise the member variables with default
     *  values.
     */
    cActionDefSingleLiner();

    //! \brief Alternate constructor to initialize from XML Node
    /*! It initialises the member variables from the XML element received as parameter. It
     *  first calls cActionDef::cActionDef( const QDomElement *p_poElem ) then it continues
     *  with initialising the member variables that are specific to Single Liner Actions.
     *  \param p_poElem pointer to a Single Liner action definition XML Node Element as
     *  defined in the lara_actions.xsd XML Schema.
     *  \sa cActionDefSingleLiner()
     *  \sa cActionDef()
     */
    cActionDefSingleLiner( const QDomElement *p_poElem );

    //! \brief Destructor
    /*! An empty destructor.
     */
    virtual ~cActionDefSingleLiner();

    //! \brief returns with the Name of the Pattern of this Action
    /*! Since this is a SingleLiner Action, it has only one Pattern associated with it. This
     *  function returns with the unique name identifying that single Pattern, as defined in
     *  the XML configuration file.
     *  \return the name of the single Pattern of this Action as a QString
     */
    QString                  pattern() const throw();

    //! \brief returns with the pre-defined result value of this Action
    /*! SingleLiner Actions always have a predefined result value, since they consist of only
     *  a single Pattern. Finding that Pattern in the input logs can either mean a failed or
     *  a successful Action, the presence of other Patterns cannot influence the result.
     *  \return the predefined result value as an enum
     */
    cActionResult::teResult  result()  const throw();

protected:
    //! Holds the <tt>pattern</tt> attribute of the ActionDef
    /*! \sa pattern()
     */
    QString                  m_qsPattern;

    //! Holds the <tt>result</tt> attribute of the ActionDef
    /*! \sa result()
     */
    cActionResult::teResult  m_enResult;

    //! \brief Internal function to initialize member variables
    /*! This is just a simple function to initialize the member variables with their default
     *  values.
     */
    virtual void             init()    throw();
};

#endif // ACTIONDEFSINGLELINER_H
