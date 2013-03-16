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
    QProcess *loadServod;
    QString servod;

signals:
    void sendToClient(QString,QString);
    
public slots:
    void initServoControl();
    
};

#endif // SERVOCONTROL_H
