/*
 * Project: aes32bit - AES implementation for 32 bit platforms
 * File   : AesKeyConversionTest.h
 * Author : Oliver Mueller <oliver@cogito-ergo-sum.org>
 * Purpose: CppUnit test of AES key conversion in AesEncryption class.
 *
 * $Id: AesKeyConversionTest.h 16 2011-04-18 17:00:15Z oliver $
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

#ifndef AESKEYCONVERSIONTEST_H
#define	AESKEYCONVERSIONTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "aes.h"

class AesKeyConversionTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(AesKeyConversionTest);

    CPPUNIT_TEST(testAes128KeyFromString);
    CPPUNIT_TEST(testAes192KeyFromString);
    CPPUNIT_TEST(testAes256KeyFromString);
    CPPUNIT_TEST(testAes128KeyFromArray8Bit);
    CPPUNIT_TEST(testAes192KeyFromArray8Bit);
    CPPUNIT_TEST(testAes256KeyFromArray8Bit);
    CPPUNIT_TEST(testAes128KeyFromArray32Bit);
    CPPUNIT_TEST(testAes192KeyFromArray32Bit);
    CPPUNIT_TEST(testAes256KeyFromArray32Bit);
    CPPUNIT_TEST(testAesKeyWrongChar);
    CPPUNIT_TEST(testAesKeyWrongStrLen);
    CPPUNIT_TEST(testAesKeyWrongArr32Len);

    CPPUNIT_TEST_SUITE_END();

public:
    AesKeyConversionTest();
    virtual ~AesKeyConversionTest();
    void setUp();
    void tearDown();

protected:
    void printCompareValues(AesEncryption& aesObj, const char *aesStr);

private:
    void testAes128KeyFromString();
    void testAes192KeyFromString();
    void testAes256KeyFromString();
    void testAes128KeyFromArray8Bit();
    void testAes192KeyFromArray8Bit();
    void testAes256KeyFromArray8Bit();
    void testAes128KeyFromArray32Bit();
    void testAes192KeyFromArray32Bit();
    void testAes256KeyFromArray32Bit();
    void testAesKeyWrongChar();
    void testAesKeyWrongStrLen();
    void testAesKeyWrongArr32Len();

    static const char *aes128key;
    static const char *aes192key;
    static const char *aes256key;
    static const char *aesWrongCharKey;
    static const char *aesWrongLenKey;
    static uint8_t aes128key8array[16];
    static uint8_t aes192key8array[24];
    static uint8_t aes256key8array[32];
    static uint32_t aes128key32array[4];
    static uint32_t aes192key32array[6];
    static uint32_t aes256key32array[8];

};

#endif	/* AESKEYCONVERSIONTEST_H */

