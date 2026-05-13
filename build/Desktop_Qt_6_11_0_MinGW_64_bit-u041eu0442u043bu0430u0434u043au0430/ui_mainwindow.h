/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QTextEdit *outputText;
    QPushButton *helpButton;
    QPushButton *quitButton;
    QPushButton *logoutButton;
    QLabel *menuLabel;
    QLineEdit *desInputEdit;
    QLineEdit *desKeyEdit;
    QPushButton *desButton;
    QCheckBox *desDecryptCheckBox;
    QLineEdit *md5InputEdit;
    QPushButton *md5Button;
    QLineEdit *secantFunctionEdit;
    QLineEdit *secantX0Edit;
    QLineEdit *secantX1Edit;
    QLineEdit *secantEpsEdit;
    QPushButton *secantButton;
    QLineEdit *graphInputEdit;
    QPushButton *graphCycleButton;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(941, 560);
        outputText = new QTextEdit(MainWindow);
        outputText->setObjectName("outputText");
        outputText->setGeometry(QRect(529, 40, 351, 480));
        outputText->setReadOnly(true);
        helpButton = new QPushButton(MainWindow);
        helpButton->setObjectName("helpButton");
        helpButton->setGeometry(QRect(220, 50, 130, 40));
        quitButton = new QPushButton(MainWindow);
        quitButton->setObjectName("quitButton");
        quitButton->setGeometry(QRect(300, 500, 130, 40));
        logoutButton = new QPushButton(MainWindow);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(130, 500, 130, 40));
        menuLabel = new QLabel(MainWindow);
        menuLabel->setObjectName("menuLabel");
        menuLabel->setGeometry(QRect(240, 10, 100, 40));
        menuLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        desInputEdit = new QLineEdit(MainWindow);
        desInputEdit->setObjectName("desInputEdit");
        desInputEdit->setGeometry(QRect(60, 130, 130, 40));
        desInputEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        desKeyEdit = new QLineEdit(MainWindow);
        desKeyEdit->setObjectName("desKeyEdit");
        desKeyEdit->setGeometry(QRect(220, 130, 130, 40));
        desKeyEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        desButton = new QPushButton(MainWindow);
        desButton->setObjectName("desButton");
        desButton->setGeometry(QRect(380, 130, 130, 41));
        desDecryptCheckBox = new QCheckBox(MainWindow);
        desDecryptCheckBox->setObjectName("desDecryptCheckBox");
        desDecryptCheckBox->setGeometry(QRect(380, 170, 130, 20));
        md5InputEdit = new QLineEdit(MainWindow);
        md5InputEdit->setObjectName("md5InputEdit");
        md5InputEdit->setGeometry(QRect(140, 210, 130, 40));
        md5InputEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        md5Button = new QPushButton(MainWindow);
        md5Button->setObjectName("md5Button");
        md5Button->setGeometry(QRect(300, 210, 130, 40));
        secantFunctionEdit = new QLineEdit(MainWindow);
        secantFunctionEdit->setObjectName("secantFunctionEdit");
        secantFunctionEdit->setGeometry(QRect(60, 290, 130, 40));
        secantFunctionEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        secantX0Edit = new QLineEdit(MainWindow);
        secantX0Edit->setObjectName("secantX0Edit");
        secantX0Edit->setGeometry(QRect(220, 290, 50, 40));
        secantX0Edit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        secantX1Edit = new QLineEdit(MainWindow);
        secantX1Edit->setObjectName("secantX1Edit");
        secantX1Edit->setGeometry(QRect(300, 290, 50, 40));
        secantX1Edit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        secantEpsEdit = new QLineEdit(MainWindow);
        secantEpsEdit->setObjectName("secantEpsEdit");
        secantEpsEdit->setGeometry(QRect(380, 290, 130, 40));
        secantEpsEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        secantButton = new QPushButton(MainWindow);
        secantButton->setObjectName("secantButton");
        secantButton->setGeometry(QRect(220, 350, 130, 40));
        graphInputEdit = new QLineEdit(MainWindow);
        graphInputEdit->setObjectName("graphInputEdit");
        graphInputEdit->setGeometry(QRect(130, 430, 130, 40));
        graphInputEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        graphCycleButton = new QPushButton(MainWindow);
        graphCycleButton->setObjectName("graphCycleButton");
        graphCycleButton->setGeometry(QRect(300, 430, 130, 40));
        line = new QFrame(MainWindow);
        line->setObjectName("line");
        line->setGeometry(QRect(90, 100, 391, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(MainWindow);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(90, 180, 391, 20));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        line_3 = new QFrame(MainWindow);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(90, 260, 391, 20));
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        line_4 = new QFrame(MainWindow);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(90, 400, 391, 20));
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        line_5 = new QFrame(MainWindow);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(90, 480, 391, 20));
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Form", nullptr));
        helpButton->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        quitButton->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        menuLabel->setText(QCoreApplication::translate("MainWindow", "Main Menu", nullptr));
        desInputEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter text for DES", nullptr));
        desKeyEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter DES key", nullptr));
        desButton->setText(QCoreApplication::translate("MainWindow", "Run DES", nullptr));
        desDecryptCheckBox->setText(QCoreApplication::translate("MainWindow", "Decrypt mode", nullptr));
        md5InputEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter text for MD5", nullptr));
        md5Button->setText(QCoreApplication::translate("MainWindow", "Generate MD5", nullptr));
        secantFunctionEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Example: x^2-4", nullptr));
        secantX0Edit->setPlaceholderText(QCoreApplication::translate("MainWindow", "x0", nullptr));
        secantX1Edit->setPlaceholderText(QCoreApplication::translate("MainWindow", "x1", nullptr));
        secantEpsEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Precision", nullptr));
        secantButton->setText(QCoreApplication::translate("MainWindow", "Solve Secant", nullptr));
        graphInputEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Example: 0-1, 1-2", nullptr));
        graphCycleButton->setText(QCoreApplication::translate("MainWindow", "Check Graph Cycle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
