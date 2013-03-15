#include <QDebug>
#include <QString>
#include <qjson/parser.h>
#include <QMap>
#include <QVariant>
#include <QVariantMap>

#include "serialconnection.h"


SerialConnection::SerialConnection(QObject *parent) :
    QObject(parent)
{
    gumbaPortSettings.BaudRate = BAUD38400;
    gumbaPortSettings.DataBits = DATA_8;
    gumbaPortSettings.FlowControl = FLOW_XONXOFF;
    gumbaPortSettings.Parity = PAR_NONE;
    gumbaPortSettings.StopBits = STOP_1;
    gumbaPortSettings.Timeout_Millisec = 500;

    gumba = new QextSerialPort("/dev/ttyUSB0",gumbaPortSettings);
    gumba->flush();
    connect(gumba,SIGNAL(readyRead()),this,SLOT(gumbaPackageAvalable()));
    connect(this,SIGNAL(gumbaPackageReceived(QString)),this,SLOT(parseNewLine(QString)));
}

void SerialConnection::connectGumba()
{

    if(gumba->open(QextSerialPort::ReadWrite) == true){
        qDebug() << "Port open!";
        toggleRTS();
        gumba->write("k\n");
        gumba->flush();
        gumba->write("i\n");
        gumba->flush();
    }else if(gumba->open(QextSerialPort::ReadWrite) == false){
        qDebug() << "Port not opend!";
    }
}

void SerialConnection::startGumbaApplication()
{
    gumba->write("s\n");
    qDebug() << "Start robot application";
    gumba->flush();
}

void SerialConnection::movementForward()
{
    gumba->write("w\n");
    qDebug() << "Start robot application";
    gumba->flush();
}

void SerialConnection::movementBackward()
{
    gumba->write("s\n");
    qDebug() << "Start robot application";
    gumba->flush();
}

void SerialConnection::movementLeft()
{
    gumba->write("a\n");
    qDebug() << "Start robot application";
    gumba->flush();
}

void SerialConnection::movementRight()
{
    gumba->write("d\n");
    qDebug() << "Start robot application";
    gumba->flush();
}

void SerialConnection::movementTurnLeft()
{
    gumba->write("q\n");
    qDebug() << "Start robot application";
    gumba->flush();
}

void SerialConnection::movementTurnRight()
{
    gumba->write("e\n");
    qDebug() << "Start robot application";
    gumba->flush();
}

void SerialConnection::movementStop()
{
    gumba->write("x\n");
    qDebug() << "Start robot application";
    gumba->flush();
}

void SerialConnection::toggleRTS()
{
    gumba->setRts(true);
    gumba->setRts(false);
    qDebug() << "RESET...toggle RTS!";
}

void SerialConnection::gumbaPackageAvalable()
{
    m_gumbaBuffer.append(gumba->readAll());
    int newLinePosGumba = m_gumbaBuffer.indexOf('\n')+1;
    emit gumbaPackageReceived(m_gumbaBuffer.left(newLinePosGumba));
    m_gumbaBuffer = m_gumbaBuffer.right(m_gumbaBuffer.length() - newLinePosGumba);
}

void SerialConnection::parseNewLine(const QString &gumbaString)
{

    if(gumbaString.isEmpty()){
        return;
    }

    emit sendToClient("GumbaData",gumbaString);

    if (gumbaString.at(0) == '{'){
        QVariantMap sensors;
        QJson::Parser parser;
        sensors = parser.parse(gumbaString.toAscii()).toMap();

        if((gumbaString.at(0) == '{') && (gumbaString.at(1) == '"') && (gumbaString.at(2) == 'e')){
            if(sensors.value("energy").toMap().value("batery").toInt() == 1){
                double ubat = sensors.value("energy").toMap().value("voltage").toDouble();
                double iMotorR = sensors.value("energy").toMap().value("motor_r").toDouble();
                double iMotorL = sensors.value("energy").toMap().value("motor_l").toDouble();
                double lightR = sensors.value("energy").toMap().value("light_r").toDouble();
                double lightL = sensors.value("energy").toMap().value("light_l").toDouble();
            }
        }

        if((gumbaString.at(0) == '{') && (gumbaString.at(1) == '"') && (gumbaString.at(2) == 'o')){
            if(sensors.value("obstacles").toMap().value("left").toInt() == 0){
                emit obstacleLeftOff();
            } if(sensors.value("obstacles").toMap().value("left").toInt() == 1){
                emit obstacleLeftOn();
            } if(sensors.value("obstacles").toMap().value("right").toInt() == 0){
                emit obstacleRightOff();
            } if(sensors.value("obstacles").toMap().value("right").toInt() == 1){
                emit obstacleRightOn();
            }
        }
        if((gumbaString.at(0) == '{') && (gumbaString.at(1) == '"') && (gumbaString.at(2) == 'b')){
            if(sensors.value("bumper").toMap().value("left").toInt() == 0){
                emit bumperLeftReleased();
            } if(sensors.value("bumper").toMap().value("left").toInt() == 1){
                emit bumperLeftPressd();
            } if(sensors.value("bumper").toMap().value("right").toInt() == 0){
                emit bumperRightReleased();
            } if(sensors.value("bumper").toMap().value("right").toInt() == 1){
                emit bumperRightPressed();
            }
        }
    }
}
