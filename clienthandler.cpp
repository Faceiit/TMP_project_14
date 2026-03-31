#include "clienthandler.h"
#include <QDebug>
#include <QStringList>

ClientHandler::ClientHandler(qintptr socketDescriptor, QObject *parent)
    : QObject(parent), m_authenticated(false)
{
    m_socket = new QTcpSocket(this);
    if (!m_socket->setSocketDescriptor(socketDescriptor)) {
        qDebug() << "Failed to set socket descriptor";
        deleteLater();
        return;
    }

    connect(m_socket, &QTcpSocket::readyRead, this, &ClientHandler::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientHandler::onDisconnected);

    // Приветствие как в старом коде
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
        line.chop(1);                    // удаляем \n
        if (line.endsWith('\r')) line.chop(1); // удаляем \r
        processCommand(QString::fromUtf8(line).trimmed());
    }
}

void ClientHandler::processCommand(const QString &cmd)
{
    if (cmd.isEmpty()) return;

    QStringList parts = cmd.split(' ', Qt::SkipEmptyParts);
    if (parts.isEmpty()) return;

    QString command = parts[0].toUpper();

    // Команды, доступные всегда (включая старые заглушки)
    if (command == "ECHO") {
        handleEcho(parts);
    } else if (command == "STATUS") {
        handleStatus();
    } else if (command == "QUIT") {
        handleQuit();
    } else if (command == "REGISTER") {
        handleRegister(parts);
    } else if (command == "AUTH") {
        handleAuth(parts);
    }
    // Команды, требующие авторизации
    else if (m_authenticated) {
        if (command == "GET_DATA") {
            handleGetData();
        } else if (command == "UPDATE_PROFILE") {
            handleUpdateProfile();
        }else if (command == "LOGOUT") {
            handleLogout();
        } else {
            sendResponse("Unknown command.");
        }
    } else {
        sendResponse("Please authenticate first (AUTH login password)");
    }
}

// ---------- Старые заглушки ----------
void ClientHandler::handleEcho(const QStringList &parts)
{
    // ECHO [текст] – возвращает введённый текст
    if (parts.size() > 1) {
        QString message = parts.mid(1).join(' ');
        sendResponse("ECHO: " + message);
    } else {
        sendResponse("ECHO: (nothing)");
    }
}

void ClientHandler::handleStatus()
{
    // Заглушка статуса
    QString status = "Server is running. "
                     "Authenticated: " + QString(m_authenticated ? "yes" : "no");
    sendResponse(status);
}

void ClientHandler::handleQuit()
{
    sendResponse("Goodbye!");
    m_socket->disconnectFromHost();  // закрываем соединение
}

// ---------- Работа с БД ----------
void ClientHandler::handleRegister(const QStringList &parts)
{
    if (parts.size() != 3) {
        sendResponse("Usage: REGISTER login password");
        return;
    }
    QString login = parts[1];
    QString password = parts[2];

    if (Database::getInstance()->addUser(login, password)) {
        sendResponse("Registration successful.");
    } else {
        sendResponse("Registration failed (user may already exist).");
    }
}

void ClientHandler::handleAuth(const QStringList &parts)
{
    if (parts.size() != 3) {
        sendResponse("Usage: AUTH login password");
        return;
    }
    QString login = parts[1];
    QString password = parts[2];

    if (Database::getInstance()->checkUser(login, password)) {
        m_authenticated = true;
        sendResponse("Authentication successful. Welcome!");
        // можно сохранить login для дальнейшего использования
    } else {
        sendResponse("Authentication failed. Invalid login or password.");
    }
}

// ---------- Новые заглушки (требуют авторизации) ----------
void ClientHandler::handleGetData()
{
    sendResponse("GET_DATA stub: no data yet.");
}

void ClientHandler::handleUpdateProfile()
{
    sendResponse("UPDATE_PROFILE stub: profile update not implemented.");
}
void ClientHandler::handleLogout()
{
    m_authenticated = false;
    sendResponse("You have been logged out.");
}
void ClientHandler::sendResponse(const QString &msg)
{
    m_socket->write(msg.toUtf8() + "\r\n");
}

void ClientHandler::onDisconnected()
{
    emit disconnected(this);
    deleteLater();
}