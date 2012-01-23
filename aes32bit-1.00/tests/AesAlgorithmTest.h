/*
 * Project: aes32bit - AES implementation for 32 bit platforms
 * File   : AesAlgorithmTest.h
 * Author : Oliver Mueller <oliver@cogito-ergo-sum.org>
 * Purpose: CppUnit test of AES algorithm in class AesEncryption.
 *
 * $Id: AesAlgorithmTest.h 21 2011-04-19 19:43:36Z oliver $
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

#ifndef AESALGORITHMTEST_H
#define	AESALGORITHMTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "aes.h"

class AesAlgorithmTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(AesAlgorithmTest);

    CPPUNIT_TEST(testKeyExpansion128);
    CPPUNIT_TEST(testKeyExpansion192);
    CPPUNIT_TEST(testKeyExpansion256);
    CPPUNIT_TEST(testSimple128);
    CPPUNIT_TEST(testSimple192);
    CPPUNIT_TEST(testSimple256);
    CPPUNIT_TEST(testKat);

    CPPUNIT_TEST_SUITE_END();

public:
    AesAlgorithmTest();
    virtual ~AesAlgorithmTest();
    void setUp();
    void tearDown();

protected:
    struct KatVector
    {
        bool encipher;
        const char *title;
        uint32_t count;
        AesEncryption::CipherMode mode;
        const char *key;
        const char *plain;
        const char *cipher;
        const char *iv;
    };

    static const AesAlgorithmTest::KatVector kat[];

private:
    void testKeyExpansion128();
    void testKeyExpansion192();
    void testKeyExpansion256();
    void testSimple128();
    void testSimple192();
    void testSimple256();
    void testKat();

    static const char charBase[16];
    static const uint8_t aes128expKey[176];
    static const uint8_t aes192expKey[208];
    static const uint8_t aes256expKey[240];
    static const char *aes128key;
    static const char *aes192key;
    static const char *aes256key;
};

#endif	/* AESALGORITHMTEST_H */

