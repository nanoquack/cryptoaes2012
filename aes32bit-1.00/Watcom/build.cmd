@echo off
if "%1" == "/?" goto usage
if "%1" == "/h" goto usage
if "%1" == "/help" goto usage

cd ..\src
wmake /ms /f ..\Watcom\MAKEFILE %1 %2 %3 %4 %5 %6 %7 %8 %9
cd ..\Watcom
goto done

:usage
echo Build Batch File for OpenWatcom C++ for OS/2, eComStation and Win32
echo Usage: build.cmd [ /? ^| /h ^| /help ]
echo        build.cmd [ wmake-options ] [ clean ^| all ] 

:done
