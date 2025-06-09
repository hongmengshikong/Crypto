#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstdint>

using namespace std;

// 生成密钥（简单按索引生成）
vector<char> generate_key(size_t size) {
    vector<char> key;
    key.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        key.push_back(static_cast<char>(i));
    }
    return key;
}

// XOR 加密/解密函数
string xor_encrypt_decrypt(const string& input, const vector<char>& key) {
    string output = input;
    size_t key_size = key.size();
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key[i % key_size];
    }
    return output;
}

// 将字符串转为 hex 字符串（小写格式：aa bb cc...）
string to_hex_string(const string& input) {
    stringstream hex_stream;
    for (unsigned char c : input) {
        hex_stream << setw(2) << setfill('0') << hex << (int)(static_cast<uint8_t>(c)) << " ";
    }
    string result = hex_stream.str();
    if (!result.empty()) result.pop_back(); // 去掉最后多余的空格
    return result;
}

// 封装好的加密函数：输入明文，输出 hex 格式加密字符串
string encrypt(const string& plaintext) {
    vector<char> key = generate_key(8); // 固定长度密钥
    string encrypted = xor_encrypt_decrypt(plaintext, key);

    return to_hex_string(encrypted);
}

int main() {
    string original = "你好";
    string encryptedHex = encrypt(original);

    cout << "Original: " << original << endl;
    cout << "Encrypted (Hex): " << encryptedHex << endl;

    return 0;
}