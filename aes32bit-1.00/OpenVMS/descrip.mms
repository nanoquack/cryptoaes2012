.SUFFIXES
.SUFFIXES .EXE .OBJ .cpp

EXE = aes32bit.exe
OBJ = main.OBJ,aes.OBJ,version.OBJ
.cpp.OBJ :
	CXX/DEFINE=__USE_STD_IOSTREAM/STANDARD=GNU/PREFIX=ALL $(MMS$SOURCE)


$(EXE) DEPENDS_ON $(OBJ)
	CXXLINK/EXECUTABLE=$(EXE) $(OBJ)

aes.OBJ DEPENDS_ON aes.cpp

main.OBJ DEPENDS_ON main.cpp

version.OBJ DEPENDS_ON version.cpp

clean :
	del *.OBJ;*,$(EXE);*
