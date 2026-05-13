/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QLabel *authLabel;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QTextEdit *outputText;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(800, 500);
        LoginWindow->setBaseSize(QSize(0, 0));
        loginEdit = new QLineEdit(LoginWindow);
        loginEdit->setObjectName("loginEdit");
        loginEdit->setEnabled(true);
        loginEdit->setGeometry(QRect(300, 220, 200, 40));
        loginEdit->setTabletTracking(false);
        loginEdit->setFrame(true);
        loginEdit->setEchoMode(QLineEdit::EchoMode::Normal);
        loginEdit->setCursorPosition(0);
        loginEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        loginEdit->setReadOnly(false);
        loginEdit->setCursorMoveStyle(Qt::CursorMoveStyle::LogicalMoveStyle);
        passwordEdit = new QLineEdit(LoginWindow);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEnabled(true);
        passwordEdit->setGeometry(QRect(300, 280, 200, 40));
        passwordEdit->setTabletTracking(false);
        passwordEdit->setFrame(true);
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);
        passwordEdit->setCursorPosition(0);
        passwordEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        passwordEdit->setReadOnly(false);
        passwordEdit->setCursorMoveStyle(Qt::CursorMoveStyle::LogicalMoveStyle);
        authLabel = new QLabel(LoginWindow);
        authLabel->setObjectName("authLabel");
        authLabel->setGeometry(QRect(350, 50, 100, 50));
        authLabel->setTextFormat(Qt::TextFormat::AutoText);
        authLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        loginButton = new QPushButton(LoginWindow);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(250, 340, 140, 40));
        registerButton = new QPushButton(LoginWindow);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(410, 340, 140, 40));
        outputText = new QTextEdit(LoginWindow);
        outputText->setObjectName("outputText");
        outputText->setGeometry(QRect(300, 400, 200, 60));
        outputText->setReadOnly(true);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Form", nullptr));
        loginEdit->setText(QString());
        loginEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter login", nullptr));
        passwordEdit->setText(QString());
        passwordEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter password", nullptr));
        authLabel->setText(QCoreApplication::translate("LoginWindow", "Authentication", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginWindow", "Register", nullptr));
        outputText->setDocumentTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
