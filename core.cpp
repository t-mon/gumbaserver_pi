#include "core.h"

Core::Core(QObject *parent) :
    QObject(parent)
{
    m_server = new TcpServer(this);


}
