/*
 * Project: aes32bit - AES implementation for 32 bit platforms
 * File   : AesAtomicMethodTest.cpp
 * Author : Oliver Mueller <oliver@cogito-ergo-sum.org>
 * Purpose: CppUnit test of AES atomic methods of AesEncryption class.
 *
 * $Id: AesAtomicMethodTest.cpp 63 2011-06-17 18:10:28Z oliver $
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

#include "AesAtomicMethodTest.h"

using namespace std;

const uint8_t AesAtomicMethodTest::ref[46][16] = {
    {0x19, 0x3d, 0xe3, 0xbe, 0xa0, 0xf4, 0xe2, 0x2b, 0x9a, 0xc6, 0x8d, 0x2a, 0xe9, 0xf8, 0x48, 0x08},
    {0xd4, 0x27, 0x11, 0xae, 0xe0, 0xbf, 0x98, 0xf1, 0xb8, 0xb4, 0x5d, 0xe5, 0x1e, 0x41, 0x52, 0x30},
    {0xd4, 0xbf, 0x5d, 0x30, 0xe0, 0xb4, 0x52, 0xae, 0xb8, 0x41, 0x11, 0xf1, 0x1e, 0x27, 0x98, 0xe5},
    {0x04, 0x66, 0x81, 0xe5, 0xe0, 0xcb, 0x19, 0x9a, 0x48, 0xf8, 0xd3, 0x7a, 0x28, 0x06, 0x26, 0x4c},
    {0xa0, 0xfa, 0xfe, 0x17, 0x88, 0x54, 0x2c, 0xb1, 0x23, 0xa3, 0x39, 0x39, 0x2a, 0x6c, 0x76, 0x05},

    {0xa4, 0x9c, 0x7f, 0xf2, 0x68, 0x9f, 0x35, 0x2b, 0x6b, 0x5b, 0xea, 0x43, 0x02, 0x6a, 0x50, 0x49},
    {0x49, 0xde, 0xd2, 0x89, 0x45, 0xdb, 0x96, 0xf1, 0x7f, 0x39, 0x87, 0x1a, 0x77, 0x02, 0x53, 0x3b},
    {0x49, 0xdb, 0x87, 0x3b, 0x45, 0x39, 0x53, 0x89, 0x7f, 0x02, 0xd2, 0xf1, 0x77, 0xde, 0x96, 0x1a},
    {0x58, 0x4d, 0xca, 0xf1, 0x1b, 0x4b, 0x5a, 0xac, 0xdb, 0xe7, 0xca, 0xa8, 0x1b, 0x6b, 0xb0, 0xe5},
    {0xf2, 0xc2, 0x95, 0xf2, 0x7a, 0x96, 0xb9, 0x43, 0x59, 0x35, 0x80, 0x7a, 0x73, 0x59, 0xf6, 0x7f},

    {0xaa, 0x8f, 0x5f, 0x03, 0x61, 0xdd, 0xe3, 0xef, 0x82, 0xd2, 0x4a, 0xd2, 0x68, 0x32, 0x46, 0x9a},
    {0xac, 0x73, 0xcf, 0x7b, 0xef, 0xc1, 0x11, 0xdf, 0x13, 0xb5, 0xd6, 0xb5, 0x45, 0x23, 0x5a, 0xb8},
    {0xac, 0xc1, 0xd6, 0xb8, 0xef, 0xb5, 0x5a, 0x7b, 0x13, 0x23, 0xcf, 0xdf, 0x45, 0x73, 0x11, 0xb5},
    {0x75, 0xec, 0x09, 0x93, 0x20, 0x0b, 0x63, 0x33, 0x53, 0xc0, 0xcf, 0x7c, 0xbb, 0x25, 0xd0, 0xdc},
    {0x3d, 0x80, 0x47, 0x7d, 0x47, 0x16, 0xfe, 0x3e, 0x1e, 0x23, 0x7e, 0x44, 0x6d, 0x7a, 0x88, 0x3b},

    {0x48, 0x6c, 0x4e, 0xee, 0x67, 0x1d, 0x9d, 0x0d, 0x4d, 0xe3, 0xb1, 0x38, 0xd6, 0x5f, 0x58, 0xe7},
    {0x52, 0x50, 0x2f, 0x28, 0x85, 0xa4, 0x5e, 0xd7, 0xe3, 0x11, 0xc8, 0x07, 0xf6, 0xcf, 0x6a, 0x94},
    {0x52, 0xa4, 0xc8, 0x94, 0x85, 0x11, 0x6a, 0x28, 0xe3, 0xcf, 0x2f, 0xd7, 0xf6, 0x50, 0x5e, 0x07},
    {0x0f, 0xd6, 0xda, 0xa9, 0x60, 0x31, 0x38, 0xbf, 0x6f, 0xc0, 0x10, 0x6b, 0x5e, 0xb3, 0x13, 0x01},
    {0xef, 0x44, 0xa5, 0x41, 0xa8, 0x52, 0x5b, 0x7f, 0xb6, 0x71, 0x25, 0x3b, 0xdb, 0x0b, 0xad, 0x00},

    {0xe0, 0x92, 0x7f, 0xe8, 0xc8, 0x63, 0x63, 0xc0, 0xd9, 0xb1, 0x35, 0x50, 0x85, 0xb8, 0xbe, 0x01},
    {0xe1, 0x4f, 0xd2, 0x9b, 0xe8, 0xfb, 0xfb, 0xba, 0x35, 0xc8, 0x96, 0x53, 0x97, 0x6c, 0xae, 0x7c},
    {0xe1, 0xfb, 0x96, 0x7c, 0xe8, 0xc8, 0xae, 0x9b, 0x35, 0x6c, 0xd2, 0xba, 0x97, 0x4f, 0xfb, 0x53},
    {0x25, 0xd1, 0xa9, 0xad, 0xbd, 0x11, 0xd1, 0x68, 0xb6, 0x3a, 0x33, 0x8e, 0x4c, 0x4c, 0xc0, 0xb0},
    {0xd4, 0xd1, 0xc6, 0xf8, 0x7c, 0x83, 0x9d, 0x87, 0xca, 0xf2, 0xb8, 0xbc, 0x11, 0xf9, 0x15, 0xbc},

    {0xf1, 0x00, 0x6f, 0x55, 0xc1, 0x92, 0x4c, 0xef, 0x7c, 0xc8, 0x8b, 0x32, 0x5d, 0xb5, 0xd5, 0x0c},
    {0xa1, 0x63, 0xa8, 0xfc, 0x78, 0x4f, 0x29, 0xdf, 0x10, 0xe8, 0x3d, 0x23, 0x4c, 0xd5, 0x03, 0xfe},
    {0xa1, 0x4f, 0x3d, 0xfe, 0x78, 0xe8, 0x03, 0xfc, 0x10, 0xd5, 0xa8, 0xdf, 0x4c, 0x63, 0x29, 0x23},
    {0x4b, 0x86, 0x8d, 0x6d, 0x2c, 0x4a, 0x89, 0x80, 0x33, 0x9d, 0xf4, 0xe8, 0x37, 0xd2, 0x18, 0xd8},
    {0x6d, 0x88, 0xa3, 0x7a, 0x11, 0x0b, 0x3e, 0xfd, 0xdb, 0xf9, 0x86, 0x41, 0xca, 0x00, 0x93, 0xfd},

    {0x26, 0x0e, 0x2e, 0x17, 0x3d, 0x41, 0xb7, 0x7d, 0xe8, 0x64, 0x72, 0xa9, 0xfd, 0xd2, 0x8b, 0x25},
    {0xf7, 0xab, 0x31, 0xf0, 0x27, 0x83, 0xa9, 0xff, 0x9b, 0x43, 0x40, 0xd3, 0x54, 0xb5, 0x3d, 0x3f},
    {0xf7, 0x83, 0x40, 0x3f, 0x27, 0x43, 0x3d, 0xf0, 0x9b, 0xb5, 0x31, 0xff, 0x54, 0xab, 0xa9, 0xd3},
    {0x14, 0x15, 0xb5, 0xbf, 0x46, 0x16, 0x15, 0xec, 0x27, 0x46, 0x56, 0xd7, 0x34, 0x2a, 0xd8, 0x43},
    {0x4e, 0x54, 0xf7, 0x0e, 0x5f, 0x5f, 0xc9, 0xf3, 0x84, 0xa6, 0x4f, 0xb2, 0x4e, 0xa6, 0xdc, 0x4f},

    {0x5a, 0x41, 0x42, 0xb1, 0x19, 0x49, 0xdc, 0x1f, 0xa3, 0xe0, 0x19, 0x65, 0x7a, 0x8c, 0x04, 0x0c},
    {0xbe, 0x83, 0x2c, 0xc8, 0xd4, 0x3b, 0x86, 0xc0, 0x0a, 0xe1, 0xd4, 0x4d, 0xda, 0x64, 0xf2, 0xfe},
    {0xbe, 0x3b, 0xd4, 0xfe, 0xd4, 0xe1, 0xf2, 0xc8, 0x0a, 0x64, 0x2c, 0xc0, 0xda, 0x83, 0x86, 0x4d},
    {0x00, 0x51, 0x2f, 0xd1, 0xb1, 0xc8, 0x89, 0xff, 0x54, 0x76, 0x6d, 0xcd, 0xfa, 0x1b, 0x99, 0xea},
    {0xea, 0xd2, 0x73, 0x21, 0xb5, 0x8d, 0xba, 0xd2, 0x31, 0x2b, 0xf5, 0x60, 0x7f, 0x8d, 0x29, 0x2f},

    {0xea, 0x83, 0x5c, 0xf0, 0x04, 0x45, 0x33, 0x2d, 0x65, 0x5d, 0x98, 0xad, 0x85, 0x96, 0xb0, 0xc5},
    {0x87, 0xec, 0x4a, 0x8c, 0xf2, 0x6e, 0xc3, 0xd8, 0x4d, 0x4c, 0x46, 0x95, 0x97, 0x90, 0xe7, 0xa6},
    {0x87, 0x6e, 0x46, 0xa6, 0xf2, 0x4c, 0xe7, 0x8c, 0x4d, 0x90, 0x4a, 0xd8, 0x97, 0xec, 0xc3, 0x95},
    {0x47, 0x37, 0x94, 0xed, 0x40, 0xd4, 0xe4, 0xa5, 0xa3, 0x70, 0x3a, 0xa6, 0x4c, 0x9f, 0x42, 0xbc},
    {0xac, 0x77, 0x66, 0xf3, 0x19, 0xfa, 0xdc, 0x21, 0x28, 0xd1, 0x29, 0x41, 0x57, 0x5c, 0x00, 0x6e},

    {0xeb, 0x40, 0xf2, 0x1e, 0x59, 0x2e, 0x38, 0x84, 0x8b, 0xa1, 0x13, 0xe7, 0x1b, 0xc3, 0x42, 0xd2}
};

CPPUNIT_TEST_SUITE_REGISTRATION(AesAtomicMethodTest);

AesAtomicMethodTest::AesAtomicMethodTest()
{
}

AesAtomicMethodTest::~AesAtomicMethodTest()
{
}

void AesAtomicMethodTest::setUp()
{
}

void AesAtomicMethodTest::tearDown()
{
}

void AesAtomicMethodTest::testSubByte()
{
    cerr << "Test: testSubByte()" << endl;
    try {
        AesTestHelper aes("0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        uint8_t box[256];
        AesEncryption::state_t *state;
        for(unsigned n = 0; n < 256; n++)
            box[n] = n;
        for(unsigned n = 0; n < 256; n += 16) {
            state = (AesEncryption::state_t*) (&box[n]);
            aes.helpSubBytes(*state);
        }
        CPPUNIT_ASSERT(aes.compareWithSbox(box));
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAtomicMethodTest::testInvSubByte()
{
    cerr << "Test: testInvSubByte()" << endl;
    try {
        AesTestHelper aes("0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        uint8_t box[256];
        AesEncryption::state_t *state;
        for(unsigned n = 0; n < 256; n++)
            box[n] = n;
        for(unsigned n = 0; n < 256; n += 16) {
            state = (AesEncryption::state_t*) (&box[n]);
            aes.helpInvSubBytes(*state);
        }
        CPPUNIT_ASSERT(aes.compareWithInvSbox(box));
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAtomicMethodTest::testSubBytes()
{
    cerr << "Test: testSubBytes()" << endl;
    try {
        AesTestHelper aes("0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        AesEncryption::state_t state;
        for(unsigned n = 0; n < 45; n += 5) {
            state.b0 = ref[n][0];
            state.b1 = ref[n][1];
            state.b2 = ref[n][2];
            state.b3 = ref[n][3];
            state.b4 = ref[n][4];
            state.b5 = ref[n][5];
            state.b6 = ref[n][6];
            state.b7 = ref[n][7];
            state.b8 = ref[n][8];
            state.b9 = ref[n][9];
            state.b10 = ref[n][10];
            state.b11 = ref[n][11];
            state.b12 = ref[n][12];
            state.b13 = ref[n][13];
            state.b14 = ref[n][14];
            state.b15 = ref[n][15];
            aes.helpSubBytes(state);
            CPPUNIT_ASSERT(state.b0 == ref[n + 1][0]);
            CPPUNIT_ASSERT(state.b1 == ref[n + 1][1]);
            CPPUNIT_ASSERT(state.b2 == ref[n + 1][2]);
            CPPUNIT_ASSERT(state.b3 == ref[n + 1][3]);
            CPPUNIT_ASSERT(state.b4 == ref[n + 1][4]);
            CPPUNIT_ASSERT(state.b5 == ref[n + 1][5]);
            CPPUNIT_ASSERT(state.b6 == ref[n + 1][6]);
            CPPUNIT_ASSERT(state.b7 == ref[n + 1][7]);
            CPPUNIT_ASSERT(state.b8 == ref[n + 1][8]);
            CPPUNIT_ASSERT(state.b9 == ref[n + 1][9]);
            CPPUNIT_ASSERT(state.b10 == ref[n + 1][10]);
            CPPUNIT_ASSERT(state.b11 == ref[n + 1][11]);
            CPPUNIT_ASSERT(state.b12 == ref[n + 1][12]);
            CPPUNIT_ASSERT(state.b13 == ref[n + 1][13]);
            CPPUNIT_ASSERT(state.b14 == ref[n + 1][14]);
            CPPUNIT_ASSERT(state.b15 == ref[n + 1][15]);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAtomicMethodTest::testInvSubBytes()
{
    cerr << "Test: testInvSubBytes()" << endl;
    try {
        AesTestHelper aes("0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        AesEncryption::state_t state;
        for(unsigned n = 1; n < 45; n += 5) {
            state.b0 = ref[n][0];
            state.b1 = ref[n][1];
            state.b2 = ref[n][2];
            state.b3 = ref[n][3];
            state.b4 = ref[n][4];
            state.b5 = ref[n][5];
            state.b6 = ref[n][6];
            state.b7 = ref[n][7];
            state.b8 = ref[n][8];
            state.b9 = ref[n][9];
            state.b10 = ref[n][10];
            state.b11 = ref[n][11];
            state.b12 = ref[n][12];
            state.b13 = ref[n][13];
            state.b14 = ref[n][14];
            state.b15 = ref[n][15];
            aes.helpInvSubBytes(state);
            CPPUNIT_ASSERT(state.b0 == ref[n - 1][0]);
            CPPUNIT_ASSERT(state.b1 == ref[n - 1][1]);
            CPPUNIT_ASSERT(state.b2 == ref[n - 1][2]);
            CPPUNIT_ASSERT(state.b3 == ref[n - 1][3]);
            CPPUNIT_ASSERT(state.b4 == ref[n - 1][4]);
            CPPUNIT_ASSERT(state.b5 == ref[n - 1][5]);
            CPPUNIT_ASSERT(state.b6 == ref[n - 1][6]);
            CPPUNIT_ASSERT(state.b7 == ref[n - 1][7]);
            CPPUNIT_ASSERT(state.b8 == ref[n - 1][8]);
            CPPUNIT_ASSERT(state.b9 == ref[n - 1][9]);
            CPPUNIT_ASSERT(state.b10 == ref[n - 1][10]);
            CPPUNIT_ASSERT(state.b11 == ref[n - 1][11]);
            CPPUNIT_ASSERT(state.b12 == ref[n - 1][12]);
            CPPUNIT_ASSERT(state.b13 == ref[n - 1][13]);
            CPPUNIT_ASSERT(state.b14 == ref[n - 1][14]);
            CPPUNIT_ASSERT(state.b15 == ref[n - 1][15]);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAtomicMethodTest::testShiftRows()
{
    cerr << "Test: testShiftRows()" << endl;
    try {
        AesTestHelper aes("0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        AesEncryption::state_t state;
        for(unsigned n = 1; n < 45; n += 5) {
            state.b0 = ref[n][0];
            state.b1 = ref[n][1];
            state.b2 = ref[n][2];
            state.b3 = ref[n][3];
            state.b4 = ref[n][4];
            state.b5 = ref[n][5];
            state.b6 = ref[n][6];
            state.b7 = ref[n][7];
            state.b8 = ref[n][8];
            state.b9 = ref[n][9];
            state.b10 = ref[n][10];
            state.b11 = ref[n][11];
            state.b12 = ref[n][12];
            state.b13 = ref[n][13];
            state.b14 = ref[n][14];
            state.b15 = ref[n][15];
            aes.helpShiftRows(state);
            CPPUNIT_ASSERT(state.b0 == ref[n + 1][0]);
            CPPUNIT_ASSERT(state.b1 == ref[n + 1][1]);
            CPPUNIT_ASSERT(state.b2 == ref[n + 1][2]);
            CPPUNIT_ASSERT(state.b3 == ref[n + 1][3]);
            CPPUNIT_ASSERT(state.b4 == ref[n + 1][4]);
            CPPUNIT_ASSERT(state.b5 == ref[n + 1][5]);
            CPPUNIT_ASSERT(state.b6 == ref[n + 1][6]);
            CPPUNIT_ASSERT(state.b7 == ref[n + 1][7]);
            CPPUNIT_ASSERT(state.b8 == ref[n + 1][8]);
            CPPUNIT_ASSERT(state.b9 == ref[n + 1][9]);
            CPPUNIT_ASSERT(state.b10 == ref[n + 1][10]);
            CPPUNIT_ASSERT(state.b11 == ref[n + 1][11]);
            CPPUNIT_ASSERT(state.b12 == ref[n + 1][12]);
            CPPUNIT_ASSERT(state.b13 == ref[n + 1][13]);
            CPPUNIT_ASSERT(state.b14 == ref[n + 1][14]);
            CPPUNIT_ASSERT(state.b15 == ref[n + 1][15]);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAtomicMethodTest::testInvShiftRows()
{
    cerr << "Test: testInvShiftRows()" << endl;
    try {
        AesTestHelper aes("0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        AesEncryption::state_t state;
        for(unsigned n = 2; n < 45; n += 5) {
            state.b0 = ref[n][0];
            state.b1 = ref[n][1];
            state.b2 = ref[n][2];
            state.b3 = ref[n][3];
            state.b4 = ref[n][4];
            state.b5 = ref[n][5];
            state.b6 = ref[n][6];
            state.b7 = ref[n][7];
            state.b8 = ref[n][8];
            state.b9 = ref[n][9];
            state.b10 = ref[n][10];
            state.b11 = ref[n][11];
            state.b12 = ref[n][12];
            state.b13 = ref[n][13];
            state.b14 = ref[n][14];
            state.b15 = ref[n][15];
            aes.helpInvShiftRows(state);
            CPPUNIT_ASSERT(state.b0 == ref[n - 1][0]);
            CPPUNIT_ASSERT(state.b1 == ref[n - 1][1]);
            CPPUNIT_ASSERT(state.b2 == ref[n - 1][2]);
            CPPUNIT_ASSERT(state.b3 == ref[n - 1][3]);
            CPPUNIT_ASSERT(state.b4 == ref[n - 1][4]);
            CPPUNIT_ASSERT(state.b5 == ref[n - 1][5]);
            CPPUNIT_ASSERT(state.b6 == ref[n - 1][6]);
            CPPUNIT_ASSERT(state.b7 == ref[n - 1][7]);
            CPPUNIT_ASSERT(state.b8 == ref[n - 1][8]);
            CPPUNIT_ASSERT(state.b9 == ref[n - 1][9]);
            CPPUNIT_ASSERT(state.b10 == ref[n - 1][10]);
            CPPUNIT_ASSERT(state.b11 == ref[n - 1][11]);
            CPPUNIT_ASSERT(state.b12 == ref[n - 1][12]);
            CPPUNIT_ASSERT(state.b13 == ref[n - 1][13]);
            CPPUNIT_ASSERT(state.b14 == ref[n - 1][14]);
            CPPUNIT_ASSERT(state.b15 == ref[n - 1][15]);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAtomicMethodTest::testMixColumns()
{
    cerr << "Test: testMixColumns()" << endl;
    try {
        AesTestHelper aes("0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        AesEncryption::state_t state;
        for(unsigned n = 2; n < 45; n += 5) {
            state.b0 = ref[n][0];
            state.b1 = ref[n][1];
            state.b2 = ref[n][2];
            state.b3 = ref[n][3];
            state.b4 = ref[n][4];
            state.b5 = ref[n][5];
            state.b6 = ref[n][6];
            state.b7 = ref[n][7];
            state.b8 = ref[n][8];
            state.b9 = ref[n][9];
            state.b10 = ref[n][10];
            state.b11 = ref[n][11];
            state.b12 = ref[n][12];
            state.b13 = ref[n][13];
            state.b14 = ref[n][14];
            state.b15 = ref[n][15];
            aes.helpMixColumns(state);
            CPPUNIT_ASSERT(state.b0 == ref[n + 1][0]);
            CPPUNIT_ASSERT(state.b1 == ref[n + 1][1]);
            CPPUNIT_ASSERT(state.b2 == ref[n + 1][2]);
            CPPUNIT_ASSERT(state.b3 == ref[n + 1][3]);
            CPPUNIT_ASSERT(state.b4 == ref[n + 1][4]);
            CPPUNIT_ASSERT(state.b5 == ref[n + 1][5]);
            CPPUNIT_ASSERT(state.b6 == ref[n + 1][6]);
            CPPUNIT_ASSERT(state.b7 == ref[n + 1][7]);
            CPPUNIT_ASSERT(state.b8 == ref[n + 1][8]);
            CPPUNIT_ASSERT(state.b9 == ref[n + 1][9]);
            CPPUNIT_ASSERT(state.b10 == ref[n + 1][10]);
            CPPUNIT_ASSERT(state.b11 == ref[n + 1][11]);
            CPPUNIT_ASSERT(state.b12 == ref[n + 1][12]);
            CPPUNIT_ASSERT(state.b13 == ref[n + 1][13]);
            CPPUNIT_ASSERT(state.b14 == ref[n + 1][14]);
            CPPUNIT_ASSERT(state.b15 == ref[n + 1][15]);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAtomicMethodTest::testInvMixColumns()
{
    cerr << "Test: testInvMixColumns()" << endl;
    try {
        AesTestHelper aes("0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        AesEncryption::state_t state;
        for(unsigned n = 3; n < 45; n += 5) {
            state.b0 = ref[n][0];
            state.b1 = ref[n][1];
            state.b2 = ref[n][2];
            state.b3 = ref[n][3];
            state.b4 = ref[n][4];
            state.b5 = ref[n][5];
            state.b6 = ref[n][6];
            state.b7 = ref[n][7];
            state.b8 = ref[n][8];
            state.b9 = ref[n][9];
            state.b10 = ref[n][10];
            state.b11 = ref[n][11];
            state.b12 = ref[n][12];
            state.b13 = ref[n][13];
            state.b14 = ref[n][14];
            state.b15 = ref[n][15];
            aes.helpInvMixColumns(state);
            CPPUNIT_ASSERT(state.b0 == ref[n - 1][0]);
            CPPUNIT_ASSERT(state.b1 == ref[n - 1][1]);
            CPPUNIT_ASSERT(state.b2 == ref[n - 1][2]);
            CPPUNIT_ASSERT(state.b3 == ref[n - 1][3]);
            CPPUNIT_ASSERT(state.b4 == ref[n - 1][4]);
            CPPUNIT_ASSERT(state.b5 == ref[n - 1][5]);
            CPPUNIT_ASSERT(state.b6 == ref[n - 1][6]);
            CPPUNIT_ASSERT(state.b7 == ref[n - 1][7]);
            CPPUNIT_ASSERT(state.b8 == ref[n - 1][8]);
            CPPUNIT_ASSERT(state.b9 == ref[n - 1][9]);
            CPPUNIT_ASSERT(state.b10 == ref[n - 1][10]);
            CPPUNIT_ASSERT(state.b11 == ref[n - 1][11]);
            CPPUNIT_ASSERT(state.b12 == ref[n - 1][12]);
            CPPUNIT_ASSERT(state.b13 == ref[n - 1][13]);
            CPPUNIT_ASSERT(state.b14 == ref[n - 1][14]);
            CPPUNIT_ASSERT(state.b15 == ref[n - 1][15]);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAtomicMethodTest::testAddRoundKey()
{
    cerr << "Test: testAddRoundKey()" << endl;
    try {
        AesTestHelper aes("0123456789abcdef2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        AesEncryption::state_t state;
        AesEncryption::word32_t key[4];
        for(unsigned n = 3; n < 45; n += 5) {
            state.b0 = ref[n][0];
            state.b1 = ref[n][1];
            state.b2 = ref[n][2];
            state.b3 = ref[n][3];
            state.b4 = ref[n][4];
            state.b5 = ref[n][5];
            state.b6 = ref[n][6];
            state.b7 = ref[n][7];
            state.b8 = ref[n][8];
            state.b9 = ref[n][9];
            state.b10 = ref[n][10];
            state.b11 = ref[n][11];
            state.b12 = ref[n][12];
            state.b13 = ref[n][13];
            state.b14 = ref[n][14];
            state.b15 = ref[n][15];
            for(unsigned m = 0, i = 0; m < 4; m++, i += 4) {
                key[m].b0 = ref[n + 1][i];
                key[m].b1 = ref[n + 1][i + 1];
                key[m].b2 = ref[n + 1][i + 2];
                key[m].b3 = ref[n + 1][i + 3];
            }
            aes.helpAddRoundKey(state, key);
            CPPUNIT_ASSERT(state.b0 == ref[n + 2][0]);
            CPPUNIT_ASSERT(state.b1 == ref[n + 2][1]);
            CPPUNIT_ASSERT(state.b2 == ref[n + 2][2]);
            CPPUNIT_ASSERT(state.b3 == ref[n + 2][3]);
            CPPUNIT_ASSERT(state.b4 == ref[n + 2][4]);
            CPPUNIT_ASSERT(state.b5 == ref[n + 2][5]);
            CPPUNIT_ASSERT(state.b6 == ref[n + 2][6]);
            CPPUNIT_ASSERT(state.b7 == ref[n + 2][7]);
            CPPUNIT_ASSERT(state.b8 == ref[n + 2][8]);
            CPPUNIT_ASSERT(state.b9 == ref[n + 2][9]);
            CPPUNIT_ASSERT(state.b10 == ref[n + 2][10]);
            CPPUNIT_ASSERT(state.b11 == ref[n + 2][11]);
            CPPUNIT_ASSERT(state.b12 == ref[n + 2][12]);
            CPPUNIT_ASSERT(state.b13 == ref[n + 2][13]);
            CPPUNIT_ASSERT(state.b14 == ref[n + 2][14]);
            CPPUNIT_ASSERT(state.b15 == ref[n + 2][15]);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

void AesAtomicMethodTest::testKeyExpansion()
{
    const char *key[] = {
        "2b7e151628aed2a6abf7158809cf4f3c",
        "8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b",
        "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4",
        NULL
    };
    const char *expkey[] = {
        "2b7e151628aed2a6abf7158809cf4f3ca0fafe1788542cb123a339392a6c7605f2c295f27a96b9435935807a7359f67f3d80477d4716fe3e1e237e446d7a883bef44a541a8525b7fb671253bdb0bad00d4d1c6f87c839d87caf2b8bc11f915bc6d88a37a110b3efddbf98641ca0093fd4e54f70e5f5fc9f384a64fb24ea6dc4fead27321b58dbad2312bf5607f8d292fac7766f319fadc2128d12941575c006ed014f9a8c9ee2589e13f0cc8b6630ca6",
        "8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7bfe0c91f72402f5a5ec12068e6c827f6b0e7a95b95c56fec24db7b4bd69b5411885a74796e92538fde75fad44bb095386485af05721efb14fa448f6d94d6dce24aa326360113b30e6a25e7ed583b1cf9a27f939436a94f767c0a69407d19da4e1ec1786eb6fa64971485f703222cb8755e26d135233f0b7b340beeb282f18a2596747d26b458c553ea7e1466c9411f1df821f750aad07d753ca4005388fcc5006282d166abc3ce7b5e98ba06f448c773c8ecc720401002202",
        "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff49ba354118e6925afa51a8b5f2067fcdea8b09c1a93d194cdbe49846eb75d5b9ad59aecb85bf3c917fee94248de8ebe96b5a9328a2678a647983122292f6c79b3812c81addadf48ba24360af2fab8b46498c5bfc9bebd198e268c3ba709e0421468007bacb2df331696e939e46c518d80c814e20476a9fb8a5025c02d59c58239de1369676ccc5a71fa2563959674ee155886ca5d2e2f31d77e0af1fa27cf73c3749c47ab18501ddae2757e4f7401905acafaaae3e4d59b349adf6acebd10190dfe4890d1e6188d0b046df344706c631e",
        NULL
    };
    cerr << "Test: testKeyExpansion()" << endl;
    try {
        for(unsigned n = 0; key[n] != NULL; n++) {
            AesTestHelper aes(key[n]);
            string eks = aes.getExpandedKeyAsHexString();
            cerr << "Reference: " << expkey[n] << endl <<
                    "Generated: " << eks << endl;
            cerr.flush();
            CPPUNIT_ASSERT(eks.compare(expkey[n]) == 0);
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
    }
}

/*
 ***********************
 * Class AesTestHelper *
 ***********************
 */

AesTestHelper::AesTestHelper(const char* keystring) throw (AesBadKeyException) :
    AesEncryption(keystring)
{
}

inline uint8_t AesTestHelper::helpSubByte(uint8_t x)
{
    return subByte(x);
}

inline void AesTestHelper::helpSubBytes(AesEncryption::state_t& state)
{
    subBytes(state);
}

uint8_t AesTestHelper::helpInvSubByte(uint8_t x)
{
    return invSubByte(x);
}

inline void AesTestHelper::helpInvSubBytes(AesEncryption::state_t& state)
{
    invSubBytes(state);
}

inline void AesTestHelper::helpShiftRows(AesEncryption::state_t& state)
{
    shiftRows(state);
}

inline void AesTestHelper::helpInvShiftRows(AesEncryption::state_t& state)
{
    invShiftRows(state);
}

inline void AesTestHelper::helpMixColumns(AesEncryption::state_t& state)
{
    mixColumns(state);
}

inline void AesTestHelper::helpInvMixColumns(AesEncryption::state_t& state)
{
    invMixColumns(state);
}

void AesTestHelper::helpAddRoundKey(AesEncryption::state_t& state, AesEncryption::word32_t *rkey)
{
    for(unsigned n = 0; n < 4; n++)
        key[n] = rkey[n];
    addRoundKey(state, 0);
}

bool AesTestHelper::compareWithSbox(uint8_t a[])
{
    for(unsigned n = 0; n < 256; n++)
        if(a[n] != subByte(n)) {
            cerr << "Error at position " << n << '.' << endl <<
                    "Should be 0x" << setw(2) << right << setfill('0') << hex << (unsigned) subByte(n) <<
                    " but found 0x" << setw(2) << right << setfill('0') << hex << (unsigned) a[n] << '.' << endl;
            return false;
        }
    return true;
}

bool AesTestHelper::compareWithInvSbox(uint8_t a[])
{
    for(unsigned n = 0; n < 256; n++)
        if(a[n] != invSubByte(n)) {
            cerr << "Error at position " << n << '.' << endl <<
                    "Should be 0x" << setw(2) << right << setfill('0') << hex << (unsigned) invSubByte(n) <<
                    " but found 0x" << setw(2) << right << setfill('0') << hex << (unsigned) a[n] << '.' << endl;
            return false;
        }
    return true;
}
