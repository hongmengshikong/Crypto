//
// Created by 时空 on 2025/6/6.
//

#ifndef DECRYPT_BASE64_H
#define DECRYPT_BASE64_H

#include <string>
#include <cstdint>

std::string decode_base64(const std::string& src, const uint8_t* decode_table);

#endif

