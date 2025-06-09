#include "EncryptTEA.h"
#include <cstring>

const uint32_t DELTA = 0x9E3779B9;

void EncryptBlock(uint32_t* v, const uint32_t* key) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0;
    for (int i = 0; i < 32; ++i) {
        sum += DELTA;
        v0 += ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        v1 += ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
    }
    v[0] = v0; v[1] = v1;
}

void EncryptString(const std::string& plain, const uint32_t* key, std::vector<uint8_t>& out) {
    size_t len = plain.size();
    size_t pad = 8 - (len % 8);
    std::string padded = plain + std::string(pad, static_cast<char>(pad));

    for (size_t i = 0; i < padded.size(); i += 8) {
        uint32_t block[2];
        memcpy(&block[0], &padded[i], 4);
        memcpy(&block[1], &padded[i + 4], 4);
        EncryptBlock(block, key);
        uint8_t* b = reinterpret_cast<uint8_t*>(block);
        out.insert(out.end(), b, b + 8);
    }
}