#include <iostream>
#include <string>
#include <stdint.h> // for uint* type
#include <limits.h> // for CHAR_BIT
using namespace std;

const uint32_t T[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x2441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

const unsigned int SHIFT[4][4]{
        {7, 12, 17, 22},
        {5, 9, 14, 20},
        {4, 11, 16, 23},
        {6, 10, 15, 21}};

const uint8_t PADDING[] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

inline uint32_t Left_Rotate32(uint32_t x, unsigned int num)
{
    num &= 31;
    return (x << num) | (x >> (-num & 31));
}

inline uint32_t Logic_Function(int Round_i, uint32_t b, uint32_t c, uint32_t d)
{
    switch (Round_i)
    {
        case 3:
            return c ^ (b | ~d);
        case 2:
            return b ^ c ^ d;
        case 1:
            return (b & d) | (c & ~d);
        case 0:
            return (b & c) | (~b & d);
    }
    return 0;
}

inline unsigned int Substituion(int Round_i, int i)
{
    switch (Round_i)
    {
        case 0:
            return i;
        case 1:
            return (1 + 5 * i) % 16;
        case 2:
            return (5 + 3 * i) % 16;
        case 3:
            return (7 * i) % 16;
    }
    return 0;
}
void Round_Function(int Round_i, uint32_t buffer[4], const uint32_t message_block[16])
{
    // Input:
    // Logic_Function				- provided by Round_i
    // T Table[Round_i*16 +(0-16)]	- provided by Round_i
    // Message Block
    // Buffer

    // Output:
    // void, but UPDATE buffer

    // Elements:
    // i = Round_i * 16 + i;
    // k = substituion(Round_i, i)
    for (int i = 0; i < 16; i++)
    {
        // 1. Calculation
        buffer[0] += Logic_Function(Round_i, buffer[1], buffer[2], buffer[3]);
        buffer[0] += message_block[Substituion(Round_i, i)];
        buffer[0] += T[Round_i * 16 + i];
        buffer[0] = Left_Rotate32(buffer[0], SHIFT[Round_i][i % 4]);
        buffer[0] += buffer[1];

        // 2. Rotate Buffer
        // Buffer right rotate by 1WORD(32-bit)
        uint32_t bufferCache = buffer[3];
        buffer[3] = buffer[2];
        buffer[2] = buffer[1];
        buffer[1] = buffer[0];
        buffer[0] = bufferCache;
    }
    return;
}

void Hash_MD5(uint32_t chain_vector[4], const uint32_t message_block[16])
{
    // traverse message_block, MD5 iteration
    uint32_t buffer[4];
    memcpy(buffer, chain_vector, 128 / CHAR_BIT);

    // For loop, i control Round function
    for (int i = 0; i < 4; i++)
        Round_Function(i, buffer, message_block);

    // Update chain_vector
    for (int i = 0; i < 4; i++)
        chain_vector[i] += buffer[i];
}

__uint128_t MD5(string _message)
{
    // 1. Pre-process message
    // padding & append length info
    // padding cached array
    // append messageBITcount, naturally store by litter-endian in C++
    uint64_t messageLength = _message.length();
    uint64_t messageBitCount = messageLength * CHAR_BIT;
    int blockCount = (messageBitCount + 64) / 512 + 1;
    uint8_t message[64 * blockCount];
    memcpy(message, _message.c_str(), messageLength);
    for (int i = messageLength, j = 0; i < (64 * blockCount - 8); i++)
        message[i] = PADDING[j++];

    memcpy(message + (64 * blockCount - 8), &messageBitCount, 64 / CHAR_BIT);

    uint32_t *messageBuffer = new uint32_t[16];

    // 2. Init Chain_vector_0 as a const
    // PAY ATTENTION TO THE IV ORDER!!
    // WRONG!! uint32_t res[4] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};
    uint32_t res[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
    for (int i = 0; i < blockCount; i++)
    {
        // Update Message_Block
        memcpy(messageBuffer, message + 64 * i, 64);
        Hash_MD5(res, messageBuffer);
    }

    // Output
    __uint128_t md5 = 0;
    for (int i = 0; i < 4; i++)
        md5 += (__uint128_t)res[i] << (i * 32);

    delete[] messageBuffer;
    return md5;
}

void MD5_Print(__uint128_t in)
{
    unsigned char *ptr = (unsigned char *)&in;
    for (int i = 0; i < 16; i++)
        printf("%02x", ptr[i]);
}

int main(void)
{
#ifdef LOCAL_COMPILE
    // freopen("in", "r", stdin);
	// freopen("out", "w", stdout);
#endif

    // user interface
    cout << "----------------- MD5 -----------------\n";
    cout << "INFO: Input a line of text, ended with an enter. (to end program input CTRL + C)\n";
    cout << "-----------------------\n";
    string str;
    while (1)
    {
        cout << "text: ";
        getline(cin, str);
        __uint128_t md5 = MD5(str);

        cout << "result: ";
        MD5_Print(md5);

        cout << "\n-----------------------\n";
    }

    return 0;
}
