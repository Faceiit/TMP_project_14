#include "mytcpserver.h"
#include <QCoreApplication>
#include <QString>
#include <QDebug>

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    //server_status=0;
}

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

void MyTcpServer::slotNewConnection(){
    mTcpSocket = mTcpServer->nextPendingConnection();
    mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
    
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}


void MyTcpServer::slotServerRead()
{
    // 1. Читаем все данные из сокета
    QByteArray buffer = mTcpSocket->readAll();
    if (buffer.isEmpty()) return;

    // Оставляем эхо-ответ (отправляем данные обратно клиенту)
    mTcpSocket->write(buffer);

    // 2. Преобразуем байты в строку и убираем лишние символы (пробелы, переносы строк \r\n)
    QString message = QString::fromUtf8(buffer).trimmed();

    // 3. Проверяем, начинается ли сообщение с команды REGISTER
    if (message.startsWith("REGISTER")) {
        // Разделяем строку по пробелам. 
        // Ожидаемый формат: "REGISTER username password"
        QStringList parts = message.split(' ');

        if (parts.size() == 3) {
            QString login = parts[1];
            QString password = parts[2];

            // 4. Обращаемся к БД через Синглтон
            bool success = Database::getInstance()->addUser(login, password);

            if (success) {
                mTcpSocket->write("Registration successful\r\n");
            } else {
                mTcpSocket->write("Registration failed\r\n");
            }
        } else {
            mTcpSocket->write("Usage: REGISTER <login> <password>\r\n");
        }
    }
    else if (message.startsWith("AUTH")) {
        QStringList parts = message.split(' ');
        
        // Ожидаемый формат: "AUTH username password"
        if (parts.size() == 3) {
            QString login = parts[1];
            QString password = parts[2];

            // Обращаемся к БД через Синглтон для проверки существования пользователя
            bool exists = Database::getInstance()->checkUser(login, password);
            if (exists) {
                mTcpSocket->write("Authentication successful. Welcome!\r\n");
            } else {
                mTcpSocket->write("Authentication failed. Invalid login or password.\r\n");
            }
        } else {
            mTcpSocket->write("Usage: AUTH <login> <password>\r\n");
        }
    }
}


void MyTcpServer::slotClientDisconnected(){
    if (mTcpSocket) {
        mTcpSocket->close();
    }
}
