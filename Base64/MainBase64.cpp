#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>

#include "EncryptBase64.h"
#include "DecryptBase64.h"

int main() {
    // 自定义 Base64 编码表
    const char base64_table[] = "QWERTYUIOPASDFGHJKLZXCVBNMabcdefghijklmnopqrstuvwxyz0123456789+/";

    // 解码表初始化
    uint8_t decode_table[128];
    std::memset(decode_table, 0xFF, sizeof(decode_table));
    for (int i = 0; i < 64; ++i) {
        decode_table[(uint8_t)base64_table[i]] = i;
    }

    // 原始数据
    std::string original = "Hello";

    // 加密
    std::string encoded = encode_base64(original, base64_table);
    std::cout << "Encoded: " << encoded << std::endl;

    // 解密
    std::string decoded = decode_base64(encoded, decode_table);
    std::cout << "Decoded: " << decoded << std::endl;

    return 0;
}
