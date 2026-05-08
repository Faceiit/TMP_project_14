#include <QApplication>
#include "mytcpserver.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Запуск сервера
    MyTcpServer server;

    // Запуск клиента GUI
    LoginWindow w;
    w.show();

    return a.exec();
}
