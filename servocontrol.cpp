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
