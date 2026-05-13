#ifndef CLIENT_H
#define CLIENT_H

/**
 * @file client.h
 * @brief Заголовочный файл класса Client, реализующего сетевое взаимодействие.
 */

#include <QObject>
#include <QTcpSocket>
#include <QMap>

class Client;

/**
 * @class ClientSingletonDestroyer
 * @brief Вспомогательный класс для корректного удаления экземпляра Client.
 * * Паттерн "Очиститель" гарантирует, что память, выделенная под Singleton,
 * будет освобождена при завершении работы приложения.
 */
class ClientSingletonDestroyer {
private:
    Client* p_instance; ///< Указатель на экземпляр синглтона
public:
    /** @brief Деструктор, удаляющий экземпляр Client. */
    ~ClientSingletonDestroyer();

    /**
     * @brief Инициализация деструктора.
     * @param p Указатель на созданный экземпляр Client.
     */
    void initialize(Client* p) { p_instance = p; }
};

/**
 * @class Client
 * @brief Основной класс для работы с сетевыми соединениями на стороне клиента.
 * * Класс реализован как Singleton и управляет пулом TCP-соединений,
 * обеспечивая отправку команд и прием ответов от сервера.
 */
class Client : public QObject {
    Q_OBJECT

private:
    static Client* p_instance; ///< Единственный экземпляр класса
    static ClientSingletonDestroyer destroyer; ///< Автоматический разрушитель экземпляра

    /** @brief Закрытый конструктор для реализации Singleton. */
    explicit Client(QObject* parent = nullptr);
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    QMap<int, QTcpSocket*> m_clients; ///< Карта активных сокетов (ID -> сокет)
    QMap<int, QByteArray> m_buffers;  ///< Буферы накопления данных для каждого клиента
    int m_nextClientId = 0;           ///< Счетчик для генерации уникальных ID соединений

public:
    /** @brief Деструктор класса, закрывающий все активные соединения. */
    ~Client();

    /**
     * @brief Получение ссылки на экземпляр класса (Singleton).
     * @return Указатель на объект Client.
     */
    static Client* getInstance();

    /**
     * @brief Создает новое TCP-соединение с сервером.
     * @param host IP-адрес или доменное имя сервера.
     * @param port Порт сервера.
     * @return Уникальный ID созданного соединения или -1 при ошибке.
     */
    int createConnection(const QString& host, quint16 port);

    /**
     * @brief Отправляет строковую команду серверу.
     * @param clientId ID соединения, через которое нужно отправить данные.
     * @param cmd Текст команды.
     */
    void sendCommand(int clientId, const QString& cmd);

    /**
     * @brief Принудительно разрывает соединение с сервером.
     * @param clientId ID удаляемого соединения.
     */
    void disconnectClient(int clientId);

private slots:
    /** @brief Обработчик появления новых данных в сокете. */
    void onReadyRead();

    /** @brief Обработчик события разрыва соединения со стороны сервера. */
    void onDisconnected();

    /**
     * @brief Обработчик сетевых ошибок.
     * @param socketError Тип возникшей ошибки сокета.
     */
    void onError(QAbstractSocket::SocketError socketError);

signals:
    /**
     * @brief Сигнал, сообщающий о получении полного ответа от сервера.
     * @param clientId ID соединения, от которого пришел ответ.
     * @param response Текст полученного ответа.
     */
    void responseReceived(int clientId, QString response);
};

#endif // CLIENT_H