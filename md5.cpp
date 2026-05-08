#include "md5.h"
#include <cmath>

// Вспомогательная функция: сдвигает биты числа влево "по кругу"
unsigned int rotate_left(unsigned int x, int n) {
    return (x << n) | (x >> (32 - n));
}

QString MD5::hash(const QString &text) {
    // Переводим текст в байты
    QByteArray data = text.toUtf8();

    // Запоминаем исходную длину в битах
    unsigned long long bit_len = (unsigned long long)data.size() * 8;

    // 1. Дополнение сообщения (алгоритм работает с блоками по 512 бит)
    // Добавляем один бит '1' (байт 0x80)
    data.append((char)0x80);

    // Добавляем нулевые байты, пока до конца блока не останется ровно 64 бита
    while ((data.size() * 8) % 512 != 448) {
        data.append((char)0);
    }

    // В последние 64 бита записываем длину исходного сообщения
    for (int i = 0; i < 8; i++) {
        data.append((char)((bit_len >> (i * 8)) & 0xFF));
    }

    // 2. Начальные значения буферов
    unsigned int A = 0x67452301;
    unsigned int B = 0xefcdab89;
    unsigned int C = 0x98badcfe;
    unsigned int D = 0x10325476;

    // Таблица T: 64 константы на основе синуса (нужны для уникальности перемешивания)
    unsigned int T[64];
    for (int i = 0; i < 64; i++) {
        T[i] = (unsigned int)(4294967296.0 * fabs(sin(i + 1)));
    }

    // Таблица S: указывает, на сколько бит сдвигать данные на каждом из 64 шагов
    unsigned int S[] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };

    // 3. Основной цикл обработки
    // Обрабатываем сообщение кусками по 64 байта (512 бит)
    for (int offset = 0; offset < data.size(); offset += 64) {

        // Копируем 64 байта в массив из 16 чисел (по 4 байта каждое)
        unsigned int W[16];
        for (int i = 0; i < 16; i++) {
            unsigned char* p = (unsigned char*)data.data() + offset + i * 4;
            W[i] = (unsigned int)p[0] | ((unsigned int)p[1] << 8) |
                   ((unsigned int)p[2] << 16) | ((unsigned int)p[3] << 24);
        }

        // Сохраняем текущие значения регистров перед перемешиванием
        unsigned int a = A;
        unsigned int b = B;
        unsigned int c = C;
        unsigned int d = D;

        // Выполняем 64 итерации перемешивания битов
        for (int i = 0; i < 64; i++) {
            unsigned int f, g;

            if (i < 16) {
                f = (b & c) | (~b & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | (~d & c);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3 * i + 5) % 16;
            } else {
                f = c ^ (b | ~d);
                g = (7 * i) % 16;
            }

            unsigned int temp = d;
            d = c;
            c = b;
            b = b + rotate_left((a + f + T[i] + W[g]), S[i]);
            a = temp;
        }

        A += a;
        B += b;
        C += c;
        D += d;
    }

    // 4. Формируем итоговую строку в HEX
    QString result = "";
    unsigned int res[4] = {A, B, C, D};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            unsigned char byte = (res[i] >> (j * 8)) & 0xFF;
            result += QString("%1").arg(byte, 2, 16, QChar('0'));
        }
    }

    return result;
}