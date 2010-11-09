#ifndef PATTERN_H
#define PATTERN_H

#include <QString>
#include <QStringList>
#include <QDomElement>
#include <QRegExp>

//! Represents a Pattern (regular expression) used to identify actions in the input log file.

/*!
 * cPattern is basically a regular expression that can match the input log lines.
 * It has a unique Name, so Action Definitions can refer to what pattern(s) they
 * consist of. It uses PCRE compatible regular expression, and can capture parts
 * of the matched text.
 */

class cPattern
{
public:
    //! \brief Empty constructor
    /*!
     *
     * The default (empty) constructor. It only initialises the member
     * variables with default values.
     */
    cPattern();

    //! \brief Alternate constructor to initialize from XML Node
    /*!
     * \param p_poElem pointer to a "pattern" XML Node Element
     * \sa cPattern()
     * A constructor that initialises the member variables from a "pattern"
     * XML Node Element.
     */
    cPattern( const QDomElement *p_poElem );

    //! \brief Destructor
    ~cPattern();

    QString      name() const throw();
    QString      pattern() const throw();
    QStringList  captures() const throw();
    QStringList  capturedTexts( const QString &p_qsLogLine ) const throw();

private:

    QString      m_qsName;
    QRegExp      m_obRegExp;
    QStringList  m_slCaptures;

    void         init()                 throw();
};

#endif // PATTERN_H
