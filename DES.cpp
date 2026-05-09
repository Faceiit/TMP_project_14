#include "DES.h"
#include <algorithm>

DES::DES() {}

std::bitset<28> DES::leftShift(std::bitset<28> bs, int n) {
    return (bs << n) | (bs >> (28 - n));
}

void DES::generateSubkeys(std::bitset<64> key) {
    subkeys.clear();
    // Упрощенная генерация (для полной версии здесь нужны таблицы PC-1, PC-2)
    std::bitset<28> left, right;
    for(int i=0; i<28; ++i) {
        right[i] = key[i];
        left[i] = key[i+28];
    }

    for (int i = 0; i < 16; ++i) {
        int shift = (i == 0 || i == 1 || i == 8 || i == 15) ? 1 : 2;
        left = leftShift(left, shift);
        right = leftShift(right, shift);
        
        std::bitset<48> combined;
        for(int j=0; j<24; ++j) {
            combined[j] = right[j];
            combined[j+24] = left[j];
        }
        subkeys.push_back(combined);
    }
}

std::bitset<32> DES::f(std::bitset<32> R, std::bitset<48> k) {
    // В реальном DES здесь S-блоки. Для примера - XOR.
    return std::bitset<32>(R.to_ullong() ^ (k.to_ullong() & 0xFFFFFFFF));
}

std::bitset<64> DES::bytesToBitset(const QByteArray &data) {
    std::bitset<64> bt(0);
    for (int i = 0; i < 8 && i < data.size(); ++i) {
        bt |= (std::bitset<64>(static_cast<unsigned char>(data[i])) << (i * 8));
    }
    return bt;
}

QByteArray DES::bitsetToBytes(std::bitset<64> bt) {
    QByteArray out;
    for (int i = 0; i < 8; ++i) {
        out.append(static_cast<char>((bt >> (i * 8)).to_ullong() & 0xFF));
    }
    return out;
}

QByteArray DES::process(const QByteArray &data, const QByteArray &key, bool decrypt) {
    generateSubkeys(bytesToBitset(key));
    if (decrypt) std::reverse(subkeys.begin(), subkeys.end());

    QByteArray result;
    // Обработка данных блоками по 8 байт
    for (int i = 0; i < data.size(); i += 8) {
        QByteArray chunk = data.mid(i, 8);
        if (chunk.size() < 8) chunk.append(8 - chunk.size(), char(0));

        std::bitset<64> block = bytesToBitset(chunk);
        std::bitset<32> L = (block >> 32).to_ullong();
        std::bitset<32> R = block.to_ullong();

        for (int j = 0; j < 16; ++j) {
            std::bitset<32> nextL = R;
            R = L ^ f(R, subkeys[j]);
            L = nextL;
        }

        std::bitset<64> finalBlock = (std::bitset<64>(R.to_ullong()) << 32) | std::bitset<64>(L.to_ullong());
        result.append(bitsetToBytes(finalBlock));
    }
    return result;
}