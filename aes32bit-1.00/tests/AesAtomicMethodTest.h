/*
 * Project: aes32bit - AES implementation for 32 bit platforms
 * File   : AesAtomicMethodTest.h
 * Author : Oliver Mueller <oliver@cogito-ergo-sum.org>
 * Purpose: CppUnit test of AES atomic methods of AesEncryption class.
 *
 * $Id: AesAtomicMethodTest.h 62 2011-06-17 00:22:10Z oliver $
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

#ifndef AESATOMICMETHODTEST_H
#define	AESATOMICMETHODTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "aes.h"

class AesTestHelper : public AesEncryption
{
public:
    AesTestHelper(const char* keystring) throw (AesBadKeyException);

    uint8_t helpSubByte(uint8_t x);
    void helpSubBytes(AesEncryption::state_t& state);
    uint8_t helpInvSubByte(uint8_t x);
    void helpInvSubBytes(AesEncryption::state_t& state);
    void helpShiftRows(AesEncryption::state_t& state);
    void helpInvShiftRows(AesEncryption::state_t& state);
    void helpMixColumns(AesEncryption::state_t& state);
    void helpInvMixColumns(AesEncryption::state_t& state);
    void helpAddRoundKey(AesEncryption::state_t& state, AesEncryption::word32_t *rkey);

    bool compareWithSbox(uint8_t a[]);
    bool compareWithInvSbox(uint8_t a[]);
};

class AesAtomicMethodTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(AesAtomicMethodTest);

    CPPUNIT_TEST(testSubByte);
    CPPUNIT_TEST(testInvSubByte);
    CPPUNIT_TEST(testSubBytes);
    CPPUNIT_TEST(testInvSubBytes);
    CPPUNIT_TEST(testShiftRows);
    CPPUNIT_TEST(testInvShiftRows);
    CPPUNIT_TEST(testMixColumns);
    CPPUNIT_TEST(testInvMixColumns);
    CPPUNIT_TEST(testAddRoundKey);
    CPPUNIT_TEST(testKeyExpansion);

    CPPUNIT_TEST_SUITE_END();

public:
    AesAtomicMethodTest();
    virtual ~AesAtomicMethodTest();
    void setUp();
    void tearDown();

private:
    static const uint8_t ref[46][16];
    
    void testSubByte();
    void testInvSubByte();
    void testSubBytes();
    void testInvSubBytes();
    void testShiftRows();
    void testInvShiftRows();
    void testMixColumns();
    void testInvMixColumns();
    void testAddRoundKey();
    void testKeyExpansion();
};

#endif	/* AESATOMICMETHODTEST_H */

