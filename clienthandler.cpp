#include "clienthandler.h"
#include "database.h"
#include <QDebug>
#include "md5.h"
#include "DES.h"
#include <QRegularExpression>

int ClientHandler::s_nextId = 0;

ClientHandler::ClientHandler(QTcpSocket* socket, QObject *parent)
    : QObject(parent), m_authenticated(false), m_socket(socket), m_clientId(s_nextId++)
{
    m_socket->setParent(this);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientHandler::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientHandler::onDisconnected);
    qDebug().noquote() << QString("[Client %1] Connected").arg(m_clientId);
    m_socket->write("Connected to server!\r\n");
}

ClientHandler::~ClientHandler() { m_socket->close(); }

void ClientHandler::onReadyRead()
{
    m_buffer.append(m_socket->readAll());
    int newlinePos;
    while ((newlinePos = m_buffer.indexOf('\n')) != -1) {
        QByteArray line = m_buffer.left(newlinePos + 1);
        m_buffer.remove(0, newlinePos + 1);
        line.chop(1);
        if (line.endsWith('\r')) line.chop(1);
        processCommand(QString::fromUtf8(line).trimmed());
    }
}

void ClientHandler::processCommand(const QString &cmd)
{
    if (cmd.isEmpty()) return;

    qDebug().noquote() << QString("[Client %1] Sent: %2").arg(m_clientId).arg(cmd);

    QStringList parts = cmd.split(' ', Qt::SkipEmptyParts);
    if (parts.isEmpty()) return;

    QString command = parts[0].toUpper();

    // Команды без авторизации
    if (command == "HELP") {
        helpMenu();
    } else if (command == "QUIT") {
        handleQuit();
    } else if (command == "REGISTER") {
        handleRegister(parts);
    } else if (command == "LOGIN") {
        handleLogin(parts);
    }
    // Команды, требующие авторизации
    else if (m_authenticated) {
        if (command == "LOGOUT") {
            handleLogout();
        } else if (command == "DES") {
            handleDes(parts);
        } else if (command == "MD5") {
            handleMd5(parts);
        } else if (command == "SECANT") {
            handleSecant(parts);
        } else if (command == "GRAPH_CYCLE") {
            handleGraphCycle(parts);
        } else {
            sendResponse("Unknown command.");
        }
    } else {
        sendResponse("Unknown command.");
    }
}

void ClientHandler::helpMenu()
{
    sendResponse("Available commands:\r\n"
                 "HELP - show this help message\r\n"
                 "REGISTER <login> <pass> - register a new user\r\n"
                 "LOGIN <login> <pass> - authenticate user\r\n"
                 "QUIT - disconnect\r\n"
                 "\r\n"
                 "After authentication:\r\n"
                 "DES <text> <key> <true/false> - DES process, true=decrypt, false=encrypt\r\n"
                 "DES DEC <hex> <key> - decrypt hex via DES\r\n"
                 "MD5 <text> - get MD5 hash\r\n"
                 "SECANT <args> - solve equation\r\n"
                 "GRAPH_CYCLE <args> - verify graph cycle\r\n"
                 "LOGOUT - log out\r\n");
}

void ClientHandler::handleQuit()
{
    sendResponse("Goodbye!");
    m_socket->disconnectFromHost();
}

void ClientHandler::handleRegister(const QStringList &parts)
{
    if (parts.size() != 3) {
        sendResponse("Usage: REGISTER login password");
        return;
    }
    if (Database::getInstance()->addUser(parts[1], parts[2])) {
        sendResponse("Registration successful.");
    } else {
        sendResponse("Registration failed (user may already exist).");
    }
}

void ClientHandler::handleLogin(const QStringList &parts)
{
    if (parts.size() != 3) {
        sendResponse("Usage: LOGIN login password");
        return;
    }
    if (Database::getInstance()->checkUser(parts[1], parts[2])) {
        m_authenticated = true;
        sendResponse("Authentication successful. Welcome!");
    } else {
        sendResponse("Authentication failed. Invalid login or password.");
    }
}

void ClientHandler::handleLogout()
{
    m_authenticated = false;
    sendResponse("You have been logged out.");
}

void ClientHandler::handleDes(const QStringList &parts)
{
    if (parts.size() < 3) {
        sendResponse("Usage: DES <text> <key> <true/false> OR DES DEC <hex> <key>");
        return;
    }

    auto parseBoolToken = [](const QString &token, bool &value) -> bool {
        if (token.compare("true", Qt::CaseInsensitive) == 0 || token == "1") {
            value = true;
            return true;
        }
        if (token.compare("false", Qt::CaseInsensitive) == 0 || token == "0") {
            value = false;
            return true;
        }
        return false;
    };

    bool decrypt = false;
    int dataStart = 1;
    bool boolMode = false;

    // Новый формат: DES <text> <key> <true/false>
    if (parts.size() >= 4 && parseBoolToken(parts.last(), decrypt)) {
        boolMode = true;
    } else if (parts[1].compare("DEC", Qt::CaseInsensitive) == 0 ||
        parts[1].compare("DECRYPT", Qt::CaseInsensitive) == 0) {
        decrypt = true;
        dataStart = 2;
    } else if (parts[1].compare("ENC", Qt::CaseInsensitive) == 0 ||
               parts[1].compare("ENCRYPT", Qt::CaseInsensitive) == 0) {
        dataStart = 2;
    }

    if ((!boolMode && parts.size() <= dataStart + 1) || (boolMode && parts.size() < 4)) {
        sendResponse("Usage: DES <text> <key> <true/false> OR DES DEC <hex> <key>");
        return;
    }

    QString keyText;
    QString dataText;

    if (boolMode) {
        keyText = parts[parts.size() - 2];
        dataText = parts.mid(1, parts.size() - 3).join(" ");
    } else {
        keyText = parts.last();
        dataText = parts.mid(dataStart, parts.size() - dataStart - 1).join(" ");
    }

    if (dataText.isEmpty() || keyText.isEmpty()) {
        sendResponse("DES error: empty data or key.");
        return;
    }

    QByteArray keyBytes = keyText.toUtf8();
    if (keyBytes.size() < 8) {
        keyBytes.append(8 - keyBytes.size(), char(0));
    } else if (keyBytes.size() > 8) {
        keyBytes = keyBytes.left(8);
    }

    DES des;

    if (decrypt) {
        static const QRegularExpression hexRe("^[0-9A-Fa-f]+$");
        if (!hexRe.match(dataText).hasMatch() || (dataText.size() % 2 != 0)) {
            sendResponse("DES error: for DEC mode data must be valid even-length hex.");
            return;
        }

        const QByteArray encryptedBytes = QByteArray::fromHex(dataText.toLatin1());
        QByteArray decrypted = des.process(encryptedBytes, keyBytes, true);

        while (!decrypted.isEmpty() && decrypted.endsWith('\0')) {
            decrypted.chop(1);
        }

        sendResponse("DES decrypted: " + QString::fromUtf8(decrypted));
    } else {
        const QByteArray encrypted = des.process(dataText.toUtf8(), keyBytes, false);
        sendResponse("DES encrypted (hex): " + QString::fromLatin1(encrypted.toHex().toUpper()));
    }
}

void ClientHandler::handleMd5(const QStringList &parts) {
    if (parts.size() < 2) {
        sendResponse("Usage: MD5 <text>");
        return;
    }

    QString text = parts.mid(1).join(" ");
    QString result = MD5::hash(text);

    sendResponse("MD5 Hash: " + result);
}

void ClientHandler::handleSecant(const QStringList &parts)
{
    sendResponse("SECANT result: not implemented yet.");
}

void ClientHandler::handleGraphCycle(const QStringList &parts)
{
    sendResponse("GRAPH_CYCLE result: not implemented yet.");
}

void ClientHandler::sendResponse(const QString &msg)
{
    m_socket->write(msg.toUtf8() + "\r\n");
}

void ClientHandler::onDisconnected()
{
    qDebug().noquote() << QString("[Client %1] Disconnected").arg(m_clientId);
    emit disconnected(this);
    deleteLater();
}
