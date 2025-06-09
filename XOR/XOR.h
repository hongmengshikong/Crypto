// xor.h
#ifndef XOR_H
#define XOR_H

#include <string>

// 使用默认密钥进行加密，返回十六进制字符串
std::string xor_encrypt(const std::string& plaintext);

// 可选：带自定义密钥的加密版本
std::string xor_encrypt_with_key(const std::string& plaintext, const std::string& key_str);

#endif // XOR_H