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

    QString                  pattern() const throw();
    cActionResult::teResult  result()  const throw();

protected:
    QString                  m_qsPattern;
    cActionResult::teResult  m_enResult;

    virtual void             init()    throw();
};

#endif // ACTIONDEFSINGLELINER_H
