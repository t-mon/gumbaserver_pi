#include "servocontrol.h"
#include <QDebug>

ServoControl::ServoControl(QObject *parent) :
    QObject(parent)
{
    loadServod = new QProcess(this);
    servod = "./root/development/ServoBlaster/servod";
}

void ServoControl::initServoControl(){
    emit sendToClient("Terminal","loading servod daemon...");
    qDebug() << "loading servod daemon...";
    loadServod->start(servod);

    qDebug() << loadServod->readAllStandardOutput();

    if(loadServod->exitStatus() == QProcess::NormalExit){
        emit sendToClient("Terminal","-->servod daemon loaded.");
        qDebug() << "-->servod daemon loaded." ;
    }else{
        emit sendToClient("Terminal","-->ERROR: servod daemon not loaded.");
        qDebug() << "-->ERROR: servod daemon not loaded.";
    }

}
