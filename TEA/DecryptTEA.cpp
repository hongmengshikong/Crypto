#include "DecryptTEA.h"
#include <cstring>

const uint32_t DELTA = 0x9E3779B9;

void DecryptBlock(uint32_t* v, const uint32_t* key) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = DELTA * 32;
    for (int i = 0; i < 32; ++i) {
        v1 -= ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
        v0 -= ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        sum -= DELTA;
    }
    v[0] = v0; v[1] = v1;
}

std::string DecryptString(const std::vector<uint8_t>& cipher, const uint32_t* key) {
    std::string result;
    for (size_t i = 0; i < cipher.size(); i += 8) {
        uint32_t block[2];
        memcpy(&block[0], &cipher[i], 4);
        memcpy(&block[1], &cipher[i + 4], 4);
        DecryptBlock(block, key);
        char* b = reinterpret_cast<char*>(block);
        result.append(b, 8);
    }
    char pad = result.back();
    result.resize(result.size() - pad);
    return result;
}
