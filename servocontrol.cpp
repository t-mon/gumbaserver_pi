#include "servocontrol.h"
#include <QDebug>

ServoControl::ServoControl(QObject *parent) :
    QObject(parent)
{
    initServoProcess = new QProcess(this);
    processString.clear();

    connect(initServoProcess,SIGNAL(readyRead()),this,SLOT(initServoProcessReadyRead()));
    connect(initServoProcess,SIGNAL(finished(int)),this,SLOT(initServoProcessFinished(int)));

}

void ServoControl::initServo(){
    initServoProcess->start("/root/scripts/initServoblaster.sh");
}


void ServoControl::initServoProcessReadyRead()
{
    processString.append(initServoProcess->readAll());
}

void ServoControl::initServoProcessFinished(const int &exitStatus)
{
    qDebug() << processString;
    qDebug() << "init servoblaster exit status: " << QString::number(exitStatus);
    processString.clear();
}
