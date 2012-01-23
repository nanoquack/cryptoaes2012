/*
 * Project: aes32bit - AES implementation for 32 bit platforms
 * File   : main.cpp
 * Author : Oliver Mueller <oliver@cogito-ergo-sum.org>
 * Purpose: Main program.
 *
 * $Id: main.cpp 50 2011-05-16 18:38:56Z oliver $
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

#ifdef __MVS__
#define _XOPEN_SOURCE
#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>

#if defined(_MSC_VER) || defined(__WATCOM_CPLUSPLUS__)
#include "getopt/getopt.h"
#endif

#include "aes.h"
#include "version.h"

using namespace std;

union word64_t
{
    uint64_t w;
    uint8_t b[8];

    struct
    {
#ifdef ARCH_BIG_ENDIAN
        uint8_t b7;
        uint8_t b6;
        uint8_t b5;
        uint8_t b4;
        uint8_t b3;
        uint8_t b2;
        uint8_t b1;
        uint8_t b0;
#else
        uint8_t b0;
        uint8_t b1;
        uint8_t b2;
        uint8_t b3;
        uint8_t b4;
        uint8_t b5;
        uint8_t b6;
        uint8_t b7;
#endif
    };
};

/*
 * Print usage of program
 */
void usage()
{
    cout << "Usage: aes32bit -h" << endl <<
            "       aes32bit [ -e | -d ] [-b] -k key-as-hex [-m ecb] [-f file] [-o file]" << endl <<
            "       aes32bit [ -e | -d ] [-b] -k key-as-hex -m { cbc | cfb | ofb } \\" << endl <<
            "                  -i iv-as-hex [-f file] [-o file]" << endl;
}

void binaryCipher(AesEncryption& aes, AesEncryption::CipherMode mode, bool encipher, istream& in, ostream& out)
{
#if (defined(__VMS) && defined(__DECCXX))
    vector<uint8_t> c, m;
    for(int u = 0; u < 16; u++) {
        c[u] = 0;
        m[u] = 0;
    }
#else
    vector<uint8_t> c(16, 0), m(16, 0);
#endif
    uint8_t x, y = 0, b;
    if(encipher) {
        while(!in.eof()) {
            bool read = false;
            for(x = 0; x < 16; x++) {
                in >> b;
                if(in.eof())
                    break;
                else {
                    m[x] = b;
                    read = true;
                }
            }
            if(read) {
                c = aes.encipherVectorToVector(m, mode);
                y = x;
                for(x = 0; x < 16; x++)
                    out << ((char) c[x]);
                out.flush();
            }
        }
        m[0] = (char) y;
        c = aes.encipherVectorToVector(m, mode);
        for(x = 0; x < 16; x++)
            out << ((char) c[x]);
    } else {
#if (defined(__VMS) && defined(__DECCXX))
        vector<uint8_t> p, q;
        for(int u = 0; u < 16; u++) {
            p[u] = 0;
            q[u] = 0;
        }
#else
        vector<uint8_t> p(16, 0), q(16, 0);
#endif
        uint8_t z = 0;
        uint8_t first = 2;
        while(!in.eof()) {
            bool read = false;
            for(x = 0; x < 16; x++) {
                in >> b;
                if(in.eof())
                    break;
                else {
                    c[x] = b;
                    read = true;
                }
            }
            q = p;
            p = m;
            if(read) {
                m = aes.decipherVectorToVector(c, mode);
                z = m[0];
            }
            if(first) {
                first--;
            } else
                for(int x = 0; x < (in.eof() || !read ? z : 16); x++)
                    out << ((char) q[x]);
        }
    }
}

/*
 * Main program
 */
int main(int argc, char** argv)
{
    string key;
    string iv;
    bool encipher = true;
    bool binary = false;
    AesEncryption::CipherMode mode = AesEncryption::ECB;
    string infile;
    string outfile;

    cerr << "aes32bit ";
#ifdef __WATCOM_CPLUSPLUS__
    cerr << (Version::getInstance().getVersion()).c_str();
#else
    cerr << Version::getInstance().getVersion();
#endif
    cerr << endl <<
            "Copyright (c) 2011, Oliver Mueller, "
            "http://www.cogito-ergo-sum.org/" << endl <<
            "All rights reserved." << endl << endl;

    if(argc == 1) {
        usage();
        return 0;
    }

    int c;
    while((c = getopt(argc, argv, ":debhi:k:m:f:o:")) != EOF) {
        switch(c) {
            case 'd':
                encipher = false;
                break;
            case 'e':
                encipher = true;
                break;
            case 'b':
                binary = true;
                break;
            case 'h':
                usage();
                return 0;
                break;
            case 'i':
                iv = optarg;
                break;
            case 'k':
                key = optarg;
                break;
            case 'f':
                infile = optarg;
                break;
            case 'o':
                outfile = optarg;
                break;
            case 'm':
                if(!strcmp(optarg, "ecb"))
                    mode = AesEncryption::ECB;
                else if(!strcmp(optarg, "cbc"))
                    mode = AesEncryption::CBC;
                else if(!strcmp(optarg, "cfb"))
                    mode = AesEncryption::CFB;
                else if(!strcmp(optarg, "ofb"))
                    mode = AesEncryption::OFB;
                else {
                    cerr << "Error: Unknown cipher mode `" << optarg << "'." << endl;
                    return 1;
                }
                break;
            default:
                cerr << "Error: Unrecognized option -" << optopt << endl;
                return 1;
        }
    }

    // Check modes and options
    if(key.length() == 0) {
        cerr << "Error: You have to provide an AES key." << endl;
        return 1;
    }
    if(mode != AesEncryption::ECB && iv.length() == 0) {
        cerr << "Error: You have to provide an initialization vector (IV)" << endl <<
                "       for the chosen cipher mode." << endl;
        return 1;
    }
    if(optind < argc) {
        cerr << "Error: Too many arguments." << endl;
        return 1;
    }

    // Cipher
    try {
        AesEncryption aes(key);
        if(mode != AesEncryption::ECB)
            aes.setIvFromHex(iv);
        if(binary) {
            // binary mode
            ifstream *fin = NULL;
            ofstream *fout = NULL;
            if(infile.empty() || infile == "-") {
                cin.unsetf(ios::skipws);
            } else {
                fin = new ifstream(infile.c_str(), ifstream::in | ifstream::binary);
                if(!fin->good()) {
#ifdef __WATCOM_CPLUSPLUS__
                    cerr << "Could not open input file \"" << infile.c_str() << "\"" << endl;
#else
                    cerr << "Could not open input file \"" << infile << "\"" << endl;
#endif
                    return 1;
                }
                fin->unsetf(ios::skipws);
            }
            if(!outfile.empty() && outfile != "-") {
                fout = new ofstream(outfile.c_str(), ofstream::out | ofstream::binary | ofstream::trunc);
                if(!fout->good()) {
#ifdef __WATCOM_CPLUSPLUS__
                    cerr << "Could not open output file \"" << outfile.c_str() << "\"" << endl;
#else
                    cerr << "Could not open output file \"" << outfile << "\"" << endl;
#endif
                    return 1;
                }
            }
            binaryCipher(aes, mode, encipher,
                (fin == NULL ? cin : *fin),
                (fout == NULL ? cout : *fout));
            if(fin != NULL)
                fin->close();
            if(fout != NULL)
                fout->close();
        } else {
            // text mode
            char line[1025];
            string result;
            while(cin.getline(line, 1024)) {
                if(encipher)
                    result = aes.encipherToHexString(line, mode);
                else
                    result = aes.decipherFromHexString(line, mode);
#ifdef __WATCOM_CPLUSPLUS__
                cout << result.c_str() << endl;
#else
                cout << result << endl;
#endif
            }
        }
    } catch(AesBadKeyException& e) {
        cerr << "Error: Could not read key; reason: " << e.what() << "." << endl;
        return 1;
    } catch(AesBadIvException& e) {
        cerr << "Error: Could not read IV; reason: " << e.what() << "." << endl;
        return 1;
    }

    return 0;
}

