#include "Utils.h"
#include <cstring>

std::string BytesToHex(const std::vector<uint8_t>& data) {
    const char* hex_chars = "0123456789ABCDEF";
    std::string hex;
    hex.reserve(data.size() * 2);

    for (uint8_t byte : data) {
        hex += hex_chars[(byte >> 4) & 0xF];
        hex += hex_chars[byte & 0xF];
    }

    return hex;
}

void StringToKey(const std::string& strKey, uint32_t key[4]) {
    std::string paddedKey = strKey;
    paddedKey.resize(16, '\0');  // Ensure it is at least 16 bytes
    std::memcpy(key, paddedKey.data(), 16); // Copy 16 bytes into 4 uint32_t
}
