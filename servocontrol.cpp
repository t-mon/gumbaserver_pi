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
    switch(servoNumber){
    case 0:
        writeServo.start("echo", QStringList() << "0=" + QString::number(pwm) << "> /dev/servoblaster");
        break;
    case 1:
        writeServo.start("echo", QStringList() << "1=" + QString::number(pwm) << "> /dev/servoblaster");
        break;
    case 2:
        writeServo.start("echo", QStringList() << "2=" + QString::number(pwm) << "> /dev/servoblaster");
        break;
    case 3:
        writeServo.start("echo", QStringList() << "3=" + QString::number(pwm) << "> /dev/servoblaster");
        break;
    case 4:
        writeServo.start("echo", QStringList() << "4=" + QString::number(pwm) << "> /dev/servoblaster");
        break;
    case 5:
        writeServo.start("echo", QStringList() << "5=" + QString::number(pwm) << "> /dev/servoblaster");
        break;
    case 6:
        writeServo.start("echo", QStringList() << "6=" + QString::number(pwm) << "> /dev/servoblaster");
        break;
    case 7:
        writeServo.start("echo", QStringList() << "7=" + QString::number(pwm) << "> /dev/servoblaster");
        break;
    }
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
