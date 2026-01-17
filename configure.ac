#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([sqlite3ext_file], [1.0.2], [andrear1979@hotmail.com])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
LT_INIT([shared win32-dll])

# Checks for programs.
AC_PROG_CC
#AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_MKDIR_P

AC_CHECK_PROG([HAVESQLITE3SHELL], [sqlite3], [sqlite3])
AM_CONDITIONAL([HAVESQLITE3SHELLFORTESTS], [test x$HAVESQLITE3SHELL = xsqlite3])

# Checks for header files.
AC_CHECK_HEADER([stdio.h],  [], [AC_MSG_ERROR([stdio.h is a mandatory requirement to build this package])])
AC_CHECK_HEADER([string.h], [], [AC_MSG_ERROR([string.h is a mandatory requirement to build this package])])
AC_CHECK_HEADER([utime.h],  [], [AC_MSG_ERROR([utime.h is a mandatory requirement to build this package])])

AC_CHECK_HEADERS([direct.h])

AC_CHECK_DECL(
	[_wfopen], 
	[
		AC_DEFINE([HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES], [], [Define this symbol if you have _wfopen and want support for UTF8 pathnames in Windows, otherwise undefine.])
		AC_MSG_NOTICE([Since _wfopen is available, support for accented filenames in Windows has been enabled;])
		AC_MSG_NOTICE([see symbol HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES in config.h])
	]
)

AX_FUNC_MKDIR

# Checks for libraries.
AC_CHECK_LIB([sqlite3], [sqlite3_value_text], [], [AC_MSG_ERROR([SQLite library is a mandatory requirement.])])

AC_ARG_WITH(
	[bigfiletests],
	[AS_HELP_STRING([--with-bigfiletests], [perform additional tests on big files (>= 4GB)])]
)
AM_CONDITIONAL([HAVEBIGFILETESTS], [test "x$with_bigfiletests" == xyes])

AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT
