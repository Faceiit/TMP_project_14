#ifndef MD5_H
#define MD5_H

#include <QString>
#include <QByteArray>
#include <QtGlobal>

class MD5 {
public:
    static QString hash(const QString &text);

private:
    // Вспомогательные типы и константы
    typedef uint32_t uint4;

    // Основные функции трансформации
    static inline uint4 F(uint4 x, uint4 y, uint4 z) { return (x & y) | (~x & z); }
    static inline uint4 G(uint4 x, uint4 y, uint4 z) { return (x & z) | (y & ~z); }
    static inline uint4 H(uint4 x, uint4 y, uint4 z) { return x ^ y ^ z; }
    static inline uint4 I(uint4 x, uint4 y, uint4 z) { return y ^ (x | ~z); }
    static inline uint4 rotateLeft(uint4 x, int n) { return (x << n) | (x >> (32 - n)); }
};

#endif