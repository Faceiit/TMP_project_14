#include "mytcpserver.h"
#include <QDebug>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::onNewConnection);
    if (!m_tcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server is not started";
    } else {
        qDebug() << "Server is started on port 33333";
    }
}

MyTcpServer::~MyTcpServer()
{
    m_tcpServer->close();
    qDeleteAll(m_clients);
    m_clients.clear();
}

void MyTcpServer::onNewConnection()
{
    while (m_tcpServer->hasPendingConnections()) {
        QTcpSocket *socket = m_tcpServer->nextPendingConnection();
        ClientHandler *handler = new ClientHandler(socket->socketDescriptor(), this);
        connect(handler, &ClientHandler::disconnected, this, &MyTcpServer::onClientDisconnected);
        m_clients.append(handler);
    }
}

void MyTcpServer::onClientDisconnected(ClientHandler *handler)
{
    m_clients.removeAll(handler);
    // handler уже удалит себя сам
}