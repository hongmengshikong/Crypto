#ifndef ENCRYPT_TEA_H
#define ENCRYPT_TEA_H

#include <vector>
#include <string>
#include <cstdint>

void EncryptBlock(uint32_t* v, const uint32_t* key);
void EncryptString(const std::string& plain, const uint32_t* key, std::vector<uint8_t>& out);

#endif