/*
 * Project: aes32bit - AES implementation for 32 bit platforms
 * File   : aes.cpp
 * Author : Oliver Mueller <oliver@cogito-ergo-sum.org>
 * Purpose: Implementation of class AesEncryption and associates classes.
 *
 * $Id: aes.cpp 63 2011-06-17 18:10:28Z oliver $
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

#include <cstring>
#include <iostream>
#include "aes.h"

using namespace std;

/*
 ***********************
 * Class AesEncryption *
 ***********************
 */

/*
 * ================= *
 * Static attributes *
 * ================= *
 */

/*
 * Character array for conversions to hex
 */
const char AesEncryption::charBase[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

/*
 * Subsitution box
 */
const uint8_t AesEncryption::sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

/*
 * Inverse substitution box
 */
const uint8_t AesEncryption::sboxinv[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
    0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
    0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
    0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
    0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
    0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
    0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
    0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
    0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
    0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
    0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
    0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
    0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
    0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
    0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
    0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

/*
 * rcon values for key expansion
 */
const uint32_t AesEncryption::rcon[15] = {
    0x00000001, 0x00000002, 0x00000004, 0x00000008,
    0x00000010, 0x00000020, 0x00000040, 0x00000080,
    0x0000001b, 0x00000036, 0x0000006c, 0x000000d8,
    0x000000ab, 0x0000004d, 0x0000009a
};

/*
 * ============ *
 * Constructors *
 * ============ *
 */

AesEncryption::AesEncryption(const char* keystring) throw (AesBadKeyException) :
    key(NULL)
{
    switch(strlen(keystring)) {
        case 32:
            knum = 4;
            rnum = 10;
            break;
        case 48:
            knum = 6;
            rnum = 12;
            break;
        case 64:
            knum = 8;
            rnum = 14;
            break;
        default:
            throw AesBadKeyException(AesBadKeyException::wrongStringLength);
    }
    key = new AesEncryption::word32_t[(rnum + 1) * 4];
    keyHex2Arr(keystring);
    expandKey();
}

AesEncryption::AesEncryption(const string& keystring) throw (AesBadKeyException) :
    key(NULL)
{   
    switch(keystring.length()) {
        case 32:
            knum = 4;
            rnum = 10;
            break;
        case 48:
            knum = 6;
            rnum = 12;
            break;
        case 64:
            knum = 8;
            rnum = 14;
            break;
        default:
            throw AesBadKeyException(AesBadKeyException::wrongStringLength);
    }
    key = new AesEncryption::word32_t[(rnum + 1) * 4];
    keyHex2Arr(keystring.c_str());
    expandKey();
}

AesEncryption::AesEncryption(const uint8_t keyarray[], int size) throw (AesBadKeyException) :
    key(NULL)
{
    switch(size) {
        case 16:
        case 24:
        case 32:
            knum = size / 4;
            rnum = knum + 6;
            break;
        default:
            throw AesBadKeyException(AesBadKeyException::wrongArrayLength);
            break;
    }
    key = new AesEncryption::word32_t[(rnum + 1) * 4];
    for(int n = 0, m = 0; m < size; n++, m += 4) {
        key[n].b0 = keyarray[m];
        key[n].b1 = keyarray[m + 1];
        key[n].b2 = keyarray[m + 2];
        key[n].b3 = keyarray[m + 3];
    }
    expandKey();
}

AesEncryption::AesEncryption(const uint32_t keyarray[], int size) throw (AesBadKeyException) :
    key(NULL)
{
    switch(size) {
        case 4:
        case 6:
        case 8:
            knum = size;
            rnum = knum + 6;
            break;
        default:
            throw AesBadKeyException(AesBadKeyException::wrongArrayLength);
            break;
    }
    key = new AesEncryption::word32_t[(rnum + 1) * 4];
    for(int n = 0; n < size; n++)
        key[n].w = keyarray[n];
    expandKey();
}

/*
 * ========== *
 * Destructor *
 * ========== *
 */

AesEncryption::~AesEncryption()
{
    if(key)
        delete[] key;
}

/*
 * ======= *
 * Methods *
 * ======= *
 */

/*
 * Enciphers a message given as a vector of 8 bit values and
 * returns the cryptogram as a vector of 8 bit values
 */
vector<uint8_t> AesEncryption::encipherVectorToVector(vector<uint8_t> m, AesEncryption::CipherMode mode)
{
    unsigned long len = m.size();
    AesEncryption::state_t state;
    vector<uint8_t> c(len, 0);
    for(int j = 0; j < len; j += 16) {
        state.b0 = m[j];
        state.b1 = m[j + 1];
        state.b2 = m[j + 2];
        state.b3 = m[j + 3];
        state.b4 = m[j + 4];
        state.b5 = m[j + 5];
        state.b6 = m[j + 6];
        state.b7 = m[j + 7];
        state.b8 = m[j + 8];
        state.b9 = m[j + 9];
        state.b10 = m[j + 10];
        state.b11 = m[j + 11];
        state.b12 = m[j + 12];
        state.b13 = m[j + 13];
        state.b14 = m[j + 14];
        state.b15 = m[j + 15];
        switch(mode) {
            case AesEncryption::ECB:
                encipherState(state);
                break;
            case AesEncryption::CBC:
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                encipherState(state);
                iv.w[0] = state.w[0];
                iv.w[1] = state.w[1];
                iv.w[2] = state.w[2];
                iv.w[3] = state.w[3];
                break;
            case AesEncryption::CFB:
                encipherState(iv);
                iv.w[0] ^= state.w[0];
                iv.w[1] ^= state.w[1];
                iv.w[2] ^= state.w[2];
                iv.w[3] ^= state.w[3];
                state.w[0] = iv.w[0];
                state.w[1] = iv.w[1];
                state.w[2] = iv.w[2];
                state.w[3] = iv.w[3];
                break;
            case AesEncryption::OFB:
                encipherState(iv);
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
        }
        c[j] = state.b0;
        c[j + 1] = state.b1;
        c[j + 2] = state.b2;
        c[j + 3] = state.b3;
        c[j + 4] = state.b4;
        c[j + 5] = state.b5;
        c[j + 6] = state.b6;
        c[j + 7] = state.b7;
        c[j + 8] = state.b8;
        c[j + 9] = state.b9;
        c[j + 10] = state.b10;
        c[j + 11] = state.b11;
        c[j + 12] = state.b12;
        c[j + 13] = state.b13;
        c[j + 14] = state.b14;
        c[j + 15] = state.b15;
    }
    return c;
}

/*
 * Enciphers a string object and
 * returns the cryptogram as a vector of 8 bit values
 */
vector<uint8_t> AesEncryption::encipher(string m, AesEncryption::CipherMode mode)
{
    unsigned long len = m.length();
    if(len % 16 != 0) {
        len += 16 - len % 16;
        m.append(len - m.length(), '\0');
    }
    AesEncryption::state_t state;
    vector<uint8_t> c(len, 0);
    for(int j = 0; j < len; j += 16) {
        state.b0 = m[j];
        state.b1 = m[j + 1];
        state.b2 = m[j + 2];
        state.b3 = m[j + 3];
        state.b4 = m[j + 4];
        state.b5 = m[j + 5];
        state.b6 = m[j + 6];
        state.b7 = m[j + 7];
        state.b8 = m[j + 8];
        state.b9 = m[j + 9];
        state.b10 = m[j + 10];
        state.b11 = m[j + 11];
        state.b12 = m[j + 12];
        state.b13 = m[j + 13];
        state.b14 = m[j + 14];
        state.b15 = m[j + 15];
        switch(mode) {
            case AesEncryption::ECB:
                encipherState(state);
                break;
            case AesEncryption::CBC:
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                encipherState(state);
                iv.w[0] = state.w[0];
                iv.w[1] = state.w[1];
                iv.w[2] = state.w[2];
                iv.w[3] = state.w[3];
                break;
            case AesEncryption::CFB:
                encipherState(iv);
                iv.w[0] ^= state.w[0];
                iv.w[1] ^= state.w[1];
                iv.w[2] ^= state.w[2];
                iv.w[3] ^= state.w[3];
                state.w[0] = iv.w[0];
                state.w[1] = iv.w[1];
                state.w[2] = iv.w[2];
                state.w[3] = iv.w[3];
                break;
            case AesEncryption::OFB:
                encipherState(iv);
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
        }
        c[j] = state.b0;
        c[j + 1] = state.b1;
        c[j + 2] = state.b2;
        c[j + 3] = state.b3;
        c[j + 4] = state.b4;
        c[j + 5] = state.b5;
        c[j + 6] = state.b6;
        c[j + 7] = state.b7;
        c[j + 8] = state.b8;
        c[j + 9] = state.b9;
        c[j + 10] = state.b10;
        c[j + 11] = state.b11;
        c[j + 12] = state.b12;
        c[j + 13] = state.b13;
        c[j + 14] = state.b14;
        c[j + 15] = state.b15;
    }
    return c;
}

/*
 * Enciphers a string object and
 * returns the cryptogram as a hex value in a string
 */
string AesEncryption::encipherToHexString(string m, AesEncryption::CipherMode mode)
{
    return vector2hex(encipher(m, mode));
}

/*
 * Takes a message as a hex value in a string,
 * enciphers it and
 * returns the cryptogram as a hex value in a string
 */
string AesEncryption::encipherHexToHex(string m, AesEncryption::CipherMode mode) throw (AesBadHexStringException)
{
    return encipherToHexString(hex2msg(m), mode);
}

/*
 * Deciphers a cryptogram given as a vector of 8 bit values and
 * returns the message as a vector of 8 bit values
 */
vector<uint8_t> AesEncryption::decipherVectorToVector(vector<uint8_t> c, AesEncryption::CipherMode mode)
{
    unsigned long len = c.size();
    AesEncryption::state_t state, tmp;
    vector<uint8_t> m(len, 0);
    for(int j = 0; j < len; j += 16) {
        state.b0 = c[j];
        state.b1 = c[j + 1];
        state.b2 = c[j + 2];
        state.b3 = c[j + 3];
        state.b4 = c[j + 4];
        state.b5 = c[j + 5];
        state.b6 = c[j + 6];
        state.b7 = c[j + 7];
        state.b8 = c[j + 8];
        state.b9 = c[j + 9];
        state.b10 = c[j + 10];
        state.b11 = c[j + 11];
        state.b12 = c[j + 12];
        state.b13 = c[j + 13];
        state.b14 = c[j + 14];
        state.b15 = c[j + 15];
        switch(mode) {
            case AesEncryption::ECB:
                decipherState(state);
                break;
            case AesEncryption::CBC:
                tmp.w[0] = state.w[0];
                tmp.w[1] = state.w[1];
                tmp.w[2] = state.w[2];
                tmp.w[3] = state.w[3];
                decipherState(state);
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                iv.w[0] = tmp.w[0];
                iv.w[1] = tmp.w[1];
                iv.w[2] = tmp.w[2];
                iv.w[3] = tmp.w[3];
                break;
            case AesEncryption::CFB:
                encipherState(iv);
                tmp.w[0] = state.w[0];
                tmp.w[1] = state.w[1];
                tmp.w[2] = state.w[2];
                tmp.w[3] = state.w[3];
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                iv.w[0] = tmp.w[0];
                iv.w[1] = tmp.w[1];
                iv.w[2] = tmp.w[2];
                iv.w[3] = tmp.w[3];
                break;
            case AesEncryption::OFB:
                encipherState(iv);
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
        }
        m[j] = state.b0;
        m[j + 1] = state.b1;
        m[j + 2] = state.b2;
        m[j + 3] = state.b3;
        m[j + 4] = state.b4;
        m[j + 5] = state.b5;
        m[j + 6] = state.b6;
        m[j + 7] = state.b7;
        m[j + 8] = state.b8;
        m[j + 9] = state.b9;
        m[j + 10] = state.b10;
        m[j + 11] = state.b11;
        m[j + 12] = state.b12;
        m[j + 13] = state.b13;
        m[j + 14] = state.b14;
        m[j + 15] = state.b15;
    }
    return m;
}

/*
 * Deciphers a cryptogram in a vector of 8 bit values and
 * returns the message as a string
 */
string AesEncryption::decipher(vector<uint8_t> c, AesEncryption::CipherMode mode)
{
    AesEncryption::state_t state, tmp;
    string m;
    for(int j = 0; j < c.size(); j += 16) {
        state.b0 = c[j];
        state.b1 = c[j + 1];
        state.b2 = c[j + 2];
        state.b3 = c[j + 3];
        state.b4 = c[j + 4];
        state.b5 = c[j + 5];
        state.b6 = c[j + 6];
        state.b7 = c[j + 7];
        state.b8 = c[j + 8];
        state.b9 = c[j + 9];
        state.b10 = c[j + 10];
        state.b11 = c[j + 11];
        state.b12 = c[j + 12];
        state.b13 = c[j + 13];
        state.b14 = c[j + 14];
        state.b15 = c[j + 15];
        switch(mode) {
            case AesEncryption::ECB:
                decipherState(state);
                break;
            case AesEncryption::CBC:
                tmp.w[0] = state.w[0];
                tmp.w[1] = state.w[1];
                tmp.w[2] = state.w[2];
                tmp.w[3] = state.w[3];
                decipherState(state);
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                iv.w[0] = tmp.w[0];
                iv.w[1] = tmp.w[1];
                iv.w[2] = tmp.w[2];
                iv.w[3] = tmp.w[3];
                break;
            case AesEncryption::CFB:
                encipherState(iv);
                tmp.w[0] = state.w[0];
                tmp.w[1] = state.w[1];
                tmp.w[2] = state.w[2];
                tmp.w[3] = state.w[3];
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                iv.w[0] = tmp.w[0];
                iv.w[1] = tmp.w[1];
                iv.w[2] = tmp.w[2];
                iv.w[3] = tmp.w[3];
                break;
            case AesEncryption::OFB:
                encipherState(iv);
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
        }
        m.append(1, (char) state.b0);
        m.append(1, (char) state.b1);
        m.append(1, (char) state.b2);
        m.append(1, (char) state.b3);
        m.append(1, (char) state.b4);
        m.append(1, (char) state.b5);
        m.append(1, (char) state.b6);
        m.append(1, (char) state.b7);
        m.append(1, (char) state.b8);
        m.append(1, (char) state.b9);
        m.append(1, (char) state.b10);
        m.append(1, (char) state.b11);
        m.append(1, (char) state.b12);
        m.append(1, (char) state.b13);
        m.append(1, (char) state.b14);
        m.append(1, (char) state.b15);
    }
    return m;
}

/*
 * Deciphers the cryptogram given by a vector of 8 bit values and
 * converts the message to a hex value provided as a string
 */
string AesEncryption::decipherToHexString(vector<uint8_t> c, AesEncryption::CipherMode mode)
{
    return msg2hex(decipher(c, mode));
}

/*
 * Deciphers the cryptogram given by a hex value in a string and
 * returns the deciphered message as a string
 */
string AesEncryption::decipherFromHexString(string c, AesEncryption::CipherMode mode) throw (AesBadHexStringException)
{
    return decipher(hex2vector(c), mode);
}

/*
 * Deciphers the cryptogram given by a hex value in a string and
 * returns the deciphered message as hex value in a string
 */
string AesEncryption::decipherHexToHex(string c, AesEncryption::CipherMode mode) throw (AesBadHexStringException)
{
    return msg2hex(decipher(hex2vector(c), mode));
}

/*
 * Retrives initialization vector (IV)
 * from a string with at least 16 characters
 */
void AesEncryption::setIvFromString(string iv) throw (AesBadIvException)
{
    if(iv.length() < 16)
        throw AesBadIvException(AesBadIvException::wrongStringLength);
    this->iv.b0 = (uint8_t) iv[0];
    this->iv.b1 = (uint8_t) iv[1];
    this->iv.b2 = (uint8_t) iv[2];
    this->iv.b3 = (uint8_t) iv[3];
    this->iv.b4 = (uint8_t) iv[4];
    this->iv.b5 = (uint8_t) iv[5];
    this->iv.b6 = (uint8_t) iv[6];
    this->iv.b7 = (uint8_t) iv[7];
    this->iv.b8 = (uint8_t) iv[8];
    this->iv.b9 = (uint8_t) iv[9];
    this->iv.b10 = (uint8_t) iv[10];
    this->iv.b11 = (uint8_t) iv[11];
    this->iv.b12 = (uint8_t) iv[12];
    this->iv.b13 = (uint8_t) iv[13];
    this->iv.b14 = (uint8_t) iv[14];
    this->iv.b15 = (uint8_t) iv[15];
}

/*
 * Retrieves initialization vector (IV)
 * from a hex value in a string
 */
void AesEncryption::setIvFromHex(string iv) throw (AesBadIvException)
{
    setIvFromString(hex2msg(iv));
}

/*
 * Retrieves initialization vector (IV)
 * from an array of 8 bit values
 */
void AesEncryption::setIvFromArray(const uint8_t iv[])
{
    this->iv.b0 = iv[0];
    this->iv.b1 = iv[1];
    this->iv.b2 = iv[2];
    this->iv.b3 = iv[3];
    this->iv.b4 = iv[4];
    this->iv.b5 = iv[5];
    this->iv.b6 = iv[6];
    this->iv.b7 = iv[7];
    this->iv.b8 = iv[8];
    this->iv.b9 = iv[9];
    this->iv.b10 = iv[10];
    this->iv.b11 = iv[11];
    this->iv.b12 = iv[12];
    this->iv.b13 = iv[13];
    this->iv.b14 = iv[14];
    this->iv.b15 = iv[15];
}

/*
 * Retrieves initialization vector (IV)
 * from an array of 32 bit values
 */
void AesEncryption::setIvFromArray(const uint32_t iv[])
{
    for(int n = 0; n < 4; n++)
        this->iv.w[n] = iv[n];
}

/*
 * Return AES key as a hexadecimal value in a string object
 */
string AesEncryption::getKeyAsHexString()
{
    return keyArr2Hex(knum);
}

/*
 * Return expanded AES key as a hexadecimal value in a string object
 */
string AesEncryption::getExpandedKeyAsHexString()
{
    return keyArr2Hex((rnum + 1) * 4);
}

/*
 * Convert key array to hexadecimal value and return it as a string object
 */
string AesEncryption::keyArr2Hex(int max)
{
    string s;
    for(int n = 0; n < max; n++) {
        s += charBase[(key[n].b0 & 0xF0) >> 4];
        s += charBase[(key[n].b0 & 0x0F)];
        s += charBase[(key[n].b1 & 0xF0) >> 4];
        s += charBase[(key[n].b1 & 0x0F)];
        s += charBase[(key[n].b2 & 0xF0) >> 4];
        s += charBase[(key[n].b2 & 0x0F)];
        s += charBase[(key[n].b3 & 0xF0) >> 4];
        s += charBase[(key[n].b3 & 0x0F)];
    }
    return s;
}

/*
 * Convert a hexadecimal value in a string object to a key array
 */
void AesEncryption::keyHex2Arr(const char *str) throw (AesBadKeyException)
{
    cout << str << endl;
    
    int l = strlen(str);
    if(l & 1 == 1)
        throw AesBadKeyException(AesBadKeyException::wrongStringLength);
    uint32_t x;
    for(int n = 0, m = 0; n < l; n++) {
        if(str[n] >= '0' && str[n] <= '9')
            x = (((uint8_t) str[n] - '0') << 4);
        else if(str[n] >= 'a' && str[n] <= 'f')
            x = (((uint8_t) str[n] - 'a' + 10) << 4);
        else if(str[n] >= 'A' && str[n] <= 'F')
            x = (((uint8_t) str[n] - 'A' + 10) << 4);
        else
            throw AesBadKeyException(AesBadKeyException::wrongCharacter);
        n++;
        if(str[n] >= '0' && str[n] <= '9')
            x += str[n] - '0';
        else if(str[n] >= 'a' && str[n] <= 'f')
            x += str[n] - 'a' + 10;
        else if(str[n] >= 'A' && str[n] <= 'F')
            x += str[n] - 'A' + 10;
        else
            throw AesBadKeyException(AesBadKeyException::wrongCharacter);
        int sh = ((n - 1) / 2) % 4;
        switch(sh) {
            case 0:
                key[m].w = x;
                break;
            case 3:
                x <<= sh * 8;
                key[m].w += x;
                m++;
                break;
            default:
                x <<= sh * 8;
                key[m].w += x;
        }
    }
    
    /*
    for (int n=0; n < l/8; n++) {
        cout << (int)key[n].b3 << " " << (int)key[n].b2 << " " << (int)key[n].b1 << " " << (int)key[n].b0 << endl;
    }*/
}

/*
 * Takes a hex value from a string and
 * converts it into a vector of 8 bit values
 */
vector<uint8_t> AesEncryption::hex2vector(string hex) throw (AesBadHexStringException)
{
    if(hex.length() & 1 == 1)
        throw AesBadKeyException(AesBadHexStringException::wrongStringLength);
    uint8_t x;
    vector<uint8_t> c(hex.length() / 2, 0);
    for(int n = 0, m = 0; n < hex.length(); n++, m++) {
        if(hex[n] >= '0' && hex[n] <= '9')
            x = (((uint8_t) hex[n] - '0') << 4);
        else if(hex[n] >= 'a' && hex[n] <= 'f')
            x = (((uint8_t) hex[n] - 'a' + 10) << 4);
        else if(hex[n] >= 'A' && hex[n] <= 'F')
            x = (((uint8_t) hex[n] - 'A' + 10) << 4);
        else
            throw AesBadHexStringException(AesBadHexStringException::wrongCharacter);
        n++;
        if(hex[n] >= '0' && hex[n] <= '9')
            x += hex[n] - '0';
        else if(hex[n] >= 'a' && hex[n] <= 'f')
            x += hex[n] - 'a' + 10;
        else if(hex[n] >= 'A' && hex[n] <= 'F')
            x += hex[n] - 'A' + 10;
        else
            throw AesBadHexStringException(AesBadHexStringException::wrongCharacter);
        c[m] = x;
    }
    return c;
}

/*
 * Takes a vector of 8 bit values and
 * converts them into a string representing a hex value
 */
string AesEncryption::vector2hex(vector<uint8_t> v)
{
    string s;
    uint8_t c;
    vector<uint8_t>::const_iterator iterator;
    for(iterator = v.begin(); iterator != v.end(); iterator++) {
        c = *iterator;
        s += charBase[(c & 0xF0) >> 4];
        s += charBase[(c & 0x0F)];
    }
    return s;
}

/*
 * Takes a string with hex values and
 * converts it into a string containing the characters
 * representing the hex values
 */
string AesEncryption::hex2msg(string hex) throw (AesBadHexStringException)
{
    if(hex.length() & 1 == 1)
        throw AesBadKeyException(AesBadHexStringException::wrongStringLength);
    uint8_t x;
    string msg;
    for(int n = 0; n < hex.length(); n++) {
        if(hex[n] >= '0' && hex[n] <= '9')
            x = (((uint8_t) hex[n] - '0') << 4);
        else if(hex[n] >= 'a' && hex[n] <= 'f')
            x = (((uint8_t) hex[n] - 'a' + 10) << 4);
        else if(hex[n] >= 'A' && hex[n] <= 'F')
            x = (((uint8_t) hex[n] - 'A' + 10) << 4);
        else
            throw AesBadHexStringException(AesBadHexStringException::wrongCharacter);
        n++;
        if(hex[n] >= '0' && hex[n] <= '9')
            x += hex[n] - '0';
        else if(hex[n] >= 'a' && hex[n] <= 'f')
            x += hex[n] - 'a' + 10;
        else if(hex[n] >= 'A' && hex[n] <= 'F')
            x += hex[n] - 'A' + 10;
        else
            throw AesBadHexStringException(AesBadHexStringException::wrongCharacter);
        msg.append(1, x);
    }
    return msg;
}

/*
 * Takes a message from a string and
 * converts it to a hex value and
 * provides it as a string
 */
string AesEncryption::msg2hex(string msg)
{
    string s;
    uint8_t c;
    for(unsigned long n = 0; n < msg.length(); n++) {
        c = (uint8_t) msg[n];
        s += charBase[(c & 0xF0) >> 4];
        s += charBase[(c & 0x0F)];
    }
    return s;
}

/*
 * ------------- *
 * AES Algorithm *
 * ------------- *
 */

/*
 * Encipher
 */
void AesEncryption::encipherState(AesEncryption::state_t& state)
{
    cout << "Before:" << endl;
    cout << (int)state.b0 << " " << (int)state.b1 << " " << (int)state.b2 << " " << (int)state.b3 << endl;
    cout << (int)state.b4 << " " << (int)state.b5 << " " << (int)state.b6 << " " << (int)state.b7 << endl;
    cout << (int)state.b8 << " " << (int)state.b9 << " " << (int)state.b10 << " " << (int)state.b11 << endl;
    cout << (int)state.b12 << " " << (int)state.b13 << " " << (int)state.b14 << " " << (int)state.b15 << endl;    
    
    addRoundKey(state, 0);
    
    for(int r = 1; r < rnum; r++) {
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, r);

    }
    subBytes(state);
    shiftRows(state);
    addRoundKey(state, rnum);
    
    cout << "After:" << endl;
    cout << (int)state.b0 << " " << (int)state.b1 << " " << (int)state.b2 << " " << (int)state.b3 << endl;
    cout << (int)state.b4 << " " << (int)state.b5 << " " << (int)state.b6 << " " << (int)state.b7 << endl;
    cout << (int)state.b8 << " " << (int)state.b9 << " " << (int)state.b10 << " " << (int)state.b11 << endl;
    cout << (int)state.b12 << " " << (int)state.b13 << " " << (int)state.b14 << " " << (int)state.b15 << endl;
}

/*
 * Decipher
 */
void AesEncryption::decipherState(AesEncryption::state_t& state)
{
cout << "Before:" << endl;
    cout << (int)state.b0 << " " << (int)state.b1 << " " << (int)state.b2 << " " << (int)state.b3 << endl;
    cout << (int)state.b4 << " " << (int)state.b5 << " " << (int)state.b6 << " " << (int)state.b7 << endl;
    cout << (int)state.b8 << " " << (int)state.b9 << " " << (int)state.b10 << " " << (int)state.b11 << endl;
    cout << (int)state.b12 << " " << (int)state.b13 << " " << (int)state.b14 << " " << (int)state.b15 << endl;       
    
    addRoundKey(state, rnum);
    for(int r = rnum - 1; r > 0; r--) {
        invShiftRows(state);
        invSubBytes(state);
        addRoundKey(state, r);
        invMixColumns(state);
    }
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, 0);
    
cout << "After:" << endl;
    cout << (int)state.b0 << " " << (int)state.b1 << " " << (int)state.b2 << " " << (int)state.b3 << endl;
    cout << (int)state.b4 << " " << (int)state.b5 << " " << (int)state.b6 << " " << (int)state.b7 << endl;
    cout << (int)state.b8 << " " << (int)state.b9 << " " << (int)state.b10 << " " << (int)state.b11 << endl;
    cout << (int)state.b12 << " " << (int)state.b13 << " " << (int)state.b14 << " " << (int)state.b15 << endl;    
}

/*
 * Key expansion
 */

void AesEncryption::expandKey()
{  
    AesEncryption::word32_t tmp;
    for(int i = knum; i < (rnum + 1) * 4; i++) {
        tmp.w = key[i - 1].w;
        //cout << (int)tmp.b3 << " " << (int)tmp.b2 << " " << (int)tmp.b1 << " " << (int)tmp.b0 << endl;
        //cout << (uint32_t)tmp.w << endl;
        
        if(i % knum == 0) {
            
            //cout << "PreShift: " << tmp.w << endl;
            
            tmp.w = (tmp.w << 24) | (tmp.w >> 8);
            
            //cout << "Shift: " << tmp.w << endl;
            
            tmp.b0 = subByte(tmp.b0);
            tmp.b1 = subByte(tmp.b1);
            tmp.b2 = subByte(tmp.b2);
            tmp.b3 = subByte(tmp.b3);
            tmp.w ^= rcon[i / knum - 1];
            //cout << "in" << endl;
        } else if(knum > 6 && i % knum == 4) {
            tmp.b0 = subByte(tmp.b0);
            tmp.b1 = subByte(tmp.b1);
            tmp.b2 = subByte(tmp.b2);
            tmp.b3 = subByte(tmp.b3);
            //cout << "out" << endl;
        }
        key[i].w = key[i - knum].w ^ tmp.w;
        
        //cout << i << ": " << (int)key[i].b3 << " " << (int)key[i].b2 << " " << (int)key[i].b1 << " " << (int)key[i].b0 << endl;
    }
}

/*
 * Methods implementing encryption
 */

void AesEncryption::subBytes(AesEncryption::state_t& state)
{
    for(int n = 0; n < 16; n++)
        state.b[n] = subByte(state.b[n]);
}

void AesEncryption::shiftRows(AesEncryption::state_t& state)
{
    uint8_t tmp;
    // row 1
    // no shifting necessary
    // row 2
    tmp = state.b1;
    state.b1 = state.b5;
    state.b5 = state.b9;
    state.b9 = state.b13;
    state.b13 = tmp;
    // row 3
    tmp = state.b2;
    state.b2 = state.b10;
    state.b10 = tmp;
    tmp = state.b6;
    state.b6 = state.b14;
    state.b14 = tmp;
    // row 4
    tmp = state.b3;
    state.b3 = state.b15;
    state.b15 = state.b11;
    state.b11 = state.b7;
    state.b7 = tmp;
}

void AesEncryption::mixColumn(AesEncryption::word32_t& column)
{
    uint8_t t0, t1, t2, t3;
    t0 = column.b0;
    t1 = column.b1;
    t2 = column.b2;
    t3 = column.b3;
    column.b0 = gmul(t0, 2) ^ gmul(t1, 3) ^ t2 ^ t3;
    column.b1 = t0 ^ gmul(t1, 2) ^ gmul(t2, 3) ^ t3;
    column.b2 = t0 ^ t1 ^ gmul(t2, 2) ^ gmul(t3, 3);
    column.b3 = gmul(t0, 3) ^ t1 ^ t2 ^ gmul(t3, 2);
}

void AesEncryption::mixColumns(AesEncryption::state_t& state)
{
    for(uint8_t n = 0; n < 4; n++)
        mixColumn((AesEncryption::word32_t&)(state.w[n]));
}

/*
 * Methods implementing decryption
 */

void AesEncryption::invSubBytes(AesEncryption::state_t& state)
{
    for(int n = 0; n < 16; n++)
        state.b[n] = invSubByte(state.b[n]);
}

void AesEncryption::invShiftRows(AesEncryption::state_t& state)
{
    uint8_t tmp;
    //row 1
    // no shifting necessary
    // row 2
    tmp = state.b1;
    state.b1 = state.b13;
    state.b13 = state.b9;
    state.b9 = state.b5;
    state.b5 = tmp;
    // row 3
    tmp = state.b2;
    state.b2 = state.b10;
    state.b10 = tmp;
    tmp = state.b6;
    state.b6 = state.b14;
    state.b14 = tmp;
    // row 4
    tmp = state.b3;
    state.b3 = state.b7;
    state.b7 = state.b11;
    state.b11 = state.b15;
    state.b15 = tmp;
}

void AesEncryption::invMixColumn(AesEncryption::word32_t& column)
{
    uint8_t t0, t1, t2, t3;
    t0 = column.b0;
    t1 = column.b1;
    t2 = column.b2;
    t3 = column.b3;
    column.b0 = gmul(t0, 0x0e) ^ gmul(t1, 0x0b) ^ gmul(t2, 0x0d) ^ gmul(t3, 0x09);
    column.b1 = gmul(t0, 0x09) ^ gmul(t1, 0x0e) ^ gmul(t2, 0x0b) ^ gmul(t3, 0x0d);
    column.b2 = gmul(t0, 0x0d) ^ gmul(t1, 0x09) ^ gmul(t2, 0x0e) ^ gmul(t3, 0x0b);
    column.b3 = gmul(t0, 0x0b) ^ gmul(t1, 0x0d) ^ gmul(t2, 0x09) ^ gmul(t3, 0x0e);
}

void AesEncryption::invMixColumns(AesEncryption::state_t& state)
{
    for(uint8_t n = 0; n < 4; n++)
        invMixColumn((AesEncryption::word32_t&)(state.w[n]));
}

/*
 * Methods for both modes
 */

void AesEncryption::addRoundKey(AesEncryption::state_t& state, unsigned round)
{
    state.w[0] ^= key[round * 4].w;
    state.w[1] ^= key[round * 4 + 1].w;
    state.w[2] ^= key[round * 4 + 2].w;
    state.w[3] ^= key[round * 4 + 3].w;
}

/*
 * Methods implementing operations in GF(256)
 */

/*
 * Multiplication in GF(256)
 * r = p * q
 */
uint8_t AesEncryption::gmul(uint8_t p, uint8_t q)
{
    uint8_t r = 0;
    for(uint8_t i = 0; i < 8; i++) {
        if(q & 0x01)
            r ^= p;
        if(p & 0x80) {
            p <<= 1;
            p ^= 0x1b;
        } else
            p <<= 1;
        q >>= 1;
    }
    return r;
}

/*
 ****************************
 * Class AesException *
 ****************************
 */

/*
 * ================= *
 * Static attributes *
 * ================= *
 */

const char *AesException::whatMsg[3] = {
    "hex string has wrong length",
    "hex string contains wrong characters",
    "array has wrong number of elements"
};

/*
 * =========== *
 * Constructor *
 * =========== *
 */

AesException::AesException(AesBadKeyException::what_t wt) :
    whatType(wt)
{
}

/*
 * ======= *
 * Methods *
 * ======= *
 */

/*
 * Return what happend as string
 */
const char* AesException::what() const throw ()
{
    return whatMsg[whatType];
}

/*
 * Return what happend as enum type
 */
AesException::what_t AesException::getWhatType() const throw ()
{
    return whatType;
}

/*
 **********************************
 * Class AesBadKeyException *
 **********************************
 */

/*
 * =========== *
 * Constructor *
 * =========== *
 */

AesBadKeyException::AesBadKeyException(AesBadKeyException::what_t wt) :
    AesException(wt)
{
}

/*
 **********************************
 * Class AesBadHexStringException *
 **********************************
 */

/*
 * =========== *
 * Constructor *
 * =========== *
 */

AesBadHexStringException::AesBadHexStringException(AesBadHexStringException::what_t wt) :
    AesException(wt)
{
}

/*
 **********************************
 * Class AesBadHexStringException *
 **********************************
 */

/*
 * =========== *
 * Constructor *
 * =========== *
 */

AesBadIvException::AesBadIvException(AesBadIvException::what_t wt) :
    AesException(wt)
{
}
