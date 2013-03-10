#include "core.h"

Core::Core(QObject *parent) :
    QObject(parent)
{
    m_server = new TcpServer(this);
    m_robot = new SerialConnection(this);

    connect(m_server,SIGNAL(connectToGumba()),m_robot,SLOT(connectToRobot()));
    connect(m_server,SIGNAL(toggleRTS()),m_robot,SLOT(toggleRTS()));
    connect(m_server,SIGNAL(startRoboApp()),m_robot,SLOT(startRobotApplication()));

}
