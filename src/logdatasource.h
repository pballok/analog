#ifndef LOGDATASOURCE_H
#define LOGDATASOURCE_H

#include <QString>
#include <QStringList>

#include <sevexception.h>

//! \brief Prepares the Input Log Files for analysis.
/*! Input Log Files are defined in the various XML configuration files. First the full path
 *  to the log files has to be created. If the file name refers to multiple files (contains
 *  '*' or '?' characters) then the list of the actual file-names must be created. Finally
 *  all the files must be copied to the temporary directory (as defined in the preferences),
 *  possibly compressed or encoded files must also be restored to their original form so the
 *  log analysis can read them.
 */
class cLogDataSource
{
public:
    //! \brief Constructor that performs the entire preparation process of the given files.
    /*! \param p_qsInputDir path of the Input Directory where the Input Log Files can be
     *                      found
     *  \param p_qsFiles    Input Log File name, that can refer to multiple files (can
     *                      contain '*' or '?' characters)
     */
    cLogDataSource( const QString &p_qsInputDir, const QString &p_qsFiles ) throw();

    //! \brief Destructor that removes the temporary files created during preparation.
    ~cLogDataSource();

    //! \brief Returns the list of prepared Input Log Files
    /*! The list of prepared files is created by the prepareFiles() function, and can contain
     *  more than one element if the originally specified file-name contained '*' or '?'
     *  characters. They all point to files in the Temporary Directory, since they are all
     *  results of the preparation process. This list will be used by cLogAnalyser, it will
     *  search for the definied Patterns in these files.
     *  \sa prepareFiles()
     */
    QStringList logFileList() const throw();

    //! \brief Returns the list of original Input Log Files
    /*! The list of original files is created by the parseFileNames() function, and can
     *  contain more than one element if the originally specified file-name contained '*' or
     *  '?' characters. They all point to files in the Input Directory. This list will be
     *  needed by cOutputCreator so the generated outputs can point to the actual log files
     *  where the identified Actions were found.
     *  \sa parseFileNames()
     */
    QStringList origFileList() const throw();

private:
    //! \brief Determines list of actual Input Log File names
    /*! Since the input file name can refer to multiple files (if it contains '*' or '?'
     *  characters) the list of actual Input Log File names can have more than one element.
     *  This list is created by checking the filesystem and get a list of file names that
     *  match the given file-name mask. The full path to the Input Files also has to be
     *  created from several pieces. The Input Directory is defined in the LARA configuration
     *  file, this path is then followed by the p_qsInputDir parameter, and finally the
     *  file-name mask received in p_qsFiles may contain additional directories as well.
     *  All these directories are appended after each other to form the full path, then the
     *  list of matching file names is determined using Qt's QDir class.
     *  \param p_qsInputDir path of the Input Directory where the Input Log Files can be
     *                      found
     *  \param p_qsFiles    Input Log File name, that can refer to multiple files (can
     *                      contain '*' or '?' characters)
     */
    void    parseFileNames( const QString &p_qsInputDir, const QString &p_qsFiles ) throw();

    //! \brief Prepares Input Log Files so they can be read and analysed
    /*! Preparing the Input Log Files means copying them to the Temporary Directory (as
     *  defined in the LARA configuration file) and unpack or decode them as necessary. The
     *  preparation method needed (simple copy, or unpack, decode, etc) is determined from
     *  the file name. If a file name ends in '.gz' or '.zip' it will be unpacked, if the
     *  name has 'sysError' in it, it will be decoded, etc. The names of the prepared files
     *  are pushed to the m_slTempFiles list. The resulting files are simple text files that
     *  can be processed by the cLogAnalyser, and will be removed by the destructor
     *  ~cLogDataSource when they're no longer needed.
     */
    void    prepareFiles() throw();

    //! \brief Unpacks a file using the "unzip" external program
    /*! This function receives a file name pointing to a file in the Output Directory. The
     *  file is then copied to the Temporary Directory and unpacked using "unzip". This
     *  function assumes that the file packed into the original ".zip" file has the same name
     *  as the packed file, but has a ".log" at the end instead of ".zip".
     *  \return The name of the unpacked file as a QString.
     */
    QString unzipFile( const QString &p_qsFileName ) throw( cSevException );

    //! \brief Unpacks a file using the "gzip" external program
    /*! This function receives a file name pointing to a file in the Output Directory. The
     *  file is then copied to the Temporary Directory and unpacked using "gzip". This
     *  function assumes that the file packed into the original ".gz" file has the same name
     *  as the packed file, but without the ".gz" part.
     *  \return The name of the unpacked file as a QString.
     */
    QString gunzipFile( const QString &p_qsFileName ) throw( cSevException );

    //! \brief Simply copies the given file to the Temporary Directory
    /*! This function receives a file name pointing to a file in the Output Directory. The
     *  file is then copied to the Temporary Directory.
     *  \return The name of the copied file as a QString.
     */
    QString copyFile( const QString &p_qsFileName ) throw( cSevException );

    //! \brief Decodes a file using a custom decoding algorythm
    /*! sysError log files are text files, each line consists of several 'tags' that are
     *  separated by commas. In each line the 5th, 9th, 10th and 11th tags are encrypted, so
     *  these tags must be de-crypted, the rest must remain untouched. The first line of the
     *  file is just a header, it contains no encrypted information. This function reads
     *  the sysError file line-by-line, splits up each line using the ',' character as the
     *  separator, calls the decodeString() function to perform decoding on the encrypted tags.
     *  Finally it creates an output file that have all the tags de-coded.
     *  \return The name of the decoded file as a QString.
     *  \sa decodeString()
     */
    QString decodeFile( const QString &p_qsFileName ) throw( cSevException );

    //! \brief Decodes a single string using a custom decoding algorythm
    /*! The input string is decoded using a 8-bytes long Key. The algorythm is a simple loop
     *  that walks over the input string character-by-character and the Key byte-by-byte. It
     *  performs a bitwise XOR operation between the current character of the input string,
     *  and the current byte of the Key. The resulting character is the decoded character, it
     *  is appended to the output string.
     *  \param p_qsInput The input string that needs to be decoded
     *  \return The decoded string as a QString
     *  \sa decodeFile()
     */
    QString decodeString( const QString &p_qsInput ) throw();

    //! \brief Holds the names of prepared files located in the Temporary Directory
    /*! \sa logFileList()
     *  \sa prepareFiles()
     *  \sa ~cLogDataSource()
     */
    QStringList m_slTempFiles;

    //! \brief Holds the names of original Input Log Files located in the Input Directory
    /*! \sa origFileList()
     *  \sa prepareFiles()
     */
    QStringList m_slOrigFiles;
};

#endif // LOGDATASOURCE_H
