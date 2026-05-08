#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "client.h"

MainWindow::MainWindow(int clientId, QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow), m_clientId(clientId)
{
    ui->setupUi(this);

    // Подключение кнопок
    connect(ui->helpButton, &QPushButton::clicked,
            this, &MainWindow::onHelpClicked);

    connect(ui->logoutButton, &QPushButton::clicked,
            this, &MainWindow::onLogoutClicked);

    connect(ui->quitButton, &QPushButton::clicked,
            this, &MainWindow::onQuitClicked);

    connect(ui->desButton, &QPushButton::clicked,
            this, &MainWindow::onDesClicked);

    connect(ui->md5Button, &QPushButton::clicked,
            this, &MainWindow::onMd5Clicked);

    connect(ui->secantButton, &QPushButton::clicked,
            this, &MainWindow::onSecantClicked);

    connect(ui->graphCycleButton, &QPushButton::clicked,
            this, &MainWindow::onGraphCycleClicked);

    // Ответы сервера
    connect(Client::getInstance(), &Client::responseReceived,
            this, &MainWindow::onServerResponse);

    ui->outputText->setReadOnly(true);
    ui->outputText->append("Main menu loaded. Press Help for commands.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onHelpClicked()
{
    Client::getInstance()->sendCommand(m_clientId, "HELP");
}

void MainWindow::onLogoutClicked()
{
    Client::getInstance()->sendCommand(m_clientId, "LOGOUT");
}

void MainWindow::onQuitClicked()
{
    Client::getInstance()->sendCommand(m_clientId, "QUIT");
    close();
}

void MainWindow::onDesClicked()
{
    QString text = ui->desInputEdit->text().trimmed();
    QString key = ui->desKeyEdit->text().trimmed();

    if (text.isEmpty() || key.isEmpty()) {
        ui->outputText->append("Enter DES text and key.");
        return;
    }

    QString cmd = QString("DES %1 %2").arg(text, key);
    Client::getInstance()->sendCommand(m_clientId, cmd);
}

void MainWindow::onMd5Clicked()
{
    QString text = ui->md5InputEdit->text().trimmed();

    if (text.isEmpty()) {
        ui->outputText->append("Enter text for MD5.");
        return;
    }

    QString cmd = QString("MD5 %1").arg(text);
    Client::getInstance()->sendCommand(m_clientId, cmd);
}

void MainWindow::onSecantClicked()
{
    QString function = ui->secantFunctionEdit->text().trimmed();
    QString x0 = ui->secantX0Edit->text().trimmed();
    QString x1 = ui->secantX1Edit->text().trimmed();
    QString eps = ui->secantEpsEdit->text().trimmed();

    if (function.isEmpty() || x0.isEmpty() || x1.isEmpty() || eps.isEmpty()) {
        ui->outputText->append("Fill all SECANT fields.");
        return;
    }

    QString cmd = QString("SECANT %1 %2 %3 %4")
                      .arg(function, x0, x1, eps);

    Client::getInstance()->sendCommand(m_clientId, cmd);
}

void MainWindow::onGraphCycleClicked()
{
    QString graph = ui->graphInputEdit->text().trimmed();

    if (graph.isEmpty()) {
        ui->outputText->append("Enter graph data.");
        return;
    }

    QString cmd = QString("GRAPH_CYCLE %1").arg(graph);
    Client::getInstance()->sendCommand(m_clientId, cmd);
}

void MainWindow::onServerResponse(int clientId, QString response)
{
    if (clientId != m_clientId)
        return;

    ui->outputText->append(response);

    if (response.contains("logged out", Qt::CaseInsensitive)) {
        LoginWindow *loginWindow = new LoginWindow();
        loginWindow->show();
        close();
    }

    if (response.contains("Goodbye", Qt::CaseInsensitive)) {
        close();
    }
}