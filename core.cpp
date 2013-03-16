#include "core.h"


Core::Core(QObject *parent) :
    QObject(parent)
{
    m_server = new TcpServer(this);
    m_robot = new SerialConnection(this);
    m_servo = new ServoControl(this);

    connect(m_server,SIGNAL(connectGumba()),m_robot,SLOT(connectGumba()));
    connect(m_server,SIGNAL(disconnectGumba()),m_robot,SLOT(disconnectGumba()));
    connect(m_server,SIGNAL(toggleRTS()),m_robot,SLOT(toggleRTS()));
    connect(m_server,SIGNAL(startRoboApp()),m_robot,SLOT(startGumbaApplication()));

    connect(m_server,SIGNAL(movementForward()),m_robot,SLOT(movementForward()));
    connect(m_server,SIGNAL(movementBackward()),m_robot,SLOT(movementBackward()));
    connect(m_server,SIGNAL(movementLeft()),m_robot,SLOT(movementLeft()));
    connect(m_server,SIGNAL(movementRight()),m_robot,SLOT(movementRight()));
    connect(m_server,SIGNAL(movementTurnLeft()),m_robot,SLOT(movementTurnLeft()));
    connect(m_server,SIGNAL(movementTurnRight()),m_robot,SLOT(movementTurnRight()));
    connect(m_server,SIGNAL(movementStop()),m_robot,SLOT(movementStop()));

    connect(m_server,SIGNAL(speedChanged(int)),m_robot,SLOT(speedChanged(int)));

    connect(m_server,SIGNAL(servoInit()),m_servo,SLOT(initServoControl()));

    connect(m_robot,SIGNAL(sendToClient(QString,QString)),m_server,SLOT(sendData(QString,QString)));
    connect(m_servo,SIGNAL(sendToClient(QString,QString)),m_server,SLOT(sendData(QString,QString)));


}
