#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

/**
 * @file loginwindow.h
 * @brief Заголовочный файл графического окна авторизации.
 * * Описывает интерфейс начального экрана приложения, через который
 * осуществляется вход и регистрация пользователей.
 */

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

/**
 * @class LoginWindow
 * @brief Класс окна авторизации и регистрации.
 * * Обеспечивает визуальное представление полей ввода учетных данных
 * и обработку сигналов от сетевого модуля Client.
 */
class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор окна авторизации.
     * @param parent Указатель на родительский виджет.
     */
    explicit LoginWindow(QWidget *parent = nullptr);

    /** @brief Деструктор, обеспечивающий корректное закрытие окна и очистку UI. */
    ~LoginWindow();

private slots:
    /** @brief Обработчик нажатия кнопки "Вход". Формирует и отправляет сетевую команду LOGIN. */
    void onLoginClicked();

    /** @brief Обработчик нажатия кнопки "Регистрация". Отправляет команду REGISTER. */
    void onRegisterClicked();

    /**
     * @brief Слот для обработки ответов сервера, относящихся к авторизации.
     * @param clientId Идентификатор соединения.
     * @param response Текст ответа сервера (например, "auth_ok" или "auth_err").
     */
    void onServerResponse(int clientId, QString response);

private:
    Ui::LoginWindow *ui; ///< Указатель на графический интерфейс, сгенерированный Qt Designer
    int m_clientId;      ///< Хранимый ID активного соединения для данного окна
};

#endif // LOGINWINDOW_H