#include "client.h"
#include <QDebug>

// Единственный экземпляр клиента
Client* Client::p_instance = nullptr;
ClientSingletonDestroyer Client::destroyer;

ClientSingletonDestroyer::~ClientSingletonDestroyer() {
    delete p_instance;
}

Client* Client::getInstance() {

    // Проверяем: создан ли уже Singleton
    if (!p_instance) {

        // Если нет — создаем новый объект Client
        p_instance = new Client();

        // Передаем destroyer указатель на объект, чтобы он автоматически освободил память позже
        destroyer.initialize(p_instance);
    }

    // Возвращаем единственный экземпляр
    return p_instance;
}

Client::Client(QObject* parent) : QObject(parent) {
    m_nextClientId = 0;
}

Client::~Client() {

    // Проходим по всем подключенным клиентам
    for (auto socket : m_clients.values()) {

        if (socket) {
            socket->disconnectFromHost();
            socket->close();
        }
    }
    m_clients.clear();
    m_buffers.clear();
}

int Client::createConnection(const QString& host, quint16 port) {

    // Создаем новый сокет (отдельный клиент)
    QTcpSocket* socket = new QTcpSocket(this);

    // Подключаемся к серверу
    socket->connectToHost(host, port);

    if (!socket->waitForConnected(3000)) {
        qDebug().noquote() << QString("[Client] Connection failed: %1")
        .arg(socket->errorString());

        socket->deleteLater();
        return -1;
    }

    int clientId = m_nextClientId++;
    socket->setProperty("clientId", clientId);

    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred,this, &Client::onError);

    m_clients.insert(clientId, socket);
    m_buffers.insert(clientId, QByteArray());

    return clientId;
}

void Client::sendCommand(int clientId, const QString& cmd) {

    QTcpSocket* socket = m_clients.value(clientId, nullptr);

    if (socket and socket->state() == QAbstractSocket::ConnectedState) {

        socket->write(cmd.toUtf8() + "\r\n");
        socket->flush();

    } else {

        qDebug().noquote() << QString("[Client %1] Not connected or not found.")
                                  .arg(clientId);
    }
}

void Client::onReadyRead() {

    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    if (!socket) return;

    int clientId = socket->property("clientId").toInt();
    QByteArray &buffer = m_buffers[clientId];

    buffer.append(socket->readAll());

    while (buffer.contains('\n')) {

        int pos = buffer.indexOf('\n');

        QByteArray line = buffer.left(pos).trimmed();
        buffer.remove(0, pos + 1);

        if (!line.isEmpty()) {
            emit responseReceived(clientId, QString::fromUtf8(line));
        }
    }
}

void Client::onError(QAbstractSocket::SocketError socketError) {

    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    if (socket) {

        int clientId = socket->property("clientId").toInt();

        qDebug().noquote() << QString("[Client %1] Socket Error: %2")
                                  .arg(clientId)
                                  .arg(socket->errorString());
    }
}

void Client::onDisconnected() {

    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    if (!socket) return;

    int clientId = socket->property("clientId").toInt();
    qDebug().noquote() << QString("[Client %1] Disconnected.")
                              .arg(clientId);

    m_clients.remove(clientId);
    m_buffers.remove(clientId);
    socket->deleteLater();
}