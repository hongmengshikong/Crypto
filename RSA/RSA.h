#ifndef RSA_H
#define RSA_H

#include <vector>
#include <string>
using namespace std;

typedef long long ll;

class RSA {
private:
    ll e, d, n;  // 公钥(e,n)，私钥(d,n)

    // 私有辅助函数
    ll gcd(ll a, ll b);                           // 求最大公约数
    bool isPrime(ll num);                         // 判断是否为素数
    ll ModularExponention(ll a, ll b, ll n);     // 模幂运算 a^b mod n
    ll extgcd(ll a, ll b, ll &x, ll &y);        // 扩展欧几里得算法
    ll ModularInverse(ll a, ll m);               // 求模逆
    void KeyGeneration();                         // 密钥生成

public:
    RSA();                                        // 构造函数，自动生成密钥对
    ~RSA();                                       // 析构函数

    vector<ll> Encrypt(const string& plaintext); // 加密字符串
    string Decrypt(const vector<ll>& ciphertext); // 解密密文

    // 获取密钥信息（可选）
    ll getPublicKeyE() const { return e; }
    ll getPublicKeyN() const { return n; }
};

#endif // RSA_H