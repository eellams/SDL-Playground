#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE
LT_INIT

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
# AC_PROG_RANLIB

AC_CONFIG_MACRO_DIRS([m4])

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lSDL2':
AC_CHECK_LIB([SDL2], [main])
# FIXME: Replace `main' with a function in `-lSDL2_gfx':
AC_CHECK_LIB([SDL2_gfx], [main])

AC_SEARCH_LIBS([math], [floor])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

#AM_PATH_CHECK(,[have_check="yes"],
#              AC_MSG_WARN([Check not found; cannot run unit tests!])
#              [have_check="no"])
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
#AM_CONDITIONAL(HAVE_CHECK, test x"$have_check" = "xyes")

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
