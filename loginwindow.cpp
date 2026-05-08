#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QPushButton>
#include "client.h"

LoginWindow::LoginWindow(QWidget *parent): QWidget(parent), ui(new Ui::LoginWindow), m_clientId(-1)
{
    ui->setupUi(this);

    // Подключение к серверу
    m_clientId = Client::getInstance()->createConnection("127.0.0.1", 33333);

    // Кнопки
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);

    // Ответы сервера
connect(Client::getInstance(), &Client::responseReceived, this, &LoginWindow::onServerResponse);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

// Авторизация
void LoginWindow::onLoginClicked()
{
    QString login = ui->loginEdit->text().trimmed();
    QString password = ui->passwordEdit->text().trimmed();

    if (login.isEmpty() or password.isEmpty()) {
        ui->outputText->append("Enter login and password.");
        return;
    }

    QString cmd = "LOGIN " + login + " " + password;
    Client::getInstance()->sendCommand(m_clientId, cmd);
}

// Регистрация
void LoginWindow::onRegisterClicked()
{
    QString login = ui->loginEdit->text().trimmed();
    QString password = ui->passwordEdit->text().trimmed();

    if (login.isEmpty() or password.isEmpty()) {
        ui->outputText->append("Enter login and password.");
        return;
    }

    QString cmd = "REGISTER " + login + " " + password;
    Client::getInstance()->sendCommand(m_clientId, cmd);
}

// Ответ сервера
void LoginWindow::onServerResponse(int clientId, QString response)
{
    if (clientId != m_clientId)
        return;

    ui->outputText->append(response);

    // Успешная авторизация
    if (response.contains("Authentication successful")) {
        MainWindow *mainWindow = new MainWindow(m_clientId);
        mainWindow->show();
        this->close();
    }
}