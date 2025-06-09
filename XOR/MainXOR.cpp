#include <iostream>
#include "XOR.h"

int main() {
    std::string original = "你好";
    std::cout << "Original: " << original << std::endl;

    // 使用默认密钥加密
    std::string encrypted1 = xor_encrypt(original);
    std::cout << "Encrypted (default key): " << encrypted1 << std::endl;

    // 使用自定义密钥加密
    std::string custom_key = "my_secret_key";
    std::string encrypted2 = xor_encrypt_with_key(original, custom_key);
    std::cout << "Encrypted (custom key): " << encrypted2 << std::endl;

    return 0;
}