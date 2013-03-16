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
    QProcess *loadServoblasterModul;
    QString servod;
    QString servoblasterModul;

signals:
    void sendToClient(QString,QString);

private slots:
    void servodOutputAvalable();
    void loadServodFinished(const int &exitStatus);

public slots:
    void initServoControl();
    
};

#endif // SERVOCONTROL_H
