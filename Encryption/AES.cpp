#include<iostream>
#include<bitset>
using namespace std;

//定义S盒
const unsigned char SBox[16][16] = {
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

//定义轮常量Rcon
const unsigned int Rcon[10] = {
        0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,
        0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000
};

//字替代操作
unsigned int SubWord(unsigned int X){
    unsigned char a3 =  X & 0x000000ff;
    unsigned char a2 = (X & 0x0000ff00) >> 8;
    unsigned char a1 = (X & 0x00ff0000) >> 16;
    unsigned char a0 = (X & 0xff000000) >> 24;
    unsigned char b3 = SBox[(a3 & 0xf0) >> 4][a3 & 0x0f];
    unsigned char b2 = SBox[(a2 & 0xf0) >> 4][a2 & 0x0f];
    unsigned char b1 = SBox[(a1 & 0xf0) >> 4][a1 & 0x0f];
    unsigned char b0 = SBox[(a0 & 0xf0) >> 4][a0 & 0x0f];

    return ((b0 << 24) | (b1 << 16) | (b2 << 8) | (b3));
}

//定义轮密钥加操作
void ADDROUNDKEY(unsigned int *state, unsigned int *w, int num_round){
    state[0] = state[0] ^ w[4 * num_round + 0];
    state[1] = state[1] ^ w[4 * num_round + 1];
    state[2] = state[2] ^ w[4 * num_round + 2];
    state[3] = state[3] ^ w[4 * num_round + 3];
}

//定义字节代替操作
void SUBBYTES(unsigned int *state){
    state[0] = SubWord(state[0]);
    state[1] = SubWord(state[1]);
    state[2] = SubWord(state[2]);
    state[3] = SubWord(state[3]);
}

//行移位操作
unsigned int RotRows(unsigned int A, int ROW){
    return (A >> (sizeof(unsigned int)*8 - 8*ROW) | (A << 8*ROW));
}

//移位操作(8bit)
unsigned int RotWord(unsigned int A){
    return (A >> (sizeof(unsigned int)*8 - 8) | (A << 8));
}

void SHIFTROWS(unsigned int *state){
    unsigned int b0 = (state[0] & 0xff000000) | ((state[1] & 0xff000000) >> 8) | ((state[2] & 0xff000000) >> 16) | ((state[3] & 0xff000000) >> 24);
    unsigned int b1 = ((state[0] & 0x00ff0000) << 8) | (state[1] & 0x00ff0000) | ((state[2] & 0x00ff0000) >> 8 ) | ((state[3] & 0x00ff0000) >> 16);
    unsigned int b2 = ((state[0] & 0x0000ff00) << 16) | ((state[1] & 0x0000ff00) << 8) | (state[2] & 0x0000ff00) | ((state[3] & 0x0000ff00) >> 8 );
    unsigned int b3 = ((state[0] & 0x000000ff) << 24) | ((state[1] & 0x000000ff) << 16) | ((state[2] & 0x000000ff) << 8) | (state[3] & 0x000000ff);
    //cout << hex << b0 << " \t" << b1 << " \t" << b2 << " \t" << b3 << " \t" << endl;
    b0 = RotRows(b0, 0);
    b1 = RotRows(b1, 1);
    b2 = RotRows(b2, 2);
    b3 = RotRows(b3, 3);
    //cout << hex << b0 << " \t" << b1 << " \t" << b2 << " \t" << b3 << " \t" << endl;
    state[0] = (b0 & 0xff000000) | ((b1 & 0xff000000) >> 8) | ((b2 & 0xff000000) >> 16) | ((b3 & 0xff000000) >> 24);
    state[1] = ((b0 & 0x00ff0000) << 8) | (b1 & 0x00ff0000) | ((b2 & 0x00ff0000) >> 8 ) | ((b3 & 0x00ff0000) >> 16);
    state[2] = ((b0 & 0x0000ff00) << 16) | ((b1 & 0x0000ff00) << 8) | (b2 & 0x0000ff00) | ((b3 & 0x0000ff00) >> 8 );
    state[3] = ((b0 & 0x000000ff) << 24) | ((b1 & 0x000000ff) << 16) | ((b2 & 0x000000ff) << 8) | (b3 & 0x000000ff);
}

//定义扩域上的b•{02}操作
unsigned char GFMul2(unsigned char x){
    if((x & 0x80) == 0x00)
        return x << 1;
    else
        return ((x << 1) ^ 0x1b);
}

//定义扩域上的b•{03}操作
unsigned char GFMul3(unsigned char x){
    return (x^GFMul2(x));
}

//定义列混淆操作
void MIXCOLUMNS(unsigned int *state){
    for(int i = 0; i < 4; i++){
        unsigned char a0 = (state[i] & 0xff000000) >> 24;
        unsigned char a1 = (state[i] & 0x00ff0000) >> 16;
        unsigned char a2 = (state[i] & 0x0000ff00) >> 8 ;
        unsigned char a3 = (state[i] & 0xff0000ff);
        unsigned char b0 =  GFMul2(a0)^GFMul3(a1)^a2^a3;
        unsigned char b1 =  a0^GFMul2(a1)^GFMul3(a2)^a3;
        unsigned char b2 =  a0^a1^GFMul2(a2)^GFMul3(a3);
        unsigned char b3 =  GFMul3(a0)^a1^a2^GFMul2(a3);

        state[i] = (b0 << 24) | (b1 << 16) | (b2<< 8) | b3;
    }
}

//定义密钥扩展函数
void KeyExpansion(unsigned int *key, unsigned int *w, unsigned int Nk, unsigned int Nr){
    unsigned int i = 0;
    while(i <= Nk-1){
        w[i] = key[i];
        i = i + 1;
    }
    //cout << "i" << " \t" << "temp" << " \t" << "w[i-Nk]" << " \t" << "w[i]" << endl;
    while(i <= 4*Nr + 3){
        unsigned int temp = w[i-1];
        if(i % Nk == 0)
            temp = SubWord(RotWord(temp))^Rcon[i/Nk-1];
        else if(Nk > 6 && i%Nk == 4)
            temp = SubWord(temp);
        w[i] = w[i-Nk]^temp;
        //cout << oct << i << " \t" << hex << temp << " \t" << w[i-Nk] << " \t" << w[i] << endl;
        i = i + 1;

    }
}

int main(void){
    unsigned int input[4] = {0x3243f6a8, 0x885a308d, 0x313198a2, 0xe0370734};
    unsigned int KEY[4]   = {0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c};
    unsigned int Nk = 4;
    unsigned int Nr = 10;

    unsigned int w[4*(Nr+1)] = {0x00000000};
    KeyExpansion(KEY, w, Nk, Nr);//获取轮密钥
    ADDROUNDKEY(input, w, 0);
    for(int i = 1; i <= (Nr - 1); i++){
        SUBBYTES(input);
        SHIFTROWS(input);
        MIXCOLUMNS(input);
        ADDROUNDKEY(input, w, i);
    }
    SUBBYTES(input);
    SHIFTROWS(input);
    ADDROUNDKEY(input, w, Nr);
    cout << hex << input[0] << " \t" << input[1] << " \t" << input[2] << " \t" << input[3] << endl ;
    return 0;
}