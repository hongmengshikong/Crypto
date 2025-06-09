#include <bits/stdc++.h>
using namespace std;

typedef uint32_t uint32;
const uint32 DELTA = 0x9E3779B9;

void EncryptBlock(uint32* v, const uint32* key) {
    uint32 v0 = v[0], v1 = v[1], sum = 0;
    for (int i = 0; i < 32; ++i) {
        sum += DELTA;
        v0 += ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        v1 += ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
    }
    v[0] = v0; v[1] = v1;
}

void DecryptBlock(uint32* v, const uint32* key) {
    uint32 v0 = v[0], v1 = v[1];
    uint32 sum = DELTA * 32;
    for (int i = 0; i < 32; ++i) {
        v1 -= ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
        v0 -= ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        sum -= DELTA;
    }
    v[0] = v0; v[1] = v1;
}

void EncryptString(string plain, const uint32* key, vector<uint8_t>& out) {
    size_t len = plain.size();
    size_t pad = 8 - (len % 8);
    string padded = plain + string(pad, pad);  // PKCS#5 padding

    for (size_t i = 0; i < padded.size(); i += 8) {
        uint32 block[2];
        memcpy(&block[0], &padded[i], 4);
        memcpy(&block[1], &padded[i + 4], 4);
        EncryptBlock(block, key);
        uint8_t* b = reinterpret_cast<uint8_t*>(block);
        out.insert(out.end(), b, b + 8);
    }
}

string DecryptString(const vector<uint8_t>& cipher, const uint32* key) {
    string result;
    for (size_t i = 0; i < cipher.size(); i += 8) {
        uint32 block[2];
        memcpy(&block[0], &cipher[i], 4);
        memcpy(&block[1], &cipher[i + 4], 4);
        DecryptBlock(block, key);
        char* b = reinterpret_cast<char*>(block);
        result.append(b, 8);
    }

    // 去掉 PKCS#5 填充
    char pad = result.back();
    result.resize(result.size() - pad);
    return result;
}

void printHex(const vector<uint8_t>& data) {
    for (uint8_t b : data)
        printf("%02X ", b);
    printf("\n");
}

int main() {
    string input = "你好123Hello";
    uint32 key[4] = {2, 2, 3, 4};

    vector<uint8_t> encrypted;
    EncryptString(input, key, encrypted);

    printf("原始字符串: %s\n", input.c_str());
    printf("加密后的十六进制: ");
    printHex(encrypted);

    string decrypted = DecryptString(encrypted, key);
    printf("解密后的字符串: %s\n", decrypted.c_str());

    return 0;
}
