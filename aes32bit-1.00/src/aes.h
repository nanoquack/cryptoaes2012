/*
 * Project: aes32bit - AES implementation for 32 bit platforms
 * File   : aes.h
 * Author : Oliver Mueller <oliver@cogito-ergo-sum.org>
 * Purpose: Declaration of class AesEncryption and associates classes.
 *
 * $Id: aes.h 61 2011-06-16 23:45:02Z oliver $
 *
 * Copyright (c) 2011 Oliver Mueller.
 * All rights reserved.
 * http://www.cogito-ergo-sum.org
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the author be held liable for any damages arising from
 * the use of this software.
 *
 */

#ifndef AES_H
#define	AES_H

#if (defined(_MSC_VER) && _MSC_VER < 1600) || (defined(__VMS) && defined(__DECCXX)) || (defined(__osf__) && defined(__alpha__))
// We are on MS Visual Studio before 2010 or
// we are on OpenVMS with DEC/Compaq/HP C++ or
// we are on Tru64 UNIX.
#include "portable/pstdint.h"
#else
// We are on a C99 compliant C/C++ distribution.
// We should use cstdint instead of stdint.h because we are on C++.
// Unfortunately most compilers doesn't support ISO's C++0x which introduces
// cstdint. Most C++ compilers are able to deal wiht stdint.h if they rely on
// a C99 compliant C compiler. So we will use stdint.h here instead of cstdint.
#include <stdint.h>
#endif

#include <string>
#include <vector>
#include <exception>

using namespace std;

class AesException : public exception
{
public:

    enum what_t
    {
        wrongStringLength = 0, wrongCharacter = 1, wrongArrayLength = 2
    };

    AesException(AesException::what_t wt);
    virtual const char *what() const throw ();
    virtual AesException::what_t getWhatType() const throw ();

protected:
    what_t whatType;
    static const char *whatMsg[3];
};

class AesBadKeyException : public AesException
{
public:
    AesBadKeyException(AesBadKeyException::what_t wt);
};

class AesBadHexStringException : public AesException
{
public:
    AesBadHexStringException(AesBadHexStringException::what_t wt);
};

class AesBadIvException : public AesException
{
public:
    AesBadIvException(AesBadIvException::what_t wt);
};

class AesEncryption
{
public:
    AesEncryption(const char* keystring) throw (AesBadKeyException);
    AesEncryption(const string& keystring) throw (AesBadKeyException);
    AesEncryption(const uint8_t keyarray[], int size) throw (AesBadKeyException);
    AesEncryption(const uint32_t keyarray[], int size) throw (AesBadKeyException);

    ~AesEncryption();

    enum CipherMode
    {
        ECB = 0, CBC = 1, CFB = 2, OFB = 3
    };

    vector<uint8_t> encipherVectorToVector(vector<uint8_t> m, AesEncryption::CipherMode mode = AesEncryption::ECB);
    vector<uint8_t> encipher(string m, AesEncryption::CipherMode mode = AesEncryption::ECB);
    vector<uint8_t> encipher(const char *m, AesEncryption::CipherMode mode = AesEncryption::ECB);
    string encipherToHexString(string m, AesEncryption::CipherMode mode = AesEncryption::ECB);
    string encipherHexToHex(string m, AesEncryption::CipherMode mode = AesEncryption::ECB) throw (AesBadHexStringException);

    vector<uint8_t> decipherVectorToVector(vector<uint8_t> c, AesEncryption::CipherMode mode = AesEncryption::ECB);
    string decipher(vector<uint8_t> c, AesEncryption::CipherMode mode = AesEncryption::ECB);
    string decipherToHexString(vector<uint8_t> c, AesEncryption::CipherMode mode = AesEncryption::ECB);
    string decipherFromHexString(string c, AesEncryption::CipherMode mode = AesEncryption::ECB) throw (AesBadHexStringException);
    string decipherHexToHex(string c, AesEncryption::CipherMode mode = AesEncryption::ECB) throw (AesBadHexStringException);

    void setIvFromString(string iv) throw (AesBadIvException);
    void setIvFromHex(string iv) throw (AesBadIvException);
    void setIvFromString(const char *iv) throw (AesBadIvException);
    void setIvFromHex(const char *iv) throw (AesBadIvException);
    void setIvFromArray(const uint8_t iv[]);
    void setIvFromArray(const uint32_t iv[]);

    string getKeyAsHexString();
    string getExpandedKeyAsHexString();

    union word32_t
    {
        uint32_t w;

        struct
        {
#ifdef ARCH_BIG_ENDIAN
            uint8_t b3;
            uint8_t b2;
            uint8_t b1;
            uint8_t b0;
#else
            uint8_t b0;
            uint8_t b1;
            uint8_t b2;
            uint8_t b3;
#endif
        };
    };

    union state_t
    {
        uint32_t w[4];
        uint8_t b[16];

        struct
        {
#ifdef ARCH_BIG_ENDIAN
            uint8_t b3;
            uint8_t b2;
            uint8_t b1;
            uint8_t b0;
            uint8_t b7;
            uint8_t b6;
            uint8_t b5;
            uint8_t b4;
            uint8_t b11;
            uint8_t b10;
            uint8_t b9;
            uint8_t b8;
            uint8_t b15;
            uint8_t b14;
            uint8_t b13;
            uint8_t b12;
#else
            uint8_t b0;
            uint8_t b1;
            uint8_t b2;
            uint8_t b3;
            uint8_t b4;
            uint8_t b5;
            uint8_t b6;
            uint8_t b7;
            uint8_t b8;
            uint8_t b9;
            uint8_t b10;
            uint8_t b11;
            uint8_t b12;
            uint8_t b13;
            uint8_t b14;
            uint8_t b15;
#endif
        };
    };

protected:
    void keyHex2Arr(const char *str) throw (AesBadKeyException);
    string keyArr2Hex(int max);
    string hex2msg(string hex) throw (AesBadHexStringException);
    vector<uint8_t> hex2vector(string hex) throw (AesBadHexStringException);
    string vector2hex(vector<uint8_t> v);
    string msg2hex(string msg);

    // Implementation of AES algorithm
    // ===============================
    // Key expansion
    void expandKey();
    // Encryption
    uint8_t subByte(uint8_t x);
    void subBytes(AesEncryption::state_t& state);
    void shiftRows(AesEncryption::state_t& state);
    void mixColumn(AesEncryption::word32_t& column);
    void mixColumns(AesEncryption::state_t& state);
    void encipherState(AesEncryption::state_t& state);
    // Decryption
    uint8_t invSubByte(uint8_t x);
    void invSubBytes(AesEncryption::state_t& state);
    void invShiftRows(AesEncryption::state_t& state);
    void invMixColumn(AesEncryption::word32_t& column);
    void invMixColumns(AesEncryption::state_t& state);
    void decipherState(AesEncryption::state_t& state);
    // Both modes
    void addRoundKey(AesEncryption::state_t& state, unsigned round);
    // GF(256) operations
    uint8_t gmul(uint8_t p, uint8_t q);

    // AES data
    int knum;                     // Nk
    int rnum;                     // Nr
    AesEncryption::word32_t *key; // expanded key
    AesEncryption::state_t iv;    // initialization vector for CBC, CFB, OFB

    static const uint32_t rcon[15];    // Rcon
    static const uint8_t sbox[256];    // s-box
    static const uint8_t sboxinv[256]; // inverse s-box
    static const char charBase[16];    // characters for hex value conversion
};

inline vector<uint8_t> AesEncryption::encipher(const char *m, AesEncryption::CipherMode mode)
{
    return encipher(string(m), mode);
}

inline void AesEncryption::setIvFromString(const char *iv) throw (AesBadIvException)
{
    setIvFromString(string(iv));
}

inline void AesEncryption::setIvFromHex(const char *iv) throw (AesBadIvException)
{
    setIvFromHex(string(iv));
}

inline uint8_t AesEncryption::subByte(uint8_t x)
{
    return sbox[x];
}

inline uint8_t AesEncryption::invSubByte(uint8_t x)
{
    return sboxinv[x];
}

#endif	/* AES_H */

