#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui { class MainWindow; }

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(int clientId, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onHelpClicked();
    void onLogoutClicked();
    void onQuitClicked();

    void onDesClicked();
    void onMd5Clicked();
    void onSecantClicked();
    void onGraphCycleClicked();

    void onServerResponse(int clientId, QString response);

private:
    Ui::MainWindow *ui;
    int m_clientId;
};

#endif // MAINWINDOW_H