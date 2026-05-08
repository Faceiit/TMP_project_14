#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QStringList>
#include <QByteArray>

class ClientHandler : public QObject
{
Q_OBJECT
    public:
             explicit ClientHandler(QTcpSocket* socket, QObject *parent = nullptr);
    ~ClientHandler();

signals:
    void disconnected(ClientHandler* handler);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    void processCommand(const QString &cmd);
    void sendResponse(const QString &msg);

    // Базовые команды
    void helpMenu();
    void handleQuit();

    // Авторизация
    void handleRegister(const QStringList &parts);
    void handleLogin(const QStringList &parts);
    void handleLogout();

    // Рабочие методы проекта
    void handleDes(const QStringList &parts);
    void handleMd5(const QStringList &parts);
    void handleSecant(const QStringList &parts);
    void handleGraphCycle(const QStringList &parts);

    QTcpSocket* m_socket;
    QByteArray m_buffer;
    bool m_authenticated;
    int m_clientId;
    static int s_nextId;
};

#endif // CLIENTHANDLER_H
