#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandler(qintptr socketDescriptor, QObject* parent = nullptr);
    ~ClientHandler();

signals:
    void disconnected(ClientHandler* handler); // сигнал для удаления из списка

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket* m_socket;
    QByteArray m_buffer;

    void processCommand(const QByteArray& data);
    void handleEcho(const QString& text);
    void handleStatus();
    void handleQuit();
};

#endif // CLIENTHANDLER_H