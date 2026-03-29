#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Database; // Опережающее объявление

// Класс для автоматического удаления синглтона
class SingletonDestroyer {
private:
    Database * p_instance;
public:
    ~SingletonDestroyer(); 
    void initialize(Database * p) { p_instance = p; }
};

class Database : public QObject {
    Q_OBJECT
private:
    static Database * p_instance;
    static SingletonDestroyer destroyer;
    QSqlDatabase db; 

protected:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    Database(const Database&) = delete;            // Запрещаем копирование
    Database& operator=(const Database&) = delete; // Запрещаем присваивание
    friend class SingletonDestroyer;

public:
    static Database* getInstance();

    // Методы из вашего исходного кода
    bool addUser(const QString &login, const QString &password); 
    bool checkUser(const QString &login, const QString &password); };

#endif // DATABASE_H