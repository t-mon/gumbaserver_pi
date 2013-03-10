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
}

void SerialConnection::connectToRobot()
{

    if(gumba->open(QextSerialPort::ReadWrite) == true){
        qDebug() << "Port open!";
        toggleRTS();
    }else if(gumba->open(QextSerialPort::ReadWrite) == false){
        qDebug() << "Port not opend!";
    }

    QString readyString = gumba->readLine();
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
    //qDebug() << "got Buffer" << m_gumbaBuffer;
    int newLinePosGumba = m_gumbaBuffer.indexOf('\n')+1;
    qDebug() << "newline index" << newLinePosGumba;
    emit gumbaPackageReceived(m_gumbaBuffer.left(newLinePosGumba));
    m_gumbaBuffer = m_gumbaBuffer.right(m_gumbaBuffer.length() - newLinePosGumba);
}

void SerialConnection::parseNewLine(const QString &gumbaString)
{
    qDebug() << "Line to parse: _--------------" << gumbaString;

    //    if(gumbaString.at(0) == '[' && gumbaString.at(1) == 'R' && gumbaString.at(2) == 'P' ){
    //        qDebug() << "Got [READY] string...";

    //        gumba->write("\n");
    //    }


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

                qDebug() << "Batery Voltage: " << ubat;
                qDebug() << "Motor right: " << iMotorR;
                qDebug() << "Motor left: " << iMotorL;
                qDebug() << "Light right: " << lightR;
                qDebug() << "Light left: " << lightL;

                //                ui->motorRightLable->setText("Motor Right: " + QString::number(iMotorR));
                //                ui->motorLeftLable->setText("Motor Left: " + QString::number(iMotorL));
                //                ui->lightLeftLable->setText("Light Left: " + QString::number(lightL));
                //                ui->lightRightLable->setText("Light Right: " + QString::number(lightR));


                //                ubat = ubat/100;
                //                if (ubat != 0){
                //                    if(ubat > 5.8){
                //                        ui->bateryLineEdit->setStyleSheet("background-color:green;");
                //                    }else if (ubat <= 5.8){
                //                        ui->bateryLineEdit->setStyleSheet("background-color:red;");
                //                    }
                //                    ui->bateryLineEdit->clear();
                //                    ui->bateryLineEdit->setText(QString::number(ubat) +"V");
                //                }

            }
        }

        if((gumbaString.at(0) == '{') && (gumbaString.at(1) == '"') && (gumbaString.at(2) == 'o')){
            if(sensors.value("obstacles").toMap().value("left").toInt() == 0){
                emit obstacleLeftOff();
                //ui->obstacleLeft->setStyleSheet("background-color:green;");
                qDebug() << "Obstacle Left OFF";
            } if(sensors.value("obstacles").toMap().value("left").toInt() == 1){
                emit obstacleLeftOn();
                //ui->obstacleLeft->setStyleSheet("background-color:red;");
                qDebug() << "Obstacle Left ON";
            } if(sensors.value("obstacles").toMap().value("right").toInt() == 0){
                emit obstacleRightOff();
                //ui->obstacleRight->setStyleSheet("background-color:green;");
                qDebug() << "Obstacle Right OFF";
            } if(sensors.value("obstacles").toMap().value("right").toInt() == 1){
                emit obstacleRightOn();
                //ui->obstacleRight->setStyleSheet("background-color:red;");
                qDebug() << "Obstacle Right ON";
            }
        }
        if((gumbaString.at(0) == '{') && (gumbaString.at(1) == '"') && (gumbaString.at(2) == 'b')){
            if(sensors.value("bumper").toMap().value("left").toInt() == 0){
                emit bumperLeftReleased();
                qDebug() << "Bumper Left OFF";
            } if(sensors.value("bumper").toMap().value("left").toInt() == 1){
                emit bumperLeftPressd(true);
                qDebug() << "Bumper Left ON";
            } if(sensors.value("bumper").toMap().value("right").toInt() == 0){
                emit bumperRightReleased();
                qDebug() << "Bumper Right OFF";
            } if(sensors.value("bumper").toMap().value("right").toInt() == 1){
                emit bumperRightPressed();
                qDebug() << "Bumper Right ON";
            }
        }
    }
    if(gumbaString.at(0) == '[' || gumbaString.at(0) == '#' ){

        qDebug() << "       " + gumbaString;
    }


}
