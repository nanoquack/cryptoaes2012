check_PROGRAMS = aes32kat aes32keytest aes32metest

aes32kat_SOURCES = AesAlgorithmTestRunner.cpp AesAlgorithmTest.cpp AesAlgorithmTest.h kat.cpp ../src/aes.cpp ../src/aes.h
aes32kat_CXXFLAGS = $(CPPUNIT_CFLAGS) -I../src
aes32kat_LDADD = $(CPPUNIT_LIBS)

aes32keytest_SOURCES = AesKeyConversionTest.cpp AesKeyConversionTestRunner.cpp AesKeyConversionTest.h ../src/aes.cpp ../src/aes.h
aes32keytest_CXXFLAGS = $(CPPUNIT_CFLAGS) -I../src
aes32keytest_LDADD = $(CPPUNIT_LIBS)

aes32metest_SOURCES = AesAtomicMethodTest.cpp AesAtomicMethodTestRunner.cpp AesAtomicMethodTest.h ../src/aes.cpp ../src/aes.h
aes32metest_CXXFLAGS = $(CPPUNIT_CFLAGS) -I../src
aes32metest_LDADD = $(CPPUNIT_LIBS)
