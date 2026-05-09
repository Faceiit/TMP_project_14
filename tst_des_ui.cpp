#include <QtTest>
#include <QFile>
#include "DES.h"
#include "mainwindow.h"

class DesUiTests : public QObject
{
    Q_OBJECT

private slots:
    void des_encrypt_decrypt_roundtrip();
    void des_build_command_encrypt_false();
    void des_build_command_decrypt_true();
    void ui_contains_des_checkbox();
};

void DesUiTests::des_encrypt_decrypt_roundtrip()
{
    DES des;
    const QByteArray text("Hello DES");
    QByteArray key("mysecret");
    if (key.size() < 8) {
        key.append(8 - key.size(), char(0));
    } else if (key.size() > 8) {
        key = key.left(8);
    }

    const QByteArray encrypted = des.process(text, key, false);
    QByteArray decrypted = des.process(encrypted, key, true);

    while (!decrypted.isEmpty() && decrypted.endsWith('\0')) {
        decrypted.chop(1);
    }

    QCOMPARE(decrypted, text);
}

void DesUiTests::des_build_command_encrypt_false()
{
    const QString cmd = MainWindow::buildDesCommand("abc", "12345678", false);
    QCOMPARE(cmd, QString("DES abc 12345678 false"));
}

void DesUiTests::des_build_command_decrypt_true()
{
    const QString cmd = MainWindow::buildDesCommand("ABCD", "key12345", true);
    QCOMPARE(cmd, QString("DES ABCD key12345 true"));
}

void DesUiTests::ui_contains_des_checkbox()
{
    QFile file("mainwindow.ui");
    QVERIFY2(file.open(QIODevice::ReadOnly | QIODevice::Text), "Cannot open mainwindow.ui");
    const QString xml = QString::fromUtf8(file.readAll());

    QVERIFY2(xml.contains("name=\"desDecryptCheckBox\""),
             "desDecryptCheckBox widget is missing in mainwindow.ui");
}

QTEST_APPLESS_MAIN(DesUiTests)
#include "tst_des_ui.moc"
