#ifndef DSLOGFILE_H
#define DSLOGFILE_H

#include <QObject>
#include <QFile>
#include <QString>

class cDSLogFile : public QObject
{
Q_OBJECT
public:
    cDSLogFile();
    cDSLogFile( const QString &p_qsFileName );

    void openFile( const QString &p_qsFileName );
    QString line( unsigned int p_uiLine ) const;

signals:

public slots:

private:
    mutable QFile m_obFile;
};

#endif // DSLOGFILE_H
