cmake_minimum_required(VERSION 3.31)
project(Crypto)

set(CMAKE_CXX_STANDARD 20)

add_executable(Base64_APP
        Base64/MainBase64.cpp
        Base64/EncryptBase64.cpp
        Base64/DecryptBase64.cpp
)

add_executable(XOR_APP
        XOR/XOR.cpp
        XOR/MainXOR.cpp
)

add_executable(TEA_APP
        TEA/EncryptTEA.cpp
        TEA/DecryptTEA.cpp
        TEA/MainTEA.cpp
        TEA/Utils.cpp
)

add_executable(AES_APP
        AES/aes.cpp
        AES/MainAES.cpp
        AES/Utils.cpp
)

add_executable(DES_APP
        DES/des.cpp
        DES/MainDES.cpp
        DES/Utils.cpp
)

add_executable(RSA_APP
        RSA/RSA.cpp
        RSA/MainRSA.cpp

)

add_executable(MD5_1_APP
        MD5/1/MainMD5.cpp
        MD5/1/md5.cpp
)

add_executable(MD5_1_1_APP
        MD5/1_1/MainMD5.cpp
        MD5/1_1/md5.cpp
)