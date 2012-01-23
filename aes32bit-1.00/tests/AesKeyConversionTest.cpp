/*
 * Project: aes32bit - AES implementation for 32 bit platforms
 * File   : AesKeyConversionTest.cpp
 * Author : Oliver Mueller <oliver@cogito-ergo-sum.org>
 * Purpose: CppUnit test of AES key conversion in AesEncryption class.
 *
 * $Id: AesKeyConversionTest.cpp 17 2011-04-18 19:48:19Z oliver $
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

#include "AesKeyConversionTest.h"

const char *AesKeyConversionTest::aes128key = "0123456789abcdefabf7158809cf4f3c";
const char *AesKeyConversionTest::aes192key = "0123456789abcdefc810f32b809079e562f8ead2522c6b7b";
const char *AesKeyConversionTest::aes256key = "0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4";
const char *AesKeyConversionTest::aesWrongCharKey = "603deb1015za71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";
const char *AesKeyConversionTest::aesWrongLenKey = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff";
uint8_t AesKeyConversionTest::aes128key8array[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
uint8_t AesKeyConversionTest::aes192key8array[24] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xc8, 0x10, 0xf3, 0x2b, 0x80, 0x90, 0x79, 0xe5, 0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b};
uint8_t AesKeyConversionTest::aes256key8array[32] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4};
uint32_t AesKeyConversionTest::aes128key32array[4] = {0x67452301, 0xefcdab89, 0x8815f7ab, 0x3c4fcf09};
uint32_t AesKeyConversionTest::aes192key32array[6] = {0x67452301, 0xefcdab89, 0x2bf310c8, 0xe5799080, 0xd2eaf862, 0x7b6b2c52};
uint32_t AesKeyConversionTest::aes256key32array[8] = {0x67452301, 0xefcdab89, 0xf0ae732b, 0x81777d85, 0x072c351f, 0xd708613b, 0xa310982d, 0xf4df1409};

CPPUNIT_TEST_SUITE_REGISTRATION(AesKeyConversionTest);

AesKeyConversionTest::AesKeyConversionTest()
{
}

AesKeyConversionTest::~AesKeyConversionTest()
{
}

void AesKeyConversionTest::setUp()
{
}

void AesKeyConversionTest::tearDown()
{
}

void AesKeyConversionTest::printCompareValues(AesEncryption& aesObj, const char *aesStr)
{
    cerr << "Original : " << aesStr << endl <<
            "Converted: " << aesObj.getKeyAsHexString() << endl << endl;
}

void AesKeyConversionTest::testAes128KeyFromString()
{
    cerr << "Test: aes128KeyFromString" << endl;
    try {
        AesEncryption aes128(aes128key);
        printCompareValues(aes128, aes128key);
        string keyStr = aes128.getKeyAsHexString();
        CPPUNIT_ASSERT(keyStr.compare(aes128key) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesKeyConversionTest::testAes192KeyFromString()
{
    cerr << "Test: aes192KeyFromString" << endl;
    try {
        AesEncryption aes192(aes192key);
        printCompareValues(aes192, aes192key);
        CPPUNIT_ASSERT(aes192.getKeyAsHexString().compare(aes192key) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesKeyConversionTest::testAes256KeyFromString()
{
    cerr << "Test: aes256KeyFromString" << endl;
    try {
        AesEncryption aes256(aes256key);
        printCompareValues(aes256, aes256key);
        CPPUNIT_ASSERT(aes256.getKeyAsHexString().compare(aes256key) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesKeyConversionTest::testAes128KeyFromArray8Bit()
{
    cerr << "Test: aes128KeyFromArray8Bit" << endl;
    try {
        AesEncryption aes128(aes128key8array, 16);
        printCompareValues(aes128, aes128key);
        CPPUNIT_ASSERT(aes128.getKeyAsHexString().compare(aes128key) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesKeyConversionTest::testAes192KeyFromArray8Bit()
{
    cerr << "Test: aes192KeyFromArray8Bit" << endl;
    try {
        AesEncryption aes192(aes192key8array, 24);
        printCompareValues(aes192, aes192key);
        CPPUNIT_ASSERT(aes192.getKeyAsHexString().compare(aes192key) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesKeyConversionTest::testAes256KeyFromArray8Bit()
{
    cerr << "Test: aes256KeyFromArray8Bit" << endl;
    try {
        AesEncryption aes256(aes256key8array, 32);
        printCompareValues(aes256, aes256key);
        CPPUNIT_ASSERT(aes256.getKeyAsHexString().compare(aes256key) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesKeyConversionTest::testAes128KeyFromArray32Bit()
{
    cerr << "Test: aes128KeyFromArray32Bit" << endl;
    try {
        AesEncryption aes128(aes128key32array, 4);
        printCompareValues(aes128, aes128key);
        CPPUNIT_ASSERT(aes128.getKeyAsHexString().compare(aes128key) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesKeyConversionTest::testAes192KeyFromArray32Bit()
{
    cerr << "Test: aes192KeyFromArray32Bit" << endl;
    try {
        AesEncryption aes192(aes192key32array, 6);
        printCompareValues(aes192, aes192key);
        CPPUNIT_ASSERT(aes192.getKeyAsHexString().compare(aes192key) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesKeyConversionTest::testAes256KeyFromArray32Bit()
{
    cerr << "Test: aes256KeyFromArray32Bit" << endl;
    try {
        AesEncryption aes256(aes256key32array, 8);
        printCompareValues(aes256, aes256key);
        CPPUNIT_ASSERT(aes256.getKeyAsHexString().compare(aes256key) == 0);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesKeyConversionTest::testAesKeyWrongChar()
{
    cerr << "Test: aesKeyWrongChar" << endl;
    try {
        AesEncryption aes(aesWrongCharKey);
        printCompareValues(aes, aesWrongCharKey);
        CPPUNIT_ASSERT(false);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(e.getWhatType() == AesBadKeyException::wrongCharacter);
    }
}

void AesKeyConversionTest::testAesKeyWrongStrLen()
{
    cerr << "Test: aesKeyWrongStrLen" << endl;
    try {
        AesEncryption aes(aesWrongLenKey);
        printCompareValues(aes, aesWrongLenKey);
        CPPUNIT_ASSERT(false);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(e.getWhatType() == AesBadKeyException::wrongStringLength);
    }
}

void AesKeyConversionTest::testAesKeyWrongArr32Len()
{
    cerr << "Test: aesKeyWrongArr32Len" << endl;
    try {
        AesEncryption aes256(aes256key32array, 7);
        printCompareValues(aes256, aes256key);
        CPPUNIT_ASSERT(false);
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(e.getWhatType() == AesBadKeyException::wrongArrayLength);
    }
}
