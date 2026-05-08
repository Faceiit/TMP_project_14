#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMap>

class Client;

class ClientSingletonDestroyer {
private:
    Client* p_instance;
public:
    ~ClientSingletonDestroyer();
    void initialize(Client* p) { p_instance = p; }
};

class Client : public QObject {
    Q_OBJECT

private:
    static Client* p_instance;
    static ClientSingletonDestroyer destroyer;

    explicit Client(QObject* parent = nullptr);
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    QMap<int, QTcpSocket*> m_clients;
    QMap<int, QByteArray> m_buffers;
    int m_nextClientId = 0;

public:
    ~Client();
    static Client* getInstance();

    int createConnection(const QString& host, quint16 port);
    void sendCommand(int clientId, const QString& cmd);
    void disconnectClient(int clientId);

private slots:
    void onReadyRead();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

signals:
    void responseReceived(int clientId, QString response);
};

#endif // CLIENT_H
