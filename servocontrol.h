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
    void initServoProcessReadStandardOutput();
    void initServoProcessReadStandardError();


    void initServoProcessFinished(const int &exitStatus);

public slots:
    void initServo();
    void setServo(int servoNumber, int pwm);
    
};

#endif // SERVOCONTROL_H
