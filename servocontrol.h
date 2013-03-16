#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <QObject>
#include <QProcess>

class ServoControl : public QObject
{
    Q_OBJECT
public:
    explicit ServoControl(QObject *parent = 0);
    
private:
    QProcess *initServoProcess;
    QString processString;

signals:
    void sendToClient(QString,QString);

private slots:
    void initServoProcessReadyRead();
    void initServoProcessFinished(const int &exitStatus);

public slots:
    void initServo();
    
};

#endif // SERVOCONTROL_H
