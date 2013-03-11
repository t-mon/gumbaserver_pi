#include "core.h"

Core::Core(QObject *parent) :
    QObject(parent)
{
    m_server = new TcpServer(this);
    m_robot = new SerialConnection(this);

    connect(m_server,SIGNAL(connectGumba()),m_robot,SLOT(connectGumba()));
    connect(m_server,SIGNAL(toggleRTS()),m_robot,SLOT(toggleRTS()));
    connect(m_server,SIGNAL(startRoboApp()),m_robot,SLOT(startGumbaApplication()));

    connect(m_robot,SIGNAL(sendToClient(QString,QString)),m_server,SLOT(sendData(QString,QString)));

}
