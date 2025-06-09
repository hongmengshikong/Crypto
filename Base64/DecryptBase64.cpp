//
// Created by 时空 on 2025/6/6.
//

#include "DecryptBase64.h"
#include <stdexcept>

std::string decode_base64(const std::string& src, const uint8_t* decode_table) {
    std::string output;
    uint32_t buf = 0;
    int bits = 0;

    for (char c : src) {
        if (c == '=') break;

        if ((unsigned char)c > 127)
            throw std::invalid_argument("Invalid character in base64 input");

        uint8_t val = decode_table[(uint8_t)c];
        buf = (buf << 6) | val;
        bits += 6;

        if (bits >= 8) {
            bits -= 8;
            output += (char)((buf >> bits) & 0xFF);
        }
    }

    return output;
}
