#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

/**
 * @file clienthandler.h
 * @brief Заголовочный файл класса ClientHandler.
 * * Класс отвечает за индивидуальное обслуживание каждого подключенного клиента,
 * интерпретацию протокола обмена сообщениями и вызов бизнес-логики.
 */

#include <QObject>
#include <QTcpSocket>
#include <QStringList>
#include <QByteArray>

/**
 * @class ClientHandler
 * @brief Класс-обработчик клиентского сеанса.
 * * Создается сервером для каждого нового TCP-соединения. Управляет состоянием
 * авторизации пользователя и маршрутизацией запросов к криптографическим
 * и математическим модулям.
 */
class ClientHandler : public QObject
{
    Q_OBJECT
public:
    /**
         * @brief Конструктор обработчика.
         * @param socket Указатель на сокет открытого соединения.
         * @param parent Родительский объект.
         */
    explicit ClientHandler(QTcpSocket* socket, QObject *parent = nullptr);

    /** @brief Деструктор, гарантирующий закрытие сокета и очистку ресурсов сессии. */
    ~ClientHandler();

signals:
    /**
     * @brief Сигнал, информирующий сервер о завершении сеанса.
     * @param handler Указатель на текущий экземпляр обработчика для его удаления из списка.
     */
    void disconnected(ClientHandler* handler);

private slots:
    /** @brief Чтение входящего потока данных из сокета и накопление в буфере. */
    void onReadyRead();

    /** @brief Обработка события закрытия соединения со стороны клиента. */
    void onDisconnected();

private:
    /**
     * @brief Разбор текстовой команды и вызов соответствующего метода обработки.
     * @param cmd Полная строка команды, полученная от клиента.
     */
    void processCommand(const QString &cmd);

    /**
     * @brief Отправка текстового ответа обратно клиенту.
     * @param msg Строка ответа (результат выполнения или сообщение об ошибке).
     */
    void sendResponse(const QString &msg);

    // Базовые команды
    /** @brief Отправка списка доступных команд клиенту. */
    void helpMenu();

    /** @brief Корректное завершение сессии по инициативе пользователя. */
    void handleQuit();

    // Авторизация
    /**
     * @brief Регистрация нового пользователя в базе данных.
     * @param parts Список аргументов (логин, пароль).
     */
    void handleRegister(const QStringList &parts);

    /**
     * @brief Проверка учетных данных и перевод сессии в статус авторизованной.
     * @param parts Список аргументов (логин, пароль).
     */
    void handleLogin(const QStringList &parts);

    /** @brief Сброс статуса авторизации текущей сессии. */
    void handleLogout();

    // Рабочие методы проекта
    /**
     * @brief Обработка запроса на шифрование/дешифрование алгоритмом DES.
     * @param parts Аргументы команды (режим, ключ, данные).
     */
    void handleDes(const QStringList &parts);

    /**
     * @brief Обработка запроса на вычисление хеша MD5.
     * @param parts Аргументы команды (строка для хеширования).
     */
    void handleMd5(const QStringList &parts);

    /**
     * @brief Решение уравнения методом секущих.
     * @param parts Параметры уравнения и начальные приближения.
     */
    void handleSecant(const QStringList &parts);

    /**
     * @brief Анализ графа на наличие циклов.
     * @param parts Описание структуры графа (узлы и ребра).
     */
    void handleGraphCycle(const QStringList &parts);

    QTcpSocket* m_socket;      ///< Сокет текущего соединения
    QByteArray m_buffer;       ///< Внутренний буфер для сборки полных строк команд
    bool m_authenticated;      ///< Флаг успешного прохождения авторизации
    int m_clientId;            ///< Внутренний идентификатор данного обработчика
    static int s_nextId;       ///< Статический счетчик для генерации уникальных ID
};

#endif // CLIENTHANDLER_H