#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <QObject>
#include <QLocalSocket>
#include <QProcess>

class ServoControl : public QObject
{
    Q_OBJECT
public:
    explicit ServoControl(QObject *parent = 0);
    
private:
    QProcess *initServoProcess;
    QString processString;
    QLocalSocket *servoSocket;

signals:
    void sendToClient(QString,QString);

private slots:
    void initServoProcessReadStandardOutput();
    void initServoProcessReadStandardError();
    void initServoProcessFinished(const int &exitStatus);
    void servoSocketConnected();

public slots:
    void initServo();
    void setServo(const int &servoNumber, const QString &pwm);
    
};

#endif // SERVOCONTROL_H
