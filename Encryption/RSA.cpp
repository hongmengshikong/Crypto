#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;
typedef long long ll;

ll e, d, n;

ll gcd(ll a, ll b)  //求最大公约数
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

bool isPrime(ll num)  //判断是否是素数
{
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    for (ll i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

ll ModularExponention(ll a, ll b, ll n)  //求a^b mod n
{
    ll result = 1;
    a = a % n;

    while (b > 0) {
        if (b & 1) {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        b = b >> 1;
    }
    return result;
}

ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

ll ModularInverse(ll a, ll m) {
    ll x, y;
    ll g = extgcd(a, m, x, y);
    if (g != 1) return -1;  // 模逆不存在
    return (x % m + m) % m;
}

void KeyGeneration() {
    srand(time(NULL));

    // 使用较小的素数范围以避免溢出
    vector<ll> small_primes;

    // 生成100-1000范围内的素数
    for (ll i = 100; i < 1000; i++) {
        if (isPrime(i)) {
            small_primes.push_back(i);
        }
    }

    if (small_primes.size() < 2) {
        cout << "Error: Not enough primes found!" << endl;
        return;
    }

    // 随机选择两个不同的素数
    ll p = small_primes[rand() % small_primes.size()];
    ll q;
    do {
        q = small_primes[rand() % small_primes.size()];
    } while (q == p);

    n = p * q;
    ll phi_n = (p - 1) * (q - 1);

    // 选择公钥指数e
    e = 65537; // 常用的公钥指数
    if (gcd(e, phi_n) != 1) {
        // 如果65537不互质，选择其他值
        for (e = 3; e < phi_n; e += 2) {
            if (gcd(e, phi_n) == 1) break;
        }
    }

    d = ModularInverse(e, phi_n);

    cout << "密钥生成完成:" << endl;
    cout << "p = " << p << ", q = " << q << endl;
    cout << "n = " << n << ", phi_n = " << phi_n << endl;
    cout << "公钥 (e, n) = (" << e << ", " << n << ")" << endl;
    cout << "私钥 (d, n) = (" << d << ", " << n << ")" << endl << endl;
}

ll Encryption(ll value) {
    return ModularExponention(value, e, n);
}

ll Decryption(ll value) {
    return ModularExponention(value, d, n);
}

int main(void) {
    KeyGeneration();  // 生成密钥对

    string input;
    cout << "请输入要加密的字符串: ";
    getline(cin, input);

    vector<ll> cipherText;

    // 加密
    cout << "加密过程:" << endl;
    for (int i = 0; i < input.length(); i++) {
        unsigned char ch = input[i];
        ll value = (ll)ch;
        ll cipher = Encryption(value);
        cipherText.push_back(cipher);
        cout << "字符 '" << ch << "' (ASCII: " << value << ") -> " << cipher << endl;
    }

    cout << "\n加密后的数据: ";
    for (ll cipher : cipherText) {
        cout << cipher << " ";
    }
    cout << endl;

    // 解密
    cout << "\n解密过程:" << endl;
    string decrypted = "";
    for (ll cipher : cipherText) {
        ll decipher = Decryption(cipher);
        char ch = (char)decipher;
        decrypted += ch;
        cout << cipher << " -> " << decipher << " ('" << ch << "')" << endl;
    }

    cout << "\n解密后的字符串: " << decrypted << endl;

    // 验证
    if (input == decrypted) {
        cout << "\n✓ 加密解密成功！" << endl;
    } else {
        cout << "\n✗ 加密解密失败！" << endl;
        cout << "原文: " << input << endl;
        cout << "解密: " << decrypted << endl;
    }

    return 0;
}