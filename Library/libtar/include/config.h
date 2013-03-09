/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if your system has a working basename */
/* #undef HAVE_BASENAME */

/* Define if your system has a working major */
/* #undef HAVE_MAJOR */

/* Define if your system has a working minor */
/* #undef HAVE_MINOR */

/* Define if your system has a working minor */
/* #undef HAVE_MAKEDEV */

/* Define to 1 if you have the <ctype.h> header file. */
#define HAVE_CTYPE_H 1

/* Define to 1 if you have the <sys/sysmacros.h> header file. */
/* #undef HAVE_SYS_SYSMACROS_H */

/* Define to 1 if the system has the type `dev_t'. */
#define HAVE_DEV_T 1

/* Define if your system has a working dirname */
/* #undef HAVE_DIRNAME */

/* Define to 1 if your system has a working POSIX `fnmatch' function. */
/* #undef HAVE_FNMATCH */

/* Define to 1 if you have the <fnmatch.h> header file. */
/* #undef HAVE_FNMATCH_H */

/* Define to 1 if you have the <inttypes.h> header file. */
/* #undef HAVE_INTTYPES_H */

/* Define to 1 if you have the <io.h> header file. */
/* #undef HAVE_IO_H */

/* Define to 1 if you have the `lchown' function. */
/* #undef HAVE_LCHOWN */

/* Define to 1 if you have the <libgen.h> header file. */
/* #undef HAVE_LIBGEN_H */

/* Define to 1 if you have the `z' library (-lz). */
#define HAVE_LIBZ 1

/* Define to 1 if the system has the type `major_t'. */
/* #undef HAVE_MAJOR_T */

/* Define to 1 if you have the <memory.h> header file. */
/* #undef HAVE_MEMORY_H */

/* Define to 1 if you have the <dirent.h> header file. */
/* #undef HAVE_DIRENT_H */

/* Define to 1 if you have the <sys/param.h> header file. */
/* #undef HAVE_SYS_PARAM_H */

/* Define to 1 if the system has the type `minor_t'. */
/* #undef HAVE_MINOR_T */

/* Define to 1 if the system has the type `nlink_t'. */
#define HAVE_NLINK_T 1

/* Define if your system has a working snprintf */
#define HAVE_SNPRINTF 1

/* Define if your system has a working vsnprintf */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
/* #undef HAVE_STDLIB_H */

/* Define to 1 if you have the <sys/mkdev.h> header file. */
/* #undef HAVE_SYS_MKDEV_H */

/* Define if you have the strdup function */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strftime' function. */
/* #undef HAVE_STRFTIME */

/* Define to 1 if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define to 1 if you have the <string.h> header file. */
/* #undef HAVE_STRING_H */

/* Define if you have the strlcpy function */
#define HAVE_STRLCPY 1

/* Define if you have the strmode function */
/* #undef HAVE_STRMODE */

/* Define if you have the strsep function */
/* #undef HAVE_STRSEP */

/* Define to 1 if you have the <sys/stat.h> header file. */
/* #undef HAVE_SYS_STAT_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if the system has the type `uint64_t'. */
#define HAVE_UINT64_T 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if `major', `minor', and `makedev' are declared in <mkdev.h>.
   */
/* #undef MAJOR_IN_MKDEV */

/* Define to 1 if `major', `minor', and `makedev' are declared in
   <sysmacros.h>. */
/* #undef MAJOR_IN_SYSMACROS */

/* Define as 1 if makedev expects three arguments */
/* #undef MAKEDEV_THREE_ARGS */

/* Define if you want to use the basename function */
/* #undef NEED_BASENAME */

/* Define if you want to use the dirname function */
/* #undef NEED_DIRNAME */

/* Define if you want to use the fnmatch function */
#define NEED_FNMATCH 1

/* Define if you want to use the makedev function */
#define NEED_MAKEDEV 1

/* Define if you want to use the snprintf function */
/* #undef NEED_SNPRINTF */

/* Define if you want to use the strdup function */
/* #undef NEED_STRDUP */

/* Define if you want to use the strlcpy function */
/* #undef NEED_STRLCPY */

/* Define if you want to use the strmode function */
/* #undef NEED_STRMODE */

/* Define if you want to use the strsep function */
/* #undef NEED_STRSEP */

/* Define to the address where bug reports for this package should be sent. */
/* #undef PACKAGE_BUGREPORT */

/* Define to the full name of this package. */
#define PACKAGE_NAME "libtar"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libtar 1.2.11"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libtar"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.2.11"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if on AIX 3.
   System headers sometimes define this.
   We just want to avoid a redefinition error message.  */
#ifndef _ALL_SOURCE
/* #undef _ALL_SOURCE */
#endif

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `unsigned long' if not defined in system header files. */
/* #undef dev_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `unsigned int' if not defined in system header files. */
#define major_t unsigned int

/* Define to `unsigned int' if not defined in system header files. */
#define minor_t unsigned int

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to `unsigned short' if not defined in system header files. */
/* #undef nlink_t */

/* Define to `long' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `unsigned' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define to `long long' if not defined in system header files. */
/* #undef uint64_t */
