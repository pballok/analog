#ifndef LOGTABLEMODEL_H
#define LOGTABLEMODEL_H

#include <QAbstractTableModel>
#include <QFile>
#include <QString>

class cLogTableModel : public QAbstractTableModel
{
Q_OBJECT
public:
    cLogTableModel( QObject *p_poParent = 0 );
    cLogTableModel( const QString &p_qsFileName, QObject *p_poParent = 0 );

    void openFile( const QString &p_qsFileName );
    QString line( unsigned int p_uiLine ) const;

signals:

public slots:

private:
    mutable QFile  m_obFile;
    unsigned int   m_uiNumLines;
};

#endif // DSLOGFILE_H
