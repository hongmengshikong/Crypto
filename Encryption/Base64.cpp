//
// Created by 时空 on 2025/6/6.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cstdint>

// 自定义 Base64 编码表
const char base64_table[] = "QWERTYUIOPASDFGHJKLZXCVBNMabcdefghijklmnopqrstuvwxyz0123456789+/";

// 解码表（ASCII 范围 0~127）
unsigned char decode_base64_table[128];

// 初始化解码表
void init_decode_table() {
    std::fill(std::begin(decode_base64_table), std::end(decode_base64_table), 64); // 默认非法字符为 64
    for (int i = 0; i < 64; ++i) {
        decode_base64_table[(unsigned char)base64_table[i]] = i;
    }
}

// 编码函数
std::string encode(const std::string &src) {
    std::string encoded;
    size_t len = src.size();
    size_t i = 0;

    while (i + 3 <= len) {
        unsigned char b1 = src[i];
        unsigned char b2 = src[i + 1];
        unsigned char b3 = src[i + 2];
        encoded += base64_table[b1 >> 2];
        encoded += base64_table[((b1 & 0x03) << 4) | (b2 >> 4)];
        encoded += base64_table[((b2 & 0x0F) << 2) | (b3 >> 6)];
        encoded += base64_table[b3 & 0x3F];
        i += 3;
    }

    if (len - i == 1) {
        unsigned char b1 = src[i];
        encoded += base64_table[b1 >> 2];
        encoded += base64_table[(b1 & 0x03) << 4];
        encoded += "==";
    } else if (len - i == 2) {
        unsigned char b1 = src[i];
        unsigned char b2 = src[i + 1];
        encoded += base64_table[b1 >> 2];
        encoded += base64_table[((b1 & 0x03) << 4) | (b2 >> 4)];
        encoded += base64_table[(b2 & 0x0F) << 2];
        encoded += '=';
    }

    return encoded;
}

// 解码函数
std::string decode(const std::string &src) {
    int inputLen = src.length();
    if (inputLen % 4 != 0) {
        throw std::invalid_argument("Invalid base64 input length");
    }

    int outputLen = inputLen / 4 * 3;
    if (src[inputLen - 1] == '=') outputLen--;
    if (src[inputLen - 2] == '=') outputLen--;

    std::string output;
    output.reserve(outputLen);

    for (int i = 0; i < inputLen; i += 4) {
        uint32_t buf = 0;
        int pad = 0;

        for (int j = 0; j < 4; ++j) {
            char c = src[i + j];
            if (c == '=') {
                buf <<= 6;
                pad++;
            } else {
                if ((unsigned char)c > 127 || decode_base64_table[(unsigned char)c] == 64) {
                    throw std::invalid_argument("Invalid base64 character");
                }
                buf = (buf << 6) | decode_base64_table[(unsigned char)c];
            }
        }

        output.push_back((buf >> 16) & 0xFF);
        if (pad < 2) output.push_back((buf >> 8) & 0xFF);
        if (pad < 1) output.push_back(buf & 0xFF);
    }

    return output;
}

// 示例测试
int main() {
    init_decode_table();  // 必须先初始化解码表

    std::string original = "你好";
    std::string encoded = encode(original);
    std::string decoded = decode(encoded);

    std::cout << "原文: " << original << std::endl;
    std::cout << "编码: " << encoded << std::endl;
    std::cout << "解码: " << decoded << std::endl;

    if (decoded == original) {
        std::cout << "✅ 编码解码一致！" << std::endl;
    } else {
        std::cout << "❌ 编码解码不一致！" << std::endl;
    }

    return 0;
}
