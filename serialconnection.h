#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include <QObject>

class SerialConnection : public QObject
{
    Q_OBJECT
public:
    explicit SerialConnection(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SERIALCONNECTION_H
