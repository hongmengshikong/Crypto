#include <bits/stdc++.h>
using namespace std;

void Encrypt(long* EntryData, long* Key) {
    //分别加密数组中的前四个字节与后4个字节,4个字节为一组每次加密两组
    unsigned long x = EntryData[0];
    unsigned long y = EntryData[1];

    unsigned long sum = 0;
    unsigned long delta = 0x9E3779B9;
    //总共加密32轮
    for (int i = 0; i < 32; i++) {
        sum += delta;
        x += ((y << 4) + Key[0]) ^ (y + sum) ^ ((y >> 5) + Key[1]);
        y += ((x << 4) + Key[2]) ^ (x + sum) ^ ((x >> 5) + Key[3]);
    }
    //最后加密的结果重新写入到数组中
    EntryData[0] = x;
    EntryData[1] = y;
}

void Decrypt(long* EntryData, long* Key) {
    //分别加密数组中的前四个字节与后4个字节,4个字节为一组每次加密两组
    unsigned long x = EntryData[0];
    unsigned long y = EntryData[1];

    unsigned long sum = 0;
    unsigned long delta = 0x9E3779B9;
    sum = delta << 5;   //注意这里,sum = 32轮之后的黄金分割值. 因为我们要反序解密.
    //总共加密32轮 那么反序也解密32轮
    for (int i = 0; i < 32; i++) {
        // 先将y解开 然后参与运算在解x
        y -= ((x << 4) + Key[2]) ^ (x + sum) ^ ((x >> 5) + Key[3]);
        x -= ((y << 4) + Key[0]) ^ (y + sum) ^ ((y >> 5) + Key[1]);
        sum -= delta;
    }
    //最后加密的结果重新写入到数组中
    EntryData[0] = x;
    EntryData[1] = y;
}

int main() {
    long Data[3] = {1, 2};  //明文，必须是8字节的倍数，不够需要程序补全，参考base64方法
    printf("待加密的数值：%d %d\n",Data[0],Data[1]);

    long key[4] = {2,2,3,4 };   //密钥随便

    //Encrypt每次只是加密4字节数组中的两组(也就是每次加密8个字节) 如果你数据多.可以来个for循环来循环加密,但是Entrypt内部还有32次循环,所以速度上还是会有点影响.
    Encrypt(Data, key);
    printf("加密后的数值：%d %d\n",Data[0],Data[1]);
    Decrypt(Data, key);
    printf("解密后的数值：%d %d\n",Data[0],Data[1]);
    system("pause");
}
