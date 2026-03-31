#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include "database.h"

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandler(qintptr socketDescriptor, QObject *parent = nullptr);
    ~ClientHandler();

signals:
    void disconnected(ClientHandler *handler);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *m_socket;
    QByteArray m_buffer;
    bool m_authenticated;  // флаг авторизации

    void processCommand(const QString &cmd);
    void sendResponse(const QString &msg);

    // Команды
    void handleEcho(const QStringList &parts);   // старая заглушка
    void handleStatus();                         // старая заглушка
    void handleQuit();                           // старая заглушка
    void handleRegister(const QStringList &parts);
    void handleAuth(const QStringList &parts);
    void handleGetData();        // новая заглушка (требует авторизации)
    void handleUpdateProfile();  // новая заглушка (требует авторизации)
    void handleLogout();
};

#endif // CLIENTHANDLER_H