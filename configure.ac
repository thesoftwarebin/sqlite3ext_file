#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([sqlite3ext_file], [1.0], [andrear1979@hotmail.com])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
LT_INIT([shared win32-dll])

# Checks for programs.
AC_PROG_CC
#AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_MKDIR_P

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h utime.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset mkdir strrchr])

AC_CHECK_LIB([sqlite3], [sqlite3_value_text], [], [AC_MSG_ERROR([SQLite library is a mandatory requirement.])])

AC_CHECK_DECL([_wfopen], [AC_DEFINE([HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES], [], [Define this symbol if you have _wfopen and want support for UTF8 pathnames in Windows, otherwise undefine.])])

AC_CHECK_DECLS([sys_siglist], [], [],
[#include <signal.h>
/* NetBSD declares sys_siglist in unistd.h. */
#if HAVE_UNISTD_H
# include <unistd.h>
#endif
])


AC_CHECK_HEADER([stdio.h],
[AC_DEFINE([HAVE_STDIO_H], [1],
[Define to 1 if you have <stdio.h>.])],
[AC_MSG_ERROR([Sorry, can’t do anything for you])])

AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT

#if (defined(WIN32) || defined(_WIN32)) && !defined(HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES) && !defined(LIBSQLITEFILE_DISABLE_WCHAR)
#-	#define HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
#-#endif
