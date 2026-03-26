#include "clienthandler.h"
#include <QDebug>
#include <QStringList>

ClientHandler::ClientHandler(qintptr socketDescriptor, QObject* parent)
    : QObject(parent)
{
    m_socket = new QTcpSocket(this);
    if (!m_socket->setSocketDescriptor(socketDescriptor)) {
        qDebug() << "Failed to set socket descriptor";
        deleteLater();
        return;
    }

    connect(m_socket, &QTcpSocket::readyRead, this, &ClientHandler::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientHandler::onDisconnected);

    // Приветствие
    m_socket->write("Hello, World!!! I am echo server!\r\n");
}

ClientHandler::~ClientHandler()
{
    m_socket->close();
}

void ClientHandler::onReadyRead()
{
    m_buffer.append(m_socket->readAll());

    int newlinePos;
    while ((newlinePos = m_buffer.indexOf('\n')) != -1) {
        QByteArray line = m_buffer.left(newlinePos + 1);
        m_buffer.remove(0, newlinePos + 1);
        line.chop(1);
        if (line.endsWith('\r')) line.chop(1);
        processCommand(line);
    }
}

void ClientHandler::onDisconnected()
{
    emit disconnected(this);   // сообщаем серверу, что клиент ушёл
    deleteLater();             // безопасное самоуничтожение
}

void ClientHandler::processCommand(const QByteArray& data)
{
    QString cmdLine = QString::fromUtf8(data).trimmed();
    if (cmdLine.isEmpty()) return;

    QStringList parts = cmdLine.split(' ', Qt::SkipEmptyParts);
    if (parts.isEmpty()) return;

    QString command = parts[0].toUpper();

    if (command == "ECHO") {
        QString message = parts.mid(1).join(' ');
        handleEcho(message);
    }
    else if (command == "STATUS") {
        handleStatus();
    }
    else if (command == "QUIT") {
        handleQuit();
    }
    else {
        m_socket->write("Unknown command\r\n");
    }
}

void ClientHandler::handleEcho(const QString& text)
{
    m_socket->write(("ECHO: " + text + "\r\n").toUtf8());
}

void ClientHandler::handleStatus()
{
    m_socket->write("Server is running.\r\n");
}

void ClientHandler::handleQuit()
{
    m_socket->write("Goodbye!\r\n");
    m_socket->disconnectFromHost();  // инициирует закрытие
}