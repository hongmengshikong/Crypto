//
// Created by 时空 on 2025/6/6.
//

#include "EncryptBase64.h"

std::string encode_base64(const std::string& src, const char* base64_table) {
    std::string encoded;
    int i = 0;
    int len = src.length();
    while (i + 2 < len) {
        encoded += base64_table[(src[i] >> 2) & 0x3F];
        encoded += base64_table[((src[i] & 0x03) << 4) | (src[i + 1] >> 4)];
        encoded += base64_table[((src[i + 1] & 0x0F) << 2) | (src[i + 2] >> 6)];
        encoded += base64_table[src[i + 2] & 0x3F];
        i += 3;
    }
    if (i < len) {
        encoded += base64_table[(src[i] >> 2) & 0x3F];
        if (i + 1 < len) {
            encoded += base64_table[((src[i] & 0x03) << 4) | (src[i + 1] >> 4)];
            encoded += base64_table[(src[i + 1] & 0x0F) << 2];
            encoded += '=';
        } else {
            encoded += base64_table[(src[i] & 0x03) << 4];
            encoded += '=';
            encoded += '=';
        }
    }
    return encoded;
}

