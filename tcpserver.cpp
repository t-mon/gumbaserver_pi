#include <QObject>
#include <QMap>
#include <QVariant>
#include <QVariantMap>
#include <QTcpSocket>

#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QObject(parent)
{
    m_tcpServer = new QTcpServer(this);
    m_tcpServer->listen(QHostAddress::Any, 2222);
    qDebug() << "-->Server created";
    connect(m_tcpServer,SIGNAL(newConnection()),this,SLOT(clientConnected()));
}

void TcpServer::clientConnected()
{
    QTcpSocket *client = m_tcpServer->nextPendingConnection();
    qDebug() << "New Client Connected: " << client->peerAddress().toString() << "over Port " << client->peerPort();
    connect(client,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(client,SIGNAL(disconnected()),this,SLOT(clientDisconnected()));
    clientList.append(client);
}

void TcpServer::readData()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    QByteArray dataIn;

    dataIn = client->readAll();

    QVariantMap map;
    QJson::Parser parser;
    map = parser.parse(dataIn).toMap();

    // ====================================================================================
    // Roboter application
    if((map.value("target").toString() == "RoboterApplication") && (map.value("command").toString() == "start")){
        emit startRoboApp();
    }
    if((map.value("target").toString() == "RoboterApplication") && (map.value("command").toString() == "connect")){
        emit connectGumba();
    }
    if((map.value("target").toString() == "RoboterApplication") && (map.value("command").toString() == "disconnect")){
        emit disconnectGumba();
    }
    if((map.value("target").toString() == "RoboterApplication") && (map.value("command").toString() == "toggle")){
        emit toggleRTS();
    }

    // ====================================================================================
    // Roboter movement
    if((map.value("target").toString() == "RoboterMovement") && (map.value("command").toString() == "forward")){
        emit movementForward();
    }
    if((map.value("target").toString() == "RoboterMovement") && (map.value("command").toString() == "backward")){
        emit movementBackward();
    }
    if((map.value("target").toString() == "RoboterMovement") && (map.value("command").toString() == "left")){
        emit movementLeft();
    }
    if((map.value("target").toString() == "RoboterMovement") && (map.value("command").toString() == "right")){
        emit movementRight();
    }
    if((map.value("target").toString() == "RoboterMovement") && (map.value("command").toString() == "turnLeft")){
        emit movementTurnLeft();
    }
    if((map.value("target").toString() == "RoboterMovement") && (map.value("command").toString() == "turnRight")){
        emit movementTurnRight();
    }
    if((map.value("target").toString() == "RoboterMovement") && (map.value("command").toString() == "stop")){
        emit movementStop();
    }
    if((map.value("target").toString() == "RoboterSpeed")){
        qDebug() << map.value("command").toInt();
        emit speedChanged(map.value("command").toInt());
    }
    // ====================================================================================
    // SERVO

    // Servo number    GPIO number   Pin in P1 header
    //      0               4             P1-7
    //      1              17             P1-11
    //      2              18             P1-12
    //      3              21             P1-13
    //      4              22             P1-15
    //      5              23             P1-16
    //      6              24             P1-18
    //      7              25             P1-22

    if((map.value("target").toString() == "Servo") && (map.value("command").toString() == "init")){
        emit servoInit();
    }
    if((map.value("target").toString() == "Servo0")){
        QString pwm=map.value("command").toString();
        qDebug() << "servo 0 set to" << pwm;
        emit servoChanged(0,pwm);
    }
    if((map.value("target").toString() == "Servo1")){
        QString pwm=map.value("command").toString();
        qDebug() << "servo 1 set to" << pwm;
        emit servoChanged(1,pwm);
    }
    if((map.value("target").toString() == "Servo2")){
        QString pwm=map.value("command").toString();
        qDebug() << "servo 2 set to" << pwm;
        emit servoChanged(2,pwm);
    }

}

void TcpServer::clientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    qDebug() << "-->Client disconnected" << client->peerAddress().toString();

}

void TcpServer::sendData(QString target, QString command)
{
    foreach(QTcpSocket *client,clientList){

        QVariantMap map;
        map.insert("target",target);
        map.insert("command",command);

        QJson::Serializer serializer;
        QByteArray dataOut = serializer.serialize(map);
        //qDebug() << "-->Send Data: " << dataOut;
        client->write(dataOut);
    }
}
