#ifndef DES_H
#define DES_H

#include <QString>
#include <QByteArray>
#include <QVector>
#include <bitset>
#include <QtGlobal>

class DES {
public:
    DES();

    // Универсальный метод для шифрования/расшифрования
    // Принимает данные и ключ в виде QByteArray
    QByteArray process(const QByteArray &data, const QByteArray &key, bool decrypt);

private:
    std::vector<std::bitset<48>> subkeys;

    void generateSubkeys(std::bitset<64> key);
    std::bitset<28> leftShift(std::bitset<28> bs, int n);
    std::bitset<32> f(std::bitset<32> R, std::bitset<48> k);
    
    // Вспомогательные методы преобразования
    std::bitset<64> bytesToBitset(const QByteArray &data);
    QByteArray bitsetToBytes(std::bitset<64> bt);
};

#endif // DES_H