#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <cstdint>

std::string BytesToHex(const std::vector<uint8_t>& data);
void StringToKey(const std::string& strKey, uint32_t key[4]);

#endif // UTILS_H
