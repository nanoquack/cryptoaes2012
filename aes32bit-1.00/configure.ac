#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([aes32bit], [1.00], [oliver@cogito-ergo-sum.org])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/aes.cpp])
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_CONFIG_HEADERS([config.h])
AC_C_BIGENDIAN

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_ARG_WITH([cppunit],
    [  --without-cppunit       Disable tests with CppUnit. Note that you can't run AES KAT without CppUnit!],
    [cppunit_enable=$with_cppunit],
    [cppunit_enable=yes]
)

AS_IF(
    [test "x$cppunit_enable" = xyes],
    [AM_PATH_CPPUNIT(1.12.0, [], [AC_MSG_FAILURE(CppUnit >= 1.12.0 is required to build aes32bit.)])]
)

# Checks for header files.
AC_CHECK_HEADERS([stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_UINT8_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_C_BIGENDIAN([CPPFLAGS="$CPPFLAGS -DARCH_BIG_ENDIAN=1"],[CPPFLAGS="$CPPFLAGS -DARCH_LITTLE_ENDIAN=1"])

# Checks for library functions.

AC_OUTPUT
