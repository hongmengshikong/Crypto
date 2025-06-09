#include <iostream>
#include <string>
#include "EncryptTEA.h"
#include "DecryptTEA.h"
#include "Utils.h"

int main() {
    std::string plainText = "123中文";
    std::string keyStr = "this_is_tea_flag"; // 16-byte key string

    uint32_t key[4];
    StringToKey(keyStr, key);

    std::vector<uint8_t> encryptedData;
    EncryptString(plainText, key, encryptedData);
    std::string hexResult = BytesToHex(encryptedData);

    std::cout << "Encrypted data (hex): " << hexResult << std::endl;
//    for (auto b : encryptedData) {
//        printf("%02X ", b);
//    }

//    std::cout << std::endl;

    std::string decryptedText = DecryptString(encryptedData, key);
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    return 0;
}