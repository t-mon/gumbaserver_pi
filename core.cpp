#include "core.h"

Core::Core(QObject *parent) :
    QObject(parent)
{
    m_server = new TcpServer(this);
    m_robot = new SerialConnection(this);

    connect(m_server,SIGNAL(connectToGumba()),m_robot,SLOT(connectToRobot()));


}
