#include "mytcpserver.h"
#include <QDebug>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    m_tcpServer = new QTcpServer(this);

    connect(m_tcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::onNewConnection);

    if (!m_tcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

MyTcpServer::~MyTcpServer()
{
    m_tcpServer->close();
    // Все клиенты удалятся автоматически, так как они привязаны к this? Нет, они удаляются сами, но лучше очистить список
    qDeleteAll(m_clients);
    m_clients.clear();
}

void MyTcpServer::onNewConnection()
{
    while (m_tcpServer->hasPendingConnections()) {
        QTcpSocket *socket = m_tcpServer->nextPendingConnection();
        // Создаём обработчика, передавая ему дескриптор сокета
        ClientHandler *handler = new ClientHandler(socket->socketDescriptor(), this);
        // Соединяем сигнал отсоединения со слотом удаления из списка
        connect(handler, &ClientHandler::disconnected, this, &MyTcpServer::onClientDisconnected);
        m_clients.append(handler);
    }
}

void MyTcpServer::onClientDisconnected(ClientHandler *handler)
{
    m_clients.removeAll(handler);
    // Объект handler уже удалит себя сам (deleteLater в onDisconnected)
}