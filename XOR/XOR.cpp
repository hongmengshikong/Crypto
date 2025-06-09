// xor.cpp
#include "XOR.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>

// 生成密钥（简单按索引生成）
static std::vector<char> generate_key(size_t size) {
    std::vector<char> key;
    key.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        key.push_back(static_cast<char>(i));
    }
    return key;
}

// XOR 加密/解密函数
static std::string xor_encrypt_decrypt(const std::string& input, const std::vector<char>& key) {
    std::string output = input;
    size_t key_size = key.size();
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key[i % key_size];
    }
    return output;
}

// 将字符串转为 hex 字符串（小写格式：aa bb cc...）
static std::string to_hex_string(const std::string& input) {
    std::stringstream hex_stream;
    for (unsigned char c : input) {
        hex_stream << std::setw(2) << std::setfill('0') << std::hex
                   << (int)(static_cast<uint8_t>(c)) << " ";
    }
    std::string result = hex_stream.str();
    if (!result.empty()) result.pop_back(); // 去掉最后多余的空格
    return result;
}

// 默认加密函数：使用固定长度密钥
std::string xor_encrypt(const std::string& plaintext) {
    std::vector<char> key = generate_key(8); // 固定长度8
    std::string encrypted = xor_encrypt_decrypt(plaintext, key);
    return to_hex_string(encrypted);
}

// 自定义密钥加密函数
std::string xor_encrypt_with_key(const std::string& plaintext, const std::string& key_str) {
    std::vector<char> key(key_str.begin(), key_str.end());
    std::string encrypted = xor_encrypt_decrypt(plaintext, key);
    return to_hex_string(encrypted);
}