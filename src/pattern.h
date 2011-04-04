#ifndef PATTERN_H
#define PATTERN_H

#include <QString>
#include <QStringList>
#include <QDomElement>
#include <QRegExp>

//! \brief Represents a Pattern (regular expression) used to identify actions in the input log file.
/*! cPattern is basically a regular expression that can match input log lines. It uses
 *  <a href="http://perldoc.perl.org/perlre.html#Regular-Expressions">PCRE</a> compatible
 *  regular expression syntax, and can capture parts of the matched text as well.
 *  Every Pattern has a unique Name, so Action Definitions (cActionDef) can refer to what
 *  pattern(s) they consist of.
 */
class cPattern
{
public:
    //! \brief The default (empty) constructor.
    /*! It only calls the init() function to initialise the member variables with default
     *  values.
     */
    cPattern();

    //! \brief Alternate constructor to initialize from XML Node
    /*! It initialises the member variables from the XML element received as parameter.
     *  \param p_poElem pointer to a "pattern" XML Node Element as defined in the
     *  lara_actions.xsd XML Schema.
     *  \sa cPattern()
     */
    cPattern( const QDomElement *p_poElem );

    //! \brief Destructor
    /*! An empty destructor.
     */
    ~cPattern();

    //! \brief Returns with the <tt>name</tt> attribute of the Pattern.
    /*! The <tt>name</tt> attribute is a unique identifier. It is used by the different
     *  Action classes to specify which Pattern(s) define the given Action. This way the
     *  Action definition doesn't have to contain the full regular expression including the
     *  list of Captured Attributes, etc. Especially if multiple Actions use the same
     *  Pattern, these unique Pattern names make Action definitions a lot simpler.
     *  \return The unique name of the Pattern as a QString.
     */
    QString      name() const throw();

    //! \brief Returns with the <tt>pattern</tt> attribute of the Pattern.
    /*! The <tt>pattern</tt> attribute is the regular expression that is used to find
     *  log lines within the input log files. It uses the
     *  <a href="http://perldoc.perl.org/perlre.html#Regular-Expressions">PCRE</a> syntax
     *  including <em>capturing</em> parts of the matched text as well.
     *  \return The regular expression as a QString.
     */
    QString      pattern() const throw();

    //! \brief Returns the list of names (<em>not</em> values) of Captured Attributes.
    /*! Each Pattern can have any number of Captured Attributes defined to it in the XML
     *  configuration file. Each Captured Attribute has a name (the value comes from the
     *  matched regular expression) and these names are stored within a string list in the
     *  same order as they were defined in the XML file.
     *  \return The names of all the defined Captured Attributes as a QStringList.
     */
    QStringList  captures() const throw();

    //! \brief Returns the captured texts if the regular expression matches the input string.
    /*! If the regular expression of the Pattern matches the input string and the regular
     *  expression contains capture text commands ('(' and ')' characters) the values of
     *  the successfully captured texts are returned. For example if the regular expression
     *  is <tt>"The (\S+) is (\S+)"</tt> and the input string is <tt>"The car is blue"</tt>
     *  then the returned list will have two items: <tt>"car"</tt> and <tt>"blue"</tt>. The
     *  result list will contain the captured texts in the same order as they occurred in the
     *  input string.
     *  \param p_qsLogLine the input string to capture texts from
     *  \return The list of captured texts as a QStringList or an empty list if the input
     *  string did not match the regular expression.
     */
    QStringList  capturedTexts( const QString &p_qsLogLine ) const throw();

private:

    //! Holds the <tt>name</tt> attribute of the Pattern
    /*! \sa name()
     */
    QString      m_qsName;

    //! Holds the <tt>pattern</tt> attribute of the Pattern
    /*! The <tt>pattern</tt> attribute is stored as a QRegExp object to make matching and
     *  capturing simpler.
     *  \sa pattern() capturedTexts()
     */
    QRegExp      m_obRegExp;

    //! Holds the list of the names of Captured Attributes
    /*! \sa captures() capturedTexts()
     */
    QStringList  m_slCaptures;

    //! \brief Internal function to initialize member variables
    /*! This is just a simple function to initialize the member variables with their default
     *  values.
     */
    void         init()                 throw();
};

#endif // PATTERN_H
