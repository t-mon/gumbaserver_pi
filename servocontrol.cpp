#include "servocontrol.h"
#include <QDebug>

ServoControl::ServoControl(QObject *parent) :
    QObject(parent)
{
    loadServod = new QProcess(this);
    servod = "./root/development/ServoBlaster/servod";

    connect(loadServod,SIGNAL(readyRead()),this,SLOT(servodOutputAvalable()));
    connect(loadServod,SIGNAL(finished(int)),this,SLOT(loadServodFinished(int)));

}

void ServoControl::initServoControl(){
    emit sendToClient("Terminal","loading servod daemon...");
    qDebug() << "loading servod daemon...";
    loadServod->start(servod);

    //    qDebug() << loadServod->readAllStandardOutput();

}


void ServoControl::servodOutputAvalable()
{
    qDebug() << loadServod->readAllStandardOutput();
}

void ServoControl::loadServodFinished(const int &exitStatus)
{
    qDebug() << "load servod exitstatus: " << QString::number(exitStatus);
    //if(loadServod->exitStatus() == QProcess::NormalExit){
    if(exitStatus == 0){
        emit sendToClient("Terminal","-->servod daemon loaded.");
        qDebug() << "-->servod daemon loaded." ;
    }else{
        emit sendToClient("Terminal","-->ERROR: servod daemon not loaded.");
        qDebug() << "-->ERROR: servod daemon not loaded.";
    }
}
