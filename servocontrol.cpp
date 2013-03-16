#include "servocontrol.h"
#include <QDebug>

ServoControl::ServoControl(QObject *parent) :
    QObject(parent)
{
    initServoProcess = new QProcess(this);
    processString.clear();

    connect(initServoProcess,SIGNAL(readyRead()),this,SLOT(initServoProcessReadStandardOutput()));
    connect(initServoProcess,SIGNAL(readyReadStandardError()),this,SLOT(initServoProcessReadStandardError()));
    connect(initServoProcess,SIGNAL(finished(int)),this,SLOT(initServoProcessFinished(int)));

}

void ServoControl::initServo(){
    initServoProcess->start("/root/scripts/initServoblaster.sh");
    initServoProcess->waitForFinished();
}


// Servo number    GPIO number   Pin in P1 header
//      0               4             P1-7
//      1              17             P1-11
//      2              18             P1-12
//      3              21             P1-13
//      4              22             P1-15
//      5              23             P1-16
//      6              24             P1-18
//      7              25             P1-22


void ServoControl::setServo(int servoNumber, int pwm)
{
    QProcess writeServo;
    QString cmd;
    switch(servoNumber){
    case 0:
        cmd="0=" + QString::number(pwm);
        break;
    case 1:
        cmd="1=" + QString::number(pwm);
        break;
    case 2:
        cmd="2=" + pwm;
        break;
    case 3:
        cmd="3=" + QString::number(pwm);
        break;
    case 4:
        cmd="4=" + QString::number(pwm);
        break;
    case 5:
        cmd="5=" + QString::number(pwm);
        break;
    case 6:
        cmd="6=" + QString::number(pwm);
        break;
    case 7:
        cmd="7=" + QString::number(pwm);
        break;
    }
    writeServo.start("echo", QStringList() << cmd << ">" << "/dev/servoblaster");
    writeServo.waitForFinished();
}


void ServoControl::initServoProcessFinished(const int &exitStatus)
{
    qDebug() << processString;
    emit sendToClient("Terminal",processString);
    if(exitStatus == 0){
        emit sendToClient("Terminal","Servoblaster initialized successfully!");
        qDebug() << "Servoblaster initialized successfully!";
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
