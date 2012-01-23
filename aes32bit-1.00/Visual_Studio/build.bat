@echo off
pushd %~dp0

if "%1" == "/?" goto help
if "%1" == "/help" goto help

rem Check for Visual Studio Command Prompt's environment
cl > NUL 2>&1
if errorlevel 9009 (
   echo No environment for "Visual Studio Command Prompt" set.
   set EXITVAL=9009
   goto done
)

cl 2>&1 | find "80x86" > NUL
if not errorlevel 1 (
   rem 32 bit environment set
   set CPPUNITLIB="cppunit32.lib"
) else (
   rem 64 bit environment set
   set CPPUNITLIB="cppunit64.lib"
)

cd ..\src
if %errorlevel% neq 0 (
   set EXITVAL = %errorlevel%
   goto done
)
nmake /f ..\Visual_Studio\src.mak %*
if %errorlevel% neq 0 (
   set EXITVAL = %errorlevel%
   goto done
)

cd ..\tests
if %errorlevel% neq 0 (
   set EXITVAL = %errorlevel%
   goto done
)
nmake /f ..\Visual_Studio\tests.mak CPPUNITLIB=%CPPUNITLIB% %*
if %errorlevel% neq 0 (
   set EXITVAL = %errorlevel%
   goto done
)

set EXITVAL = 0
goto done

:help
echo Usage: build.bat [ /? ^| /help ]
echo        build.bat [ nmake-flags ] [ CPPUNIT=^<cppunit-dir^> ] [ clean ^| all ]
echo.
echo First version prints this help screen.
echo The second one invokes nmake to clean or build.
echo With CPPUNIT=^<cppunit-dir^> you can specify the path where your CppUnit
echo installation resides, e.g. CPPUNIT=C:\cppunit.
set EXITVAL = 0

:done
popd
exit /b %EXITVAL%
