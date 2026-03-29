// main.cpp
#include "database.h"
#include <QCoreApplication>
#include "mytcpserver.h"


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    Database::getInstance();
    MyTcpServer myserv;
    return a.exec();
}  

