#ifndef DECRYPT_TEA_H
#define DECRYPT_TEA_H

#include <vector>
#include <string>
#include <cstdint>

void DecryptBlock(uint32_t* v, const uint32_t* key);
std::string DecryptString(const std::vector<uint8_t>& cipher, const uint32_t* key);

#endif