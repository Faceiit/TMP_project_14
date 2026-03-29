#include "database.h"

// Инициализация статических членов
Database* Database::p_instance = nullptr;
SingletonDestroyer Database::destroyer;

// Реализация деструктора разрушителя
SingletonDestroyer::~SingletonDestroyer() {
    delete p_instance;
}

Database::Database(QObject *parent) : QObject(parent) {
    db = QSqlDatabase::addDatabase("QSQLITE"); 
    db.setDatabaseName("server.db"); 

    if (!db.open()) {
        qDebug() << "Ошибка подключения к БД: " << db.lastError().text();
    } else {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS Users ("
                   "login VARCHAR(20) NOT NULL, "
                   "password VARCHAR(20) NOT NULL)");
    }
}

Database::~Database() {
    if (db.isOpen()) {
        db.close(); 
    }
}

Database* Database::getInstance() {
    if (!p_instance) {
        p_instance = new Database();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

bool Database::addUser(const QString &login, const QString &password) {
    QSqlQuery query;
    query.prepare("INSERT INTO Users (login, password) VALUES (:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    return query.exec();
}

bool Database::checkUser(const QString &login, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE login = :login AND password = :password");
    query.bindValue(":login", login); 
    query.bindValue(":password", password); 
    return query.exec() && query.next();
}