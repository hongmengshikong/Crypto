#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include "Utils.h"

using namespace std;


int main() {
    string plaintext = "中文123English";
    string keyText = "MySecrK1"; // 8字节密钥

    cout << "原文: " << plaintext << endl;

    // 准备密钥
    Block key = stringToBlock(keyText);

    // 明文转为分组
    vector<Block> blocks = stringToBlocks(plaintext);
    vector<Block> encryptedBlocks;

    // 加密每个分组
    for (auto blk : blocks) {
        des(blk, key, e);
        encryptedBlocks.push_back(blk);
    }

    std::string result = blockToHex(encryptedBlocks);

    std::cout << "密文 (hex): " << result << std::endl;
//    // 输出加密结果（二进制显示）
//    cout << "密文（二进制）:" << endl;
//    for (const auto& blk : encryptedBlocks) {
//        cout << blk << endl;
//    }

    // 解密
    vector<Block> decryptedBlocks;
    for (auto blk : encryptedBlocks) {
        des(blk, key, d);
        decryptedBlocks.push_back(blk);
    }

    string decrypted = blocksToString(decryptedBlocks);

    // 去除尾部可能存在的 '\0' 补位
    decrypted.erase(decrypted.find_last_not_of('\0') + 1);

    cout << "解密后: " << decrypted << endl;

    return 0;
}
