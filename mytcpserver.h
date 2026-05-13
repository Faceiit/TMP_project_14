#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

/**
 * @file mytcpserver.h
 * @brief Заголовочный файл основного класса TCP-сервера.
 * * Описывает логику прослушивания порта, принятия новых соединений
 * и управления списком активных клиентских сессий.
 */

#include <QObject>
#include <QTcpServer>
#include <QList>
#include "clienthandler.h"

/**
 * @class MyTcpServer
 * @brief Основной класс сервера, координирующий сетевое взаимодействие.
 * * Класс инициализирует QTcpServer и делегирует обработку каждого нового
 * входящего соединения отдельному объекту ClientHandler.
 */
class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор сервера.
     * * Инициализирует сервер и начинает прослушивание заданного порта.
     * @param parent Родительский объект в иерархии Qt.
     */
    explicit MyTcpServer(QObject *parent = nullptr);

    /** @brief Деструктор, останавливающий сервер и удаляющий всех активных клиентов. */
    ~MyTcpServer();

private slots:
    /** * @brief Слот обработки нового входящего соединения.
     * * Создает экземпляр ClientHandler для каждого подключившегося пользователя.
     */
    void onNewConnection();

    /**
     * @brief Слот удаления клиента из списка активных сессий.
     * @param handler Указатель на обработчик, который инициировал отключение.
     */
    void onClientDisconnected(ClientHandler *handler);

private:
    QTcpServer *m_tcpServer;     ///< Внутренний объект QTcpServer для низкоуровневой работы с сетью
    QList<ClientHandler*> m_clients; ///< Список (пул) всех текущих активных обработчиков клиентов
};

#endif // MYTCPSERVER_H