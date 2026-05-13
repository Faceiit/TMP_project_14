#ifndef MD5_H
#define MD5_H

/**
 * @file md5.h
 * @brief Заголовочный файл класса MD5.
 * * Содержит реализацию алгоритма хеширования MD5 (Message Digest Algorithm 5),
 * используемого для проверки целостности данных и хранения паролей.
 */

#include <QString>
#include <QByteArray>
#include <QtGlobal>

/**
 * @class MD5
 * @brief Класс для вычисления криптографических хеш-сумм по алгоритму MD5.
 * * Все методы класса являются статическими, что позволяет генерировать хеш
 * без создания экземпляра объекта.
 */
class MD5 {
public:
    /**
     * @brief Вычисляет MD5-хеш для заданной строки.
     * @param text Исходная строка для хеширования.
     * @return Строка (QString), содержащая шестнадцатеричное представление хеша.
     */
    static QString hash(const QString &text);

private:
    /** @brief Определение беззнакового 32-битного типа для внутренних вычислений. */
    typedef uint32_t uint4;

    // Основные функции трансформации (логические примитивы MD5)

    /** @brief Вспомогательная функция F: (X AND Y) OR (NOT X AND Z). */
    static inline uint4 F(uint4 x, uint4 y, uint4 z) { return (x & y) | (~x & z); }

    /** @brief Вспомогательная функция G: (X AND Z) OR (Y AND NOT Z). */
    static inline uint4 G(uint4 x, uint4 y, uint4 z) { return (x & z) | (y & ~z); }

    /** @brief Вспомогательная функция H: X XOR Y XOR Z. */
    static inline uint4 H(uint4 x, uint4 y, uint4 z) { return x ^ y ^ z; }

    /** @brief Вспомогательная функция I: Y XOR (X OR NOT Z). */
    static inline uint4 I(uint4 x, uint4 y, uint4 z) { return y ^ (x | ~z); }

    /**
     * @brief Циклический сдвиг 32-битного значения влево.
     * @param x Значение для сдвига.
     * @param n Количество бит.
     * @return Результат сдвига.
     */
    static inline uint4 rotateLeft(uint4 x, int n) { return (x << n) | (x >> (32 - n)); }
};

#endif