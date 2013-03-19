#include "servocontrol.h"
#include <QDebug>
#include <QFile>

ServoControl::ServoControl(QObject *parent) :
    QObject(parent)
{
    initServoProcess = new QProcess(this);
    processString.clear();
    //servoSocket = new QLocalSocket(this);

    servoblaster = new QFile("/dev/servoblaster");


    connect(initServoProcess,SIGNAL(readyRead()),this,SLOT(initServoProcessReadStandardOutput()));
    connect(initServoProcess,SIGNAL(readyReadStandardError()),this,SLOT(initServoProcessReadStandardError()));
    connect(initServoProcess,SIGNAL(finished(int)),this,SLOT(initServoProcessFinished(int)));

}

void ServoControl::initServo(){

    qDebug() << "try to open servoblaster...";
    emit sendToClient("Terminal","try to open servoblaster...");

    if(servoblaster->isOpen()){
        qDebug() << "servoblaster allready open!";
        emit sendToClient("Terminal","servoblaster allready open!");
        return;
    }

    if (!servoblaster->open(QIODevice::WriteOnly | QIODevice::Text)){
        emit sendToClient("Terminal","ERROR: could not open /dev/servoblaseter");
        emit sendToClient("Terminal","start initskript...");

        qDebug() << "ERROR: could not open /dev/servoblaseter";
        qDebug() << "start initskript...";

        initServoProcess->start("/root/scripts/initServoblaster.sh");
        initServoProcess->waitForFinished();
    }else{
        emit sendToClient("Terminal","/dev/servoblaseter ... open!");
        qDebug() << "/dev/servoblaseter ... open!";
    }

}


void ServoControl::setServo(const int &servoNumber, const QString &pwm)
{
    // Servo number    GPIO number   Pin in P1 header
    //      0               4             P1-7
    //      1              17             P1-11
    //      2              18             P1-12
    //      3              21             P1-13
    //      4              22             P1-15
    //      5              23             P1-16
    //      6              24             P1-18
    //      7              25             P1-22

    QString cmd;
    switch(servoNumber){
    case 0:
        cmd="0=" + pwm;
        break;
    case 1:
        cmd="1=" + pwm;
        break;
    case 2:
        cmd="2=" + pwm;
        break;
    case 3:
        cmd="3=" + pwm;
        break;
    case 4:
        cmd="4=" + pwm;
        break;
    case 5:
        cmd="5=" + pwm;
        break;
    case 6:
        cmd="6=" + pwm;
        break;
    case 7:
        cmd="7=" + pwm;
        break;
    }
    qDebug() << "Write to servoblaster:" << cmd;
    cmd = cmd + "\n";
    servoblaster->write(cmd.toAscii());
    servoblaster->flush();

}


void ServoControl::initServoProcessFinished(const int &exitStatus)
{
    qDebug() << processString;
    emit sendToClient("Terminal",processString);
    if(exitStatus == 0){
        emit sendToClient("Terminal","Servoblaster initialized successfully!");
        qDebug() << "Servoblaster initialized successfully!";
        if (!servoblaster->open(QIODevice::WriteOnly | QIODevice::Text)){
            emit sendToClient("Terminal","ERROR: could not open /dev/servoblaseter");
            emit sendToClient("Terminal","start initskript...");

            qDebug() << "ERROR: could not open /dev/servoblaseter";
            qDebug() << "start initskript...";

        }else{
            emit sendToClient("Terminal","/dev/servoblaseter ... open!");
            qDebug() << "/dev/servoblaseter ... open!";
        }

    }else{
        emit sendToClient("Terminal","ERROR: Servoblaster not inizialized.");
        qDebug() << "ERROR: Servoblaster not inizialized.";
    }
    processString.clear();



}

void ServoControl::initServoProcessReadStandardOutput()
{
    processString.append(initServoProcess->readAll());
}

void ServoControl::initServoProcessReadStandardError()
{
    processString.append(initServoProcess->readAllStandardError());
}
