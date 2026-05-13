#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file mainwindow.h
 * @brief Заголовочный файл основного рабочего окна приложения.
 * * Содержит интерфейс для вызова всех математических и криптографических функций
 * после успешной авторизации.
 */

#include <QWidget>

namespace Ui { class MainWindow; }

/**
 * @class MainWindow
 * @brief Класс основного окна приложения.
 * * Обеспечивает доступ к функционалу DES, MD5, методу секущих и анализу графов.
 * Управляет отправкой запросов через установленное сетевое соединение.
 */
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор основного окна.
     * @param clientId Идентификатор сессии, полученный при авторизации.
     * @param parent Указатель на родительский виджет.
     */
    explicit MainWindow(int clientId, QWidget *parent = nullptr);

    /** @brief Деструктор, очищающий ресурсы пользовательского интерфейса. */
    ~MainWindow();

    /**
     * @brief Вспомогательный статический метод для сборки строки команды DES.
     * * Формирует протокольную строку вида: DES <mode> <key> <data>
     * @param text Исходный текст или шифротекст.
     * @param key Ключ шифрования.
     * @param decrypt Режим: true для расшифрования, false для шифрования.
     * @return Сформированная строка команды для отправки на сервер.
     */
    static QString buildDesCommand(const QString &text, const QString &key, bool decrypt);

private slots:
    /** @brief Запрос меню справки у сервера. */
    void onHelpClicked();

    /** @brief Завершение текущего сеанса пользователя и возврат к окну логина. */
    void onLogoutClicked();

    /** @brief Полный выход из приложения. */
    void onQuitClicked();

    /** @brief Обработка нажатия кнопки шифрования/дешифрования DES. */
    void onDesClicked();

    /** @brief Обработка нажатия кнопки вычисления хеша MD5. */
    void onMd5Clicked();

    /** @brief Обработка нажатия кнопки решения уравнения методом секущих. */
    void onSecantClicked();

    /** @brief Обработка нажатия кнопки поиска циклов в графе. */
    void onGraphCycleClicked();

    /**
     * @brief Прием и отображение результатов вычислений от сервера.
     * @param clientId ID соединения.
     * @param response Текст ответа от сервера с результатом операции.
     */
    void onServerResponse(int clientId, QString response);

private:
    Ui::MainWindow *ui; ///< Объект визуального интерфейса.
    int m_clientId;      ///< Идентификатор текущего клиентского соединения.
};

#endif // MAINWINDOW_H