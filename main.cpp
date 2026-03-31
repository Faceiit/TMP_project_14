#include <QCoreApplication>
#include "database.h"
#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Database::getInstance();  // инициализация БД
    MyTcpServer server;
    return a.exec();
}