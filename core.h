#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "tcpserver.h"
#include "serialconnection.h"

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);
    
private:
    TcpServer *m_server;
    SerialConnection *m_robot;

signals:
    
public slots:
    
};

#endif // CORE_H
