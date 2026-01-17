#ifndef LIBSQLITEFILE_COMPAT_MKDIR_H
#define LIBSQLITEFILE_COMPAT_MKDIR_H


#if HAVE_MKDIR
#  if MKDIR_TAKES_ONE_ARG
     /* MinGW32 */
#    define mkdir(a, b) mkdir(a)
#  endif
#else
#  if HAVE__MKDIR
     /* plain Windows 32 */
#    define mkdir(a, b) _mkdir(a)
#  else
#    error "Don't know how to create a directory on this system."
#  endif
#endif

#endif // LIBSQLITEFILE_COMPAT_MKDIR_H
