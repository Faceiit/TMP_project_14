#ifndef DES_H
#define DES_H

/**
 * @file des.h
 * @brief Заголовочный файл класса DES.
 * * Содержит реализацию алгоритма симметричного блочного шифрования DES
 * (Data Encryption Standard).
 */

#include <QString>
#include <QByteArray>
#include <QVector>
#include <bitset>
#include <QtGlobal>

/**
 * @class DES
 * @brief Класс, реализующий алгоритм шифрования DES.
 * * Поддерживает работу с 64-битными блоками данных и 56-битными ключами
 * (представленными в виде 64-битных последовательностей).
 */
class DES {
public:
    /** @brief Конструктор по умолчанию. */
    DES();

    /**
     * @brief Универсальный метод для шифрования или расшифрования данных.
     * @param data Входные данные в виде QByteArray (кратные 8 байтам).
     * @param key Ключ шифрования (8 байт).
     * @param decrypt Режим работы: false — шифрование, true — расшифрование.
     * @return Результирующий массив байтов QByteArray.
     */
    QByteArray process(const QByteArray &data, const QByteArray &key, bool decrypt);

private:
    std::vector<std::bitset<48>> subkeys; ///< Набор из 16 раундовых ключей

    /**
     * @brief Генерация 16-ти 48-битных подключей из основного ключа.
     * @param key Исходный 64-битный ключ.
     */
    void generateSubkeys(std::bitset<64> key);

    /**
     * @brief Циклический сдвиг влево для перестановки битов в половинах ключа.
     * @param bs 28-битная последовательность.
     * @param n Количество позиций для сдвига.
     * @return Сдвинутая битовая последовательность.
     */
    std::bitset<28> leftShift(std::bitset<28> bs, int n);

    /**
     * @brief Функция Фейстеля (f).
     * * Выполняет расширение, исключающее ИЛИ с ключом раунда,
     * S-преобразование и перестановку P.
     * @param R Правая половина блока (32 бита).
     * @param k Раундовый ключ (48 бит).
     * @return Результат функции (32 бита).
     */
    std::bitset<32> f(std::bitset<32> R, std::bitset<48> k);

    /**
     * @brief Конвертация массива байтов Qt в битовую последовательность std::bitset.
     * @param data Входной массив QByteArray.
     * @return 64-битная последовательность.
     */
    std::bitset<64> bytesToBitset(const QByteArray &data);

    /**
     * @brief Конвертация битовой последовательности обратно в QByteArray.
     * @param bt 64-битная последовательность.
     * @return Массив байтов QByteArray.
     */
    QByteArray bitsetToBytes(std::bitset<64> bt);
};

#endif // DES_H