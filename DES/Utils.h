#ifndef UTILS_H
#define UTILS_H

#include <bitset>
#include <string>
#include <vector>
#include <cstdint>
#include "des.h"


// 将8字节字符串转换为64位Block
Block stringToBlock(const std::string& str);

// 将64位Block转换为字符串
std::string blockToString(const Block& block);

// 将任意长度字符串转换为多个Block
std::vector<Block> stringToBlocks(const std::string& input);

// 将多个Block组合为字符串
std::string blocksToString(const std::vector<Block>& blocks);

std::string blockToHex(const std::vector<Block>& blocks);


std::vector<uint8_t> blockToBytes(const Block& block);


std::string BytesToHex(const std::vector<uint8_t>& data);

#endif // UTILS_H
