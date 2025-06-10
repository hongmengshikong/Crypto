#include "RSA.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

RSA::RSA() {
    srand(time(NULL));
    KeyGeneration();
}

RSA::~RSA() {
    // 析构函数，清理工作（如果需要）
}

ll RSA::gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

bool RSA::isPrime(ll num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    for (ll i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

ll RSA::ModularExponention(ll a, ll b, ll n) {
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

ll RSA::extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd_val = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd_val;
}

ll RSA::ModularInverse(ll a, ll m) {
    ll x, y;
    ll g = extgcd(a, m, x, y);
    if (g != 1) return -1;  // 模逆不存在
    return (x % m + m) % m;
}

void RSA::KeyGeneration() {
    vector<ll> small_primes;

    // 生成100-1000范围内的素数
    for (ll i = 100; i < 1000; i++) {
        if (isPrime(i)) {
            small_primes.push_back(i);
        }
    }

    if (small_primes.size() < 2) {
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
}

vector<ll> RSA::Encrypt(const string& plaintext) {
    vector<ll> ciphertext;

    for (int i = 0; i < plaintext.length(); i++) {
        unsigned char ch = plaintext[i];
        ll value = (ll)ch;
        ll cipher = ModularExponention(value, e, n);
        ciphertext.push_back(cipher);
    }

    return ciphertext;
}

string RSA::Decrypt(const vector<ll>& ciphertext) {
    string plaintext = "";

    for (ll cipher : ciphertext) {
        ll decipher = ModularExponention(cipher, d, n);
        char ch = (char)decipher;
        plaintext += ch;
    }

    return plaintext;
}