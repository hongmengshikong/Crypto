#include <cstring>
#include "Utils.h"
void StringToKey(const std::string& strKey, unsigned char key[16]) {
    std::string paddedKey = strKey;
    paddedKey.resize(16, '\0');  // pad to 16 bytes
    std::memcpy(key, paddedKey.data(), 16);
}

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


std::vector<unsigned char> PadTo16Bytes(const std::string& input) {
    std::vector<unsigned char> padded(input.begin(), input.end());
    size_t padLen = 16 - (padded.size() % 16);
    padded.insert(padded.end(), padLen, static_cast<unsigned char>(padLen));
    return padded;
}

void RemovePadding(std::vector<unsigned char>& data) {
    if (data.empty()) return;
    unsigned char padLen = data.back();
    if (padLen > 16) return; // 防止异常 padding
    data.resize(data.size() - padLen);
}
