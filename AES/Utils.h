#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <cstdint>


void StringToKey(const std::string& strKey,unsigned char key[16]);

std::string BytesToHex(const std::vector<uint8_t>& data);
// 将任意长度字符串用 PKCS#7 补齐到 16 的倍数
std::vector<unsigned char> PadTo16Bytes(const std::string& input);
// 从解密后的数据中移除 PKCS#7 补齐
void RemovePadding(std::vector<unsigned char>& data);

#endif // UTILS_H
