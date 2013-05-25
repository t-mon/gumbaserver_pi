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
    void newLineToParse(const QString &line);
    void connectGumba();
    void disconnectGumba();
    void startRoboApp();
    void toggleRTS();

    void movementCommand(const QString &gumbaMoveCommand);

//    void movementForward();
//    void movementBackward();
//    void movementLeft();
//    void movementRight();
//    void movementTurnLeft();
//    void movementTurnRight();
    void movementStop();

//    void speedChanged(const int &speedLevel);

    void servoInit();
    void servoChanged(const int &servoNumber, const QString &pwm);
    void writeToTerminal(const QString &terminalString);

private:
    QTcpServer *m_tcpServer;
    QList <QTcpSocket*> clientList;
    QString m_tcpBuffer;

private slots:
    void clientConnected();
    void readData();
    void parseLine(const QString &line);
    void clientDisconnected();

public slots:
    void sendData(QString target, QString command);

};
    

#endif // TCPSERVER_H
