/*
 * Project: aes32bit - AES implementation for 32 bit platforms
 * File   : AesAlgorithmTest.cpp
 * Author : Oliver Mueller <oliver@cogito-ergo-sum.org>
 * Purpose: CppUnit test of AES algorithm in class AesEncryption.
 *
 * $Id: AesAlgorithmTest.cpp 35 2011-04-29 17:06:03Z oliver $
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

#include <iostream>
#include <iomanip>
#include <cstring>

#include "AesAlgorithmTest.h"

const char AesAlgorithmTest::charBase[16]
        = {'0', '1', '2', '3', '4', '5', '6', '7',
           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

const uint8_t AesAlgorithmTest::aes128expKey[176]
        = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
           0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C,
           0xA0, 0xFA, 0xFE, 0x17, 0x88, 0x54, 0x2C, 0xB1,
           0x23, 0xA3, 0x39, 0x39, 0x2A, 0x6C, 0x76, 0x05,
           0xF2, 0xC2, 0x95, 0xF2, 0x7A, 0x96, 0xB9, 0x43,
           0x59, 0x35, 0x80, 0x7A, 0x73, 0x59, 0xF6, 0x7F,
           0x3D, 0x80, 0x47, 0x7D, 0x47, 0x16, 0xFE, 0x3E,
           0x1E, 0x23, 0x7E, 0x44, 0x6D, 0x7A, 0x88, 0x3B,
           0xEF, 0x44, 0xA5, 0x41, 0xA8, 0x52, 0x5B, 0x7F,
           0xB6, 0x71, 0x25, 0x3B, 0xDB, 0x0B, 0xAD, 0x00,
           0xD4, 0xD1, 0xC6, 0xF8, 0x7C, 0x83, 0x9D, 0x87,
           0xCA, 0xF2, 0xB8, 0xBC, 0x11, 0xF9, 0x15, 0xBC,
           0x6D, 0x88, 0xA3, 0x7A, 0x11, 0x0B, 0x3E, 0xFD,
           0xDB, 0xF9, 0x86, 0x41, 0xCA, 0x00, 0x93, 0xFD,
           0x4E, 0x54, 0xF7, 0x0E, 0x5F, 0x5F, 0xC9, 0xF3,
           0x84, 0xA6, 0x4F, 0xB2, 0x4E, 0xA6, 0xDC, 0x4F,
           0xEA, 0xD2, 0x73, 0x21, 0xB5, 0x8D, 0xBA, 0xD2,
           0x31, 0x2B, 0xF5, 0x60, 0x7F, 0x8D, 0x29, 0x2F,
           0xAC, 0x77, 0x66, 0xF3, 0x19, 0xFA, 0xDC, 0x21,
           0x28, 0xD1, 0x29, 0x41, 0x57, 0x5C, 0x00, 0x6E,
           0xD0, 0x14, 0xF9, 0xA8, 0xC9, 0xEE, 0x25, 0x89,
           0xE1, 0x3F, 0x0C, 0xC8, 0xB6, 0x63, 0x0C, 0xA6};

const uint8_t AesAlgorithmTest::aes192expKey[208]
        = {0x8E, 0x73, 0xB0, 0xF7, 0xDA, 0x0E, 0x64, 0x52,
           0xC8, 0x10, 0xF3, 0x2B, 0x80, 0x90, 0x79, 0xE5,
           0x62, 0xF8, 0xEA, 0xD2, 0x52, 0x2C, 0x6B, 0x7B,
           0xFE, 0x0C, 0x91, 0xF7, 0x24, 0x02, 0xF5, 0xA5,
           0xEC, 0x12, 0x06, 0x8E, 0x6C, 0x82, 0x7F, 0x6B,
           0x0E, 0x7A, 0x95, 0xB9, 0x5C, 0x56, 0xFE, 0xC2,
           0x4D, 0xB7, 0xB4, 0xBD, 0x69, 0xB5, 0x41, 0x18,
           0x85, 0xA7, 0x47, 0x96, 0xE9, 0x25, 0x38, 0xFD,
           0xE7, 0x5F, 0xAD, 0x44, 0xBB, 0x09, 0x53, 0x86,
           0x48, 0x5A, 0xF0, 0x57, 0x21, 0xEF, 0xB1, 0x4F,
           0xA4, 0x48, 0xF6, 0xD9, 0x4D, 0x6D, 0xCE, 0x24,
           0xAA, 0x32, 0x63, 0x60, 0x11, 0x3B, 0x30, 0xE6,
           0xA2, 0x5E, 0x7E, 0xD5, 0x83, 0xB1, 0xCF, 0x9A,
           0x27, 0xF9, 0x39, 0x43, 0x6A, 0x94, 0xF7, 0x67,
           0xC0, 0xA6, 0x94, 0x07, 0xD1, 0x9D, 0xA4, 0xE1,
           0xEC, 0x17, 0x86, 0xEB, 0x6F, 0xA6, 0x49, 0x71,
           0x48, 0x5F, 0x70, 0x32, 0x22, 0xCB, 0x87, 0x55,
           0xE2, 0x6D, 0x13, 0x52, 0x33, 0xF0, 0xB7, 0xB3,
           0x40, 0xBE, 0xEB, 0x28, 0x2F, 0x18, 0xA2, 0x59,
           0x67, 0x47, 0xD2, 0x6B, 0x45, 0x8C, 0x55, 0x3E,
           0xA7, 0xE1, 0x46, 0x6C, 0x94, 0x11, 0xF1, 0xDF,
           0x82, 0x1F, 0x75, 0x0A, 0xAD, 0x07, 0xD7, 0x53,
           0xCA, 0x40, 0x05, 0x38, 0x8F, 0xCC, 0x50, 0x06,
           0x28, 0x2D, 0x16, 0x6A, 0xBC, 0x3C, 0xE7, 0xB5,
           0xE9, 0x8B, 0xA0, 0x6F, 0x44, 0x8C, 0x77, 0x3C,
           0x8E, 0xCC, 0x72, 0x04, 0x01, 0x00, 0x22, 0x02};

const uint8_t AesAlgorithmTest::aes256expKey[240]
        = {0x60, 0x3D, 0xEB, 0x10, 0x15, 0xCA, 0x71, 0xBE,
           0x2B, 0x73, 0xAE, 0xF0, 0x85, 0x7D, 0x77, 0x81,
           0x1F, 0x35, 0x2C, 0x07, 0x3B, 0x61, 0x08, 0xD7,
           0x2D, 0x98, 0x10, 0xA3, 0x09, 0x14, 0xDF, 0xF4,
           0x9B, 0xA3, 0x54, 0x11, 0x8E, 0x69, 0x25, 0xAF,
           0xA5, 0x1A, 0x8B, 0x5F, 0x20, 0x67, 0xFC, 0xDE,
           0xA8, 0xB0, 0x9C, 0x1A, 0x93, 0xD1, 0x94, 0xCD,
           0xBE, 0x49, 0x84, 0x6E, 0xB7, 0x5D, 0x5B, 0x9A,
           0xD5, 0x9A, 0xEC, 0xB8, 0x5B, 0xF3, 0xC9, 0x17,
           0xFE, 0xE9, 0x42, 0x48, 0xDE, 0x8E, 0xBE, 0x96,
           0xB5, 0xA9, 0x32, 0x8A, 0x26, 0x78, 0xA6, 0x47,
           0x98, 0x31, 0x22, 0x29, 0x2F, 0x6C, 0x79, 0xB3,
           0x81, 0x2C, 0x81, 0xAD, 0xDA, 0xDF, 0x48, 0xBA,
           0x24, 0x36, 0x0A, 0xF2, 0xFA, 0xB8, 0xB4, 0x64,
           0x98, 0xC5, 0xBF, 0xC9, 0xBE, 0xBD, 0x19, 0x8E,
           0x26, 0x8C, 0x3B, 0xA7, 0x09, 0xE0, 0x42, 0x14,
           0x68, 0x00, 0x7B, 0xAC, 0xB2, 0xDF, 0x33, 0x16,
           0x96, 0xE9, 0x39, 0xE4, 0x6C, 0x51, 0x8D, 0x80,
           0xC8, 0x14, 0xE2, 0x04, 0x76, 0xA9, 0xFB, 0x8A,
           0x50, 0x25, 0xC0, 0x2D, 0x59, 0xC5, 0x82, 0x39,
           0xDE, 0x13, 0x69, 0x67, 0x6C, 0xCC, 0x5A, 0x71,
           0xFA, 0x25, 0x63, 0x95, 0x96, 0x74, 0xEE, 0x15,
           0x58, 0x86, 0xCA, 0x5D, 0x2E, 0x2F, 0x31, 0xD7,
           0x7E, 0x0A, 0xF1, 0xFA, 0x27, 0xCF, 0x73, 0xC3,
           0x74, 0x9C, 0x47, 0xAB, 0x18, 0x50, 0x1D, 0xDA,
           0xE2, 0x75, 0x7E, 0x4F, 0x74, 0x01, 0x90, 0x5A,
           0xCA, 0xFA, 0xAA, 0xE3, 0xE4, 0xD5, 0x9B, 0x34,
           0x9A, 0xDF, 0x6A, 0xCE, 0xBD, 0x10, 0x19, 0x0D,
           0xFE, 0x48, 0x90, 0xD1, 0xE6, 0x18, 0x8D, 0x0B,
           0x04, 0x6D, 0xF3, 0x44, 0x70, 0x6C, 0x63, 0x1E};

const char *AesAlgorithmTest::aes128key = "2b7e151628aed2a6abf7158809cf4f3c";
const char *AesAlgorithmTest::aes192key = "8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b";
const char *AesAlgorithmTest::aes256key = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";

CPPUNIT_TEST_SUITE_REGISTRATION(AesAlgorithmTest);

AesAlgorithmTest::AesAlgorithmTest()
{
}

AesAlgorithmTest::~AesAlgorithmTest()
{
}

void AesAlgorithmTest::setUp()
{
}

void AesAlgorithmTest::tearDown()
{
}

void AesAlgorithmTest::testKeyExpansion128()
{
    cerr << "Test: testKeyExpansion128()" << endl;
    try {
        AesEncryption aes(aes128key);
        string s;
        for(int n = 0; n < 176; n++) {
            s += charBase[(aes128expKey[n] & 0xF0) >> 4];
            s += charBase[(aes128expKey[n] & 0x0F)];
        }
        cerr << "Original: " << s << endl <<
                "Expanded: " << aes.getExpandedKeyAsHexString() << endl << endl;
        CPPUNIT_ASSERT(aes.getExpandedKeyAsHexString().compare(s) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAlgorithmTest::testKeyExpansion192()
{
    cerr << "Test: testKeyExpansion192()" << endl;
    try {
        AesEncryption aes(aes192key);
        string s;
        for(int n = 0; n < 208; n++) {
            s += charBase[(aes192expKey[n] & 0xF0) >> 4];
            s += charBase[(aes192expKey[n] & 0x0F)];
        }
        cerr << "Original: " << s << endl <<
                "Expanded: " << aes.getExpandedKeyAsHexString() << endl << endl;
        CPPUNIT_ASSERT(aes.getExpandedKeyAsHexString().compare(s) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAlgorithmTest::testKeyExpansion256()
{
    cerr << "Test: testKeyExpansion256()" << endl;
    try {
        AesEncryption aes(aes256key);
        string s;
        for(int n = 0; n < 240; n++) {
            s += charBase[(aes256expKey[n] & 0xF0) >> 4];
            s += charBase[(aes256expKey[n] & 0x0F)];
        }
        cerr << "Original: " << s << endl <<
                "Expanded: " << aes.getExpandedKeyAsHexString() << endl << endl;
        CPPUNIT_ASSERT(aes.getExpandedKeyAsHexString().compare(s) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAlgorithmTest::testSimple128()
{
    cerr << "Test: testSimple128()" << endl;
    try {
        AesEncryption aes(aes128key);
        string m("This is a little test message.");
        string iv("A part of this string will be used as IV.");
        AesEncryption::CipherMode modes[] = {AesEncryption::ECB,
                                             AesEncryption::CBC,
                                             AesEncryption::CFB,
                                             AesEncryption::OFB};
        for(int x = 0; x < 4; x++) {
            aes.setIvFromString(iv);
            vector<uint8_t> c = aes.encipher(m, modes[x]);
            aes.setIvFromString(iv);
            string m_ = aes.decipher(c, modes[x]);
            cerr << "m      : " << m << endl <<
                    "d(e(m)): " << m_ << endl << endl;
            CPPUNIT_ASSERT(strcmp(m.c_str(), m_.c_str()) == 0);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAlgorithmTest::testSimple192()
{
    cerr << "Test: testSimple192()" << endl;
    try {
        AesEncryption aes(aes192key);
        string m("This is a little test message.");
        string iv("A part of this string will be used as IV.");
        AesEncryption::CipherMode modes[] = {AesEncryption::ECB,
                                             AesEncryption::CBC,
                                             AesEncryption::CFB,
                                             AesEncryption::OFB};
        for(int x = 0; x < 4; x++) {
            aes.setIvFromString(iv);
            vector<uint8_t> c = aes.encipher(m, modes[x]);
            aes.setIvFromString(iv);
            string m_ = aes.decipher(c, modes[x]);
            cerr << "m      : " << m << endl <<
                    "d(e(m)): " << m_ << endl << endl;
            CPPUNIT_ASSERT(strcmp(m.c_str(), m_.c_str()) == 0);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAlgorithmTest::testSimple256()
{
    cerr << "Test: testSimple256()" << endl;
    try {
        AesEncryption aes(aes256key);
        string m("This is a little test message.");
        string iv("A part of this string will be used as IV.");
        AesEncryption::CipherMode modes[] = {AesEncryption::ECB,
                                             AesEncryption::CBC,
                                             AesEncryption::CFB,
                                             AesEncryption::OFB};
        for(int x = 0; x < 4; x++) {
            aes.setIvFromString(iv);
            vector<uint8_t> c = aes.encipher(m, modes[x]);
            aes.setIvFromString(iv);
            string m_ = aes.decipher(c, modes[x]);
            cerr << "m      : " << m << endl <<
                    "d(e(m)): " << m_ << endl << endl;
            CPPUNIT_ASSERT(strcmp(m.c_str(), m_.c_str()) == 0);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}


void AesAlgorithmTest::testKat()
{
/*
    cerr << "Known Answer Test (KAT)" << endl;
    try {
        for(int n = 0; kat[n].count != 0xFFFF; n++) {
            AesEncryption aes(kat[n].key);
            cerr << kat[n].title << "[" <<
                    setw(3) << right << setfill('0') << kat[n].count <<
                    "]" << endl;
            if(kat[n].mode != AesEncryption::ECB)
                aes.setIvFromHex(kat[n].iv);
            if(kat[n].encipher) {
                string c = aes.encipherHexToHex(kat[n].plain, kat[n].mode);
                cerr << "Original c: " << kat[n].cipher << endl <<
                        "Produced c: " << c << endl;
                CPPUNIT_ASSERT(c.compare(kat[n].cipher) == 0);
            } else {
                string m = aes.decipherHexToHex(kat[n].cipher, kat[n].mode);
                cerr << "Original m: " << kat[n].plain << endl <<
                        "Produced m: " << m << endl;
                CPPUNIT_ASSERT(m.compare(kat[n].plain) == 0);
            }
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }*/
}
