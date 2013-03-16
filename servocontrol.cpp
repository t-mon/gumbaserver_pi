#include "servocontrol.h"
#include <QDebug>

ServoControl::ServoControl(QObject *parent) :
    QObject(parent)
{
    loadServod = new QProcess(this);
    loadServoblasterModul = new QProcess(this);

    connect(loadServod,SIGNAL(readyRead()),this,SLOT(servodOutputAvalable()));
    connect(loadServod,SIGNAL(finished(int)),this,SLOT(loadServodFinished(int)));

}

void ServoControl::initServoControl(){
    QString servodString = "./root/development/ServoBlaster/servod";
    QString servoblasterModulString = "/root/development/ServoBlaster/servoblaster.ko";

    emit sendToClient("Terminal","loading servod daemon...");
    qDebug() << "loading servod daemon...";
    loadServod->start(servodString, QStringList() << "");
    qDebug() << "exitstatus load servod: " << loadServod->exitStatus();

    loadServoblasterModul->start("insmod", QStringList() << servoblasterModulString);
    qDebug() << "exitstatus load servoblaster modul: " << loadServoblasterModul->exitStatus();

}


void ServoControl::servodOutputAvalable()
{
    qDebug() << "got servod output data";
    qDebug() << loadServod->readAllStandardOutput();
}

void ServoControl::loadServodFinished(const int &exitStatus)
{
    qDebug() << "load servod exitstatus: " << QString::number(exitStatus);
//    //if(loadServod->exitStatus() == QProcess::NormalExit){
//    if(exitStatus == 0){
//        emit sendToClient("Terminal","-->servod daemon loaded.");
//        qDebug() << "-->servod daemon loaded." ;
//    }else{
//        emit sendToClient("Terminal","-->ERROR: servod daemon not loaded.");
//        qDebug() << "-->ERROR: servod daemon not loaded.";
//    }
}
