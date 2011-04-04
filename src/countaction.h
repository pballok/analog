#ifndef COUNTACTION_H
#define COUNTACTION_H

#include <QString>
#include <QDomElement>
#include <vector>

//! \brief Stores a CountAction definition as defined in the XML configuration file
/*! CountAction is a special type of Action Definition. It is not a real Action, and as such,
 *  it doesn't have any Patterns or Results associated with it. Instead it just tells LARA
 *  to count how many times other Actions were found in the input logs, and display the
 *  result in the generated outputs. If more than one Action is listed within a CountAction,
 *  the result will be the total number of ALL those Actions added up.

 *  When an Action is listed to be counted, it is also possible to define an
 *  <tt>attribute</tt> for that Action. In such case, that Action Definition must have a
 *  captured attribute already defined with the same name, and that attribute must capture
 *  a numerical value. The CountAction will not count 1 (one) for every occurrence of such
 *  an Action, but instead the captured numerical value.
 */
class cCountAction
{
public:

    //! Holds an Action Name and an Attribute that defines one of the many Actions to count.
    typedef struct
    {
        //! Name of the Action to Count
        QString  qsName;
        //! \brief Name of an Action Attribute with a numerical value
        /*! If this Attribute name refers to a numerical attribute value, this Action will
         *  not be counted as one, but instead the value of the Attribute */
        QString  qsAttrib;
    } tsActionDef;

    //! Container type to hold all the Action Name and Attribute pairs that must be counted.
    typedef std::vector<tsActionDef>          tvActionsToCount;

    //! Iterator type for the CountAction container
    typedef tvActionsToCount::const_iterator  tiActionsToCount;

    //! \brief The default (empty) constructor.
    /*! It only calls the init() function to initialise the member variables with default
     *  values.
     */
    cCountAction();

    //! \brief Alternate constructor to initialize from XML Node
    /*! It initialises the member variables from the XML element received as parameter.
     *  \param p_poElem pointer to a "count_action" XML Node Element as defined in the
     *  lara_actions.xsd XML Schema.
     *  \sa cCountAction()
     */
    cCountAction( const QDomElement *p_poElem );

    //! \brief Destructor
    /*! An empty destructor.
     */
    ~cCountAction();

    //! Returns the <tt>name</tt> attribute of the CountAction
    /*! The <tt>name</tt> attribute is used by the cOutputCreator class, the result value of
     *  the CountAction will be listed under this name in the generated outputs.
     */
    QString           name()                const throw();

    //! \brief Returns with an iterator to the first ActionToCount definition.
    /*! Each CountAction Definition can have any number of ActionToCounts defined, these are
     *  a pair of an Action name and an Attribute name (see tsActionDef type). They are
     *  stored in a std::vector container.
     *  \return The <tt>begin</tt> iterator for the vector holding the ActionsToCount definitions
     */
    tiActionsToCount  actionsToCountBegin() const throw();

    //! \brief Returns with an iterator to the past-the-end ActionToCount definition.
    /*! \sa actionsToCountBegin()
     *  \return The <tt>end</tt> iterator for the vector holding the ActionsToCount definitions
     */
    tiActionsToCount  actionsToCountEnd()   const throw();

private:
    //! Holds the <tt>name</tt> attribute
    /*! \sa name()
     */
    QString           m_qsName;

    //! The container holding the ActionsToCount definitions
    /*! \sa actionsToCountBegin() actionsToCountEnd()
     */
    tvActionsToCount  m_veActionsToCount;

    //! \brief Internal function to initialize member variables
    /*! This is just a simple function to initialize the member variables with their default
     *  values.
     */
    void              init()                throw();
};

#endif // COUNTACTION_H
