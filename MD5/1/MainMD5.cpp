#include <iostream>
#include <string>
#include "md5.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    string input;

    cout << "请输入要加密的字符串: ";
    getline(cin, input);  // 支持包含空格的完整输入

    // 直接在 main 中进行 MD5 计算和输出
    cout << "md5(\"" << input << "\") = "
         << MD5(input).toStr() << endl;

    return 0;
}