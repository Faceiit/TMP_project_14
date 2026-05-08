#include "mytcpserver.h"
#include <QDebug>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::onNewConnection);

    if (!m_tcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug().noquote() << "[Server] Failed to start.";
    } else {
        qDebug().noquote() << "[Server] Started on port 33333.";
    }
}

MyTcpServer::~MyTcpServer()
{
    qDebug().noquote() << "[Server] Shutting down.";

    m_tcpServer->close();
    qDeleteAll(m_clients);
    m_clients.clear();
}

void MyTcpServer::onNewConnection()
{
    while (m_tcpServer->hasPendingConnections()) {

        QTcpSocket *socket = m_tcpServer->nextPendingConnection();
        ClientHandler *handler = new ClientHandler(socket, this);

        connect(handler, &ClientHandler::disconnected,
                this, &MyTcpServer::onClientDisconnected);

        m_clients.append(handler);

        qDebug().noquote() << QString("[Server] Active clients: %1")
                                  .arg(m_clients.size());
    }
}

void MyTcpServer::onClientDisconnected(ClientHandler *handler)
{
    qDebug().noquote() << "[Server] Client disconnected.";

    m_clients.removeAll(handler);

    qDebug().noquote() << QString("[Server] Active clients: %1")
                              .arg(m_clients.size());

    // handler уже удалит себя сам
}
