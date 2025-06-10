#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "RSA.h"

using namespace std;

int main() {
    // 创建RSA对象，自动生成密钥对
    RSA rsa;

    string input;
    cout << "请输入要加密的字符串: ";
    getline(cin, input);

    // 加密
    vector<long long> cipherText = rsa.Encrypt(input);

//    cout << "加密后的数据: ";
//    for (long long cipher : cipherText) {
//        cout << cipher << " ";
//    }
//    cout << endl;

    // 将 cipherText 转换为字符串
    stringstream ss;
    for (long long cipher : cipherText) {
        ss << cipher << " ";
    }
    string cipherStr = ss.str();

    // 输出字符串中的内容
    cout << "加密后的字符串表示: " << cipherStr << endl;


    // 解密
    string decryptedText = rsa.Decrypt(cipherText);
    cout << "解密后的字符串: " << decryptedText << endl;

    return 0;
}