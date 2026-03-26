#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include "clienthandler.h"

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

private slots:
    void onNewConnection();
    void onClientDisconnected(ClientHandler *handler);

private:
    QTcpServer *m_tcpServer;
    QList<ClientHandler*> m_clients;   // список активных клиентов
};

#endif // MYTCPSERVER_H
