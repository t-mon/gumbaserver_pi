#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include <QObject>
#include "qextserialport.h"

class SerialConnection : public QObject
{
    Q_OBJECT
public:
    explicit SerialConnection(QObject *parent = 0);


private:
    int serial_device;
    PortSettings gumbaPortSettings;
    QextSerialPort *gumba;
    QString gumbaHoleText;
    QString m_gumbaBuffer;


signals:
    void obstacleLeftOn();
    void obstacleLeftOff();
    void obstacleRightOn();
    void obstacleRightOff();
    void bumperLeftPressd();
    void bumperLeftReleased();
    void bumperRightPressed();
    void bumperRightReleased();
    void gumbaPackageReceived(QString);
    void gumbaDataReceived(QString);

    void sendToClient(QString,QString);

private slots:
    void parseNewLine(const QString & gumbaString);
    void gumbaPackageAvalable();
    
public slots:
    void connectGumba();
    void disconnectGumba();
    void toggleRTS();
    void startGumbaApplication();

    void movementCommand(const QString &gumbaMoveCommand);
//    void movementBackward();
//    void movementLeft();
//    void movementRight();
//    void movementTurnLeft();
//    void movementTurnRight();
//    void movementStop();

//    void speedChanged(const int &speedLevel);

};

#endif // SERIALCONNECTION_H
