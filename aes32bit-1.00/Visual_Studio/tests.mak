CPPUNIT = "C:\Develop\cppunit-1.12.1"
OBJ1 = AesAlgorithmTestRunner.obj AesAlgorithmTest.obj kat.obj aes.obj
OBJ2 = AesAtomicMethodTestRunner.obj AesAtomicMethodTest.obj aes.obj
OBJ3 = AesKeyConversionTestRunner.obj AesKeyConversionTest.obj aes.obj
PROG1 = aes32kat.exe
PROG2 = aes32metest.exe
PROG3 = aes32keytest.exe
CC = cl
CFLAGS = /EHsc /MD /I"$(CPPUNIT)\include" /I"..\src" /c 
LINK = cl
LFLAGS = /EHsc /MD
CPPUNITLIB=cppunit.lib
LIBS = "$(CPPUNIT)\lib\$(CPPUNITLIB)"

.cpp.obj:
        $(CC) $(CFLAGS) $*.cpp

all: $(PROG1) $(PROG2) $(PROG3)

$(PROG1): $(OBJ1)
	$(CC) $(LFLAGS) $** /link $(LIBS) /out:$(PROG1) 

$(PROG2): $(OBJ2)
	$(CC) $(LFLAGS) $** /link $(LIBS) /out:$(PROG2) 

$(PROG3): $(OBJ3)
	$(CC) $(LFLAGS) $** /link $(LIBS) /out:$(PROG3) 

AesAlgorithmTestRunner.obj: AesAlgorithmTestRunner.cpp AesAlgorithmTest.h

AesAlgorithmTest.obj: AesAlgorithmTest.cpp AesAlgorithmTest.h ..\src\aes.h

AesAtomicMethodTestRunner.obj: AesAtomicMethodTestRunner.cpp AesAtomicMethodTest.h

AesAtomicMethodTest.obj: AesAtomicMethodTest.cpp AesAtomicMethodTest.h ..\src\aes.h

AesKeyConversionTestRunner.obj: AesKeyConversionTestRunner.cpp AesKeyConversionTest.h

AesKeyConversionTest.obj: AesKeyConversionTest.cpp AesKeyConversionTest.h ..\src\aes.h

kat.obj: kat.cpp AesAlgorithmTest.h ..\src\aes.h

aes.obj: ..\src\aes.cpp ..\src\aes.h
	$(CC) $(CFLAGS) ..\src\aes.cpp

clean:
	del *.obj *.exe
