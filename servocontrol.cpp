#include "servocontrol.h"
#include <QDebug>

ServoControl::ServoControl(QObject *parent) :
    QObject(parent)
{
    initServoProcess = new QProcess(this);
    processString.clear();

    connect(initServoProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(initServoProcessReadStandardOutput()));
    connect(initServoProcess,SIGNAL(readyReadStandardError()),this,SLOT(initServoProcessReadStandardError()));
    connect(initServoProcess,SIGNAL(finished(int)),this,SLOT(initServoProcessFinished(int)));

}

void ServoControl::initServo(){
    initServoProcess->start("/root/scripts/initServoblaster.sh");
    initServoProcess->waitForFinished();
}


void ServoControl::initServoProcessFinished(const int &exitStatus)
{
    qDebug() << processString;

    if(exitStatus == 0){
        qDebug() << "Servoblaster initialized successfully!";
    }else{
        qDebug() << "ERROR: Servoblaster not inizialized.";
    }
    processString.clear();
}

void ServoControl::initServoProcessReadStandardOutput()
{
    processString.append(initServoProcess->readAllStandardOutput());
}

void ServoControl::initServoProcessReadStandardError()
{
    processString.append(initServoProcess->readAllStandardError());
}
