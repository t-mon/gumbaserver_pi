#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "tcpserver.h"
#include "serialconnection.h"
#include "servocontrol.h"

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);
    
private:
    TcpServer *m_server;
    SerialConnection *m_robot;
    ServoControl *m_servo;

signals:
    
public slots:
    
};

#endif // CORE_H
