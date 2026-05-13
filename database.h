#ifndef DATABASE_H
#define DATABASE_H

/**
 * @file database.h
 * @brief Заголовочный файл класса Database.
 * * Содержит описание механизмов взаимодействия с SQLite базой данных
 * и реализации паттерна Singleton для управления подключениями.
 */

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Database; // Опережающее объявление

/**
 * @class SingletonDestroyer
 * @brief Класс для автоматического контроля жизненного цикла объекта Database.
 * * Гарантирует корректное закрытие дескрипторов базы данных и освобождение
 * оперативной памяти при завершении работы приложения.
 */
class SingletonDestroyer {
private:
    Database* p_instance; ///< Указатель на единственный экземпляр базы данных
public:
    /** @brief Деструктор, инициирующий удаление объекта Database. */
    ~SingletonDestroyer();

    /**
     * @brief Привязка деструктора к конкретному экземпляру.
     * @param p Указатель на инициализированный объект Database.
     */
    void initialize(Database* p) { p_instance = p; }
};

/**
 * @class Database
 * @brief Класс-интерфейс для работы с базой данных пользователей.
 * * Позволяет выполнять базовые операции CRUD (регистрация, проверка прав доступа).
 * Использование статического экземпляра предотвращает конфликты одновременной
 * записи в один файл БД из разных потоков.
 */
class Database : public QObject {
    Q_OBJECT
private:
    static Database* p_instance; ///< Глобальный указатель на экземпляр класса
    static SingletonDestroyer destroyer; ///< Статический объект-очиститель
    QSqlDatabase db; ///< Объект соединения с SQL базой данных

protected:
    /** @brief Защищенный конструктор: инициализация драйверов и открытие файла БД. */
    explicit Database(QObject* parent = nullptr);

    /** @brief Защищенный деструктор: закрытие активных соединений. */
    ~Database();

    Database(const Database&) = delete;            ///< Запрет копирования (Singleton)
    Database& operator=(const Database&) = delete; ///< Запрет присваивания (Singleton)

    friend class SingletonDestroyer; ///< Разрешение деструктору доступа к private/protected членам

public:
    /**
     * @brief Глобальная точка доступа к объекту базы данных.
     * @return Указатель на экземпляр Database. При первом вызове создает объект.
     */
    static Database* getInstance();

    /**
     * @brief Регистрация нового пользователя.
     * @param login Уникальное имя пользователя.
     * @param password Хешированный (или открытый) пароль пользователя.
     * @return true, если пользователь успешно добавлен; false при ошибке или дубликате логина.
     */
    bool addUser(const QString& login, const QString& password);

    /**
     * @brief Проверка существования пользователя и валидности пароля.
     * @param login Имя пользователя для поиска.
     * @param password Пароль для сверки.
     * @return true, если пара логин/пароль найдена в базе.
     */
    bool checkUser(const QString& login, const QString& password);
};

#endif // DATABASE_H