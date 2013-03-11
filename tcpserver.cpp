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
    if((map.value("target").toString() == "RoboterApplication") && (map.value("command").toString() == "start")){
        emit startRoboApp();
        qDebug() << "-->emit SIGNAL: Gumba, start Robot Application";
    }
    if((map.value("target").toString() == "RoboterApplication") && (map.value("command").toString() == "connect")){
        emit connectGumba();
        qDebug() << "-->emit SIGNAL: Gumba, start Robot Application";
    }
    if((map.value("target").toString() == "RoboterApplication") && (map.value("command").toString() == "disconnect")){
        emit disconnectGumba();
        qDebug() << "-->emit SIGNAL: Gumba, start Robot Application";
    }
    if((map.value("target").toString() == "RoboterApplication") && (map.value("command").toString() == "toggle")){
        emit toggleRTS();
        qDebug() << "-->emit SIGNAL: Gumba, toggle RTS";
    }
}

void TcpServer::clientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    qDebug() << "-->Client disconnected" << client->peerAddress().toString();
    //emit writeToTerminal("client disconnected: " + client->peerAddress().toString());

}

void TcpServer::sendData(QString target, QString command)
{
    foreach(QTcpSocket *client,clientList){

        QVariantMap map;
        map.insert("target",target);
        map.insert("command",command);

        QJson::Serializer serializer;
        QByteArray dataOut = serializer.serialize(map);
        qDebug() << "-->Send Data: " << dataOut;
        client->write(dataOut);
    }
}
