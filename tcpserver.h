#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include <qjson/parser.h>
#include <qjson/serializer.h>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    
signals:
    void connectGumba();
    void disconnectGumba();
    void startRoboApp();
    void toggleRTS();

    void writeToTerminal(const QString &terminalString);

private:
    QTcpServer *m_tcpServer;
    QList <QTcpSocket*> clientList;

private slots:
    void clientConnected();
    void readData();
    void clientDisconnected();

public slots:
    void sendData(QString target, QString command);
};
    

#endif // TCPSERVER_H
