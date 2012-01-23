OBJ = main.obj aes.obj version.obj getopt.obj
PROG = aes32bit.exe
CC = cl
CFLAGS = /MD /EHsc /I".\getopt" /c
LINK = cl
LFLAGS = /EHsc /MD 

.cpp.obj:
	$(CC) $(CFLAGS) $*.cpp

all: $(PROG)

$(PROG): $(OBJ)
	$(LINK) $(LFLAGS) $** /link /out:$(PROG) 

main.obj: main.cpp aes.h version.h getopt\getopt.h

aes.obj: aes.cpp aes.h

version.obj: version.cpp version.h

getopt.obj: getopt\getopt.c
	$(CC) $(CFLAGS) getopt\getopt.c

clean:
	del *.obj $(PROG)
