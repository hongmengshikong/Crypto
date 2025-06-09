#include <iostream>
#include "aes.h"
#include "Utils.h"

int main() {
//    unsigned char key[16] = {
//            0x2b, 0x7e, 0x15, 0x16,
//            0x28, 0xae, 0xd2, 0xa6,
//            0xab, 0xf7, 0x15, 0x88,
//            0x09, 0xcf, 0x4f, 0x3c
//    };
    std::string keyStr = "this_is_aes_flag"; // 确保是16字节
    unsigned char key[16];
    StringToKey(keyStr, key);  // 正确转换


//    unsigned char plain[16] = "你好123Englis"; // 16字节

    std::string originalText = "123中文";  // 任意长度
    std::vector<unsigned char> padded = PadTo16Bytes(originalText);  // padding

    AES aes(key);  // ✅ 传入key进行初始化

//    std::cout << "原文: ";
//    for (int i = 0; i < 16; i++) std::cout << plain[i];
//    std::cout << std::endl;
//
//    aes.Cipher(plain);  // 加密
//
//    std::cout << "密文: ";
//    for (int i = 0; i < 16; i++) printf("%02x ", plain[i]);
//    std::cout << std::endl;
//
//    aes.InvCipher(plain);  // 解密
//
//    std::cout << "解密后: ";
//    for (int i = 0; i < 16; i++) std::cout << plain[i];
//    std::cout << std::endl;

    // 分块加密
    for (size_t i = 0; i < padded.size(); i += 16)
        aes.Cipher(&padded[i]);

    std::string result = BytesToHex(padded);

    std::cout << "密文 (hex): " << result << std::endl;


    // 解密
    for (size_t i = 0; i < padded.size(); i += 16)
        aes.InvCipher(&padded[i]);

    RemovePadding(padded);  // 去除 padding

    std::cout << "解密后: ";
    for (unsigned char c : padded) std::cout << c;
    std::cout << std::endl;

    return 0;
}
