set( SOURCES )

INCLUDE (CheckIncludeFiles)
INCLUDE (CheckFunctionExists)

# TODO: move both macros to special file
# Using the provided folder_path, recursively adds
# all the CPP, HPP and H source files to the SOURCES list.
macro( add_to_sources folder_path )
    file( GLOB_RECURSE TEMP ${folder_path}/*.cpp ${folder_path}/*.c )   
    list( LENGTH SOURCES len )    
    
    if ( ${len} EQUAL 0 )
        set( SOURCES ${TEMP} )        
    else()
        list( APPEND SOURCES ${TEMP} )
    endif()
endmacro()

# Using the provided folder_path, adds
# all the CPP, HPP and H source files to the SOURCES list.
# Only the folder_path is looked at, not the child folders. 
macro( add_to_sources_no_rec folder_path )
    file( GLOB TEMP ${folder_path}/*.cpp ${folder_path}/*.c )  
    list( LENGTH SOURCES len )    
    
    if ( ${len} EQUAL 0 )
        set( SOURCES ${TEMP} )        
    else()
        list( APPEND SOURCES ${TEMP} )
    endif()
endmacro()

set(APP_NO_THREADS false)
CHECK_INCLUDE_FILES("arpa/inet.h" HAVE_ARPA_INET_H )
CHECK_INCLUDE_FILES("arpa/nameser_compat.h" HAVE_ARPA_NAMESER_COMPAT_H )
set(HAVE_BOOL true)
CHECK_FUNCTION_EXISTS(catclose HAVE_CATCLOSE)
CHECK_FUNCTION_EXISTS(catgets HAVE_CATGETS)
CHECK_FUNCTION_EXISTS(catopen HAVE_CATOPEN)
CHECK_FUNCTION_EXISTS(clock_gettime HAVE_CLOCK_GETTIME)
CHECK_INCLUDE_FILES("CoreServices/CoreServices.h" HAVE_CORESERVICES_CORESERVICES_H )
CHECK_INCLUDE_FILES("cpuid.h" HAVE_CPUID_H )
CHECK_INCLUDE_FILES("ctype.h" HAVE_CTYPE_H )
CHECK_INCLUDE_FILES("dlfcn.h" HAVE_DLFCN_H )
CHECK_INCLUDE_FILES("endian.h" HAVE_ENDIAN_H )
CHECK_INCLUDE_FILES("errno.h" HAVE_ERRNO_H )
CHECK_INCLUDE_FILES("fcntl.h" HAVE_FCNTL_H )
CHECK_INCLUDE_FILES("float.h" HAVE_FLOAT_H )
CHECK_FUNCTION_EXISTS(ftime HAVE_FTIME)
CHECK_FUNCTION_EXISTS(getaddrinfo HAVE_GETADDRINFO)
CHECK_FUNCTION_EXISTS(getcwd HAVE_GETCWD)
CHECK_FUNCTION_EXISTS(gethostbyaddr HAVE_GETHOSTBYADDR)
CHECK_FUNCTION_EXISTS(gethostbyname HAVE_GETHOSTBYNAME)
CHECK_FUNCTION_EXISTS(gettimeofday HAVE_GETTIMEOFDAY)
CHECK_FUNCTION_EXISTS(iconv HAVE_ICONV)
CHECK_FUNCTION_EXISTS(iconv_close HAVE_ICONV_CLOSE)
CHECK_INCLUDE_FILES("iconv.h" HAVE_ICONV_H )
CHECK_FUNCTION_EXISTS(iconv_open HAVE_ICONV_OPEN)
CHECK_INCLUDE_FILES("inttypes.h" HAVE_INTTYPES_H )
CHECK_INCLUDE_FILES("langinfo.h" HAVE_LANGINFO_H )
find_package(nsl)
find_package(socket)
CHECK_INCLUDE_FILES("limits.h" HAVE_LIMITS_H )

configure_file(${XSILIUM_SOURCE_DIR}/CMake/Templates/xerces.config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

# Define to 1 if you have the `localeconv' function. */
#cmakedefine HAVE_LOCALECONV @HAVE_LOCALECONV@

# Define to 1 if you have the <locale.h> header file. */
#cmakedefine HAVE_LOCALE_H @HAVE_LOCALE_H@

# define if the compiler implements L"widestring" */
#cmakedefine HAVE_LSTRING @HAVE_LSTRING@

# Define to 1 if you have the <machine/endian.h> header file. */
#cmakedefine HAVE_MACHINE_ENDIAN_H @HAVE_MACHINE_ENDIAN_H@

# Define to 1 if you have the `mblen' function. */
#cmakedefine HAVE_MBLEN @HAVE_MBLEN@

# Define to 1 if you have the `mbrlen' function. */
#cmakedefine HAVE_MBRLEN @HAVE_MBRLEN@

# Define to 1 if you have the `mbsrtowcs' function. */
#cmakedefine HAVE_MBSRTOWCS @HAVE_MBSRTOWCS@

# Define to 1 if you have the `mbstowcs' function. */
#cmakedefine HAVE_MBSTOWCS @HAVE_MBSTOWCS@

# Define to 1 if you have the `memmove' function. */
#cmakedefine HAVE_MEMMOVE @HAVE_MEMMOVE@

# Define to 1 if you have the <memory.h> header file. */
#cmakedefine HAVE_MEMORY_H @HAVE_MEMORY_H@

# Define to 1 if you have the `memset' function. */
#cmakedefine HAVE_MEMSET @HAVE_MEMSET@

# define if the compiler implements namespaces */
#cmakedefine HAVE_NAMESPACES @HAVE_NAMESPACES@

# Define to 1 if you have the <netdb.h> header file. */
#cmakedefine HAVE_NETDB_H @HAVE_NETDB_H@

# Define to 1 if you have the <netinet/in.h> header file. */
#cmakedefine HAVE_NETINET_IN_H @HAVE_NETINET_IN_H@

# Define to 1 if you have the `nl_langinfo' function. */
#cmakedefine HAVE_NL_LANGINFO @HAVE_NL_LANGINFO@

# Define to 1 if you have the <nl_types.h> header file. */
#cmakedefine HAVE_NL_TYPES_H @HAVE_NL_TYPES_H@

# Define to 1 if you have the `pathconf' function. */
#cmakedefine HAVE_PATHCONF @HAVE_PATHCONF@

# Define if you have POSIX threads libraries and header files. */
#cmakedefine HAVE_PTHREAD @HAVE_PTHREAD@

# Define to 1 if you have the `realpath' function. */
#cmakedefine HAVE_REALPATH @HAVE_REALPATH@

# Define to 1 if you have the `setlocale' function. */
#cmakedefine HAVE_SETLOCALE @HAVE_SETLOCALE@

# Define to 1 if you have the `socket' function. */
#cmakedefine HAVE_SOCKET @HAVE_SOCKET@

# Define to 1 if stdbool.h conforms to C99. */
#cmakedefine HAVE_STDBOOL_H @HAVE_STDBOOL_H@

# Define to 1 if you have the <stddef.h> header file. */
#cmakedefine HAVE_STDDEF_H @HAVE_STDDEF_H@

# Define to 1 if you have the <stdint.h> header file. */
#cmakedefine HAVE_STDINT_H @HAVE_STDINT_H@

# Define to 1 if you have the <stdio.h> header file. */
#cmakedefine HAVE_STDIO_H @HAVE_STDIO_H@

# Define to 1 if you have the <stdlib.h> header file. */
#cmakedefine HAVE_STDLIB_H @HAVE_STDLIB_H@

# define if the compiler supports ISO C++ standard library */
#cmakedefine HAVE_STD_LIBS @HAVE_STD_LIBS@

# define if the compiler supports the std namespace */
#cmakedefine HAVE_STD_NAMESPACE @HAVE_STD_NAMESPACE@

# Define to 1 if you have the `strcasecmp' function. */
#cmakedefine HAVE_STRCASECMP @HAVE_STRCASECMP@

# Define to 1 if you have the `strchr' function. */
#cmakedefine HAVE_STRCHR @HAVE_STRCHR@

# Define to 1 if you have the `strdup' function. */
#cmakedefine HAVE_STRDUP @HAVE_STRDUP@

# Define to 1 if you have the `stricmp' function. */
#cmakedefine HAVE_STRICMP @HAVE_STRICMP@

# Define to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H @HAVE_STRINGS_H@

# Define to 1 if you have the <string.h> header file. */
#cmakedefine HAVE_STRING_H @HAVE_STRING_H@

# Define to 1 if you have the `strncasecmp' function. */
#cmakedefine HAVE_STRNCASECMP @HAVE_STRNCASECMP@

# Define to 1 if you have the `strnicmp' function. */
#cmakedefine HAVE_STRNICMP @HAVE_STRNICMP@

# Define to 1 if you have the `strrchr' function. */
#cmakedefine HAVE_STRRCHR @HAVE_STRRCHR@

# Define to 1 if you have the `strstr' function. */
#cmakedefine HAVE_STRSTR @HAVE_STRSTR@

# Define to 1 if you have the `strtol' function. */
#cmakedefine HAVE_STRTOL @HAVE_STRTOL@

# Define to 1 if you have the `strtoul' function. */
#cmakedefine HAVE_STRTOUL @HAVE_STRTOUL@

# Define to 1 if you have the <sys/param.h> header file. */
#cmakedefine HAVE_SYS_PARAM_H @HAVE_SYS_PARAM_H@

# Define to 1 if you have the <sys/socket.h> header file. */
#cmakedefine HAVE_SYS_SOCKET_H @HAVE_SYS_SOCKET_H@

# Define to 1 if you have the <sys/stat.h> header file. */
#cmakedefine HAVE_SYS_STAT_H @HAVE_SYS_STAT_H@

# Define to 1 if you have the <sys/timeb.h> header file. */
#cmakedefine HAVE_SYS_TIMEB_H @HAVE_SYS_TIMEB_H@

# Define to 1 if you have the <sys/time.h> header file. */
#cmakedefine HAVE_SYS_TIME_H @HAVE_SYS_TIME_H@

# Define to 1 if you have the <sys/types.h> header file. */
#cmakedefine HAVE_SYS_TYPES_H @HAVE_SYS_TYPES_H@

# Define to 1 if you have the `towlower' function. */
#cmakedefine HAVE_TOWLOWER @HAVE_TOWLOWER@

# Define to 1 if you have the `towupper' function. */
#cmakedefine HAVE_TOWUPPER @HAVE_TOWUPPER@

# Define to 1 if you have the <unistd.h> header file. */
#cmakedefine HAVE_UNISTD_H @HAVE_UNISTD_H@

# Define to 1 if you have the <wchar.h> header file. */
#cmakedefine HAVE_WCHAR_H @HAVE_WCHAR_H@

# Define to 1 if you have the `wcsicmp' function. */
#cmakedefine HAVE_WCSICMP @HAVE_WCSICMP@

# Define to 1 if you have the `wcslwr' function. */
#cmakedefine HAVE_WCSLWR @HAVE_WCSLWR@

# Define to 1 if you have the `wcsnicmp' function. */
#cmakedefine HAVE_WCSNICMP @HAVE_WCSNICMP@

# Define to 1 if you have the `wcsrtombs' function. */
#cmakedefine HAVE_WCSRTOMBS @HAVE_WCSRTOMBS@

# Define to 1 if you have the `wcstombs' function. */
#cmakedefine HAVE_WCSTOMBS @HAVE_WCSTOMBS@

# Define to 1 if you have the `wcsupr' function. */
#cmakedefine HAVE_WCSUPR @HAVE_WCSUPR@

# Define to 1 if you have the <wctype.h> header file. */
#cmakedefine HAVE_WCTYPE_H @HAVE_WCTYPE_H@

# Define to 1 if you have the <winsock2.h> header file. */
#cmakedefine HAVE_WINSOCK2_H @HAVE_WINSOCK2_H@

# Define to 1 if the system has the type `_Bool'. */
#cmakedefine HAVE__BOOL @HAVE__BOOL@

# Define to 1 if you have to use const char* with iconv, to 0 if you must use char*. */
#cmakedefine ICONV_USES_CONST_POINTER @ICONV_USES_CONST_POINTER@

# Define to the sub-directory in which libtool stores uninstalled libraries. */
#cmakedefine LT_OBJDIR @LT_OBJDIR@

# Define to 1 if your C compiler doesn't accept -c and -o together. */
#cmakedefine NO_MINUS_C_MINUS_O @NO_MINUS_C_MINUS_O@

# Name of package */
#cmakedefine PACKAGE @PACKAGE@

# Define to the address where bug reports for this package should be sent. */
#cmakedefine PACKAGE_BUGREPORT @PACKAGE_BUGREPORT@

# Define to the full name of this package. */
#cmakedefine PACKAGE_NAME @PACKAGE_NAME@

# Define to the full name and version of this package. */
#cmakedefine PACKAGE_STRING @PACKAGE_STRING@

# Define to the one symbol short name of this package. */
#cmakedefine PACKAGE_TARNAME @PACKAGE_TARNAME@

# Define to the home page for this package. */
#cmakedefine PACKAGE_URL @PACKAGE_URL@

# Define to the version of this package. */
#cmakedefine PACKAGE_VERSION @PACKAGE_VERSION@

# Define to necessary symbol if this constant uses a non-standard name on your system. */
#cmakedefine PTHREAD_CREATE_JOINABLE @PTHREAD_CREATE_JOINABLE@

# The size of `int', as computed by sizeof. */
#cmakedefine SIZEOF_INT @SIZEOF_INT@

# The size of `long', as computed by sizeof. */
#cmakedefine SIZEOF_LONG @SIZEOF_LONG@

# The size of `long long', as computed by sizeof. */
#cmakedefine SIZEOF_LONG_LONG @SIZEOF_LONG_LONG@

# The size of `short', as computed by sizeof. */
#cmakedefine SIZEOF_SHORT @SIZEOF_SHORT@

# The size of `wchar_t', as computed by sizeof. */
#cmakedefine SIZEOF_WCHAR_T @SIZEOF_WCHAR_T@

# The size of `__int64', as computed by sizeof. */
#cmakedefine SIZEOF___INT64 @SIZEOF___INT64@

# Define to 1 if you have the ANSI C header files. */
#cmakedefine STDC_HEADERS @STDC_HEADERS@

# Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#cmakedefine TIME_WITH_SYS_TIME @TIME_WITH_SYS_TIME@

# Version number of package */
#cmakedefine VERSION @VERSION@

# Define to true if autoconf is used in this configuration */
#cmakedefine XERCES_AUTOCONF @XERCES_AUTOCONF@

# Define if namespaces is supported by the compiler */
#cmakedefine XERCES_HAS_CPP_NAMESPACE @XERCES_HAS_CPP_NAMESPACE@

# Define to have SSE2 instruction support detected at runtime using __cpuid*/
#cmakedefine XERCES_HAVE_CPUID_INTRINSIC @XERCES_HAVE_CPUID_INTRINSIC@

# Define to 1 if you have emmintrin.h */
#cmakedefine XERCES_HAVE_EMMINTRIN_H @XERCES_HAVE_EMMINTRIN_H@

# Define to have SSE2 instruction support detected at runtime using __get_cpuid */
#cmakedefine XERCES_HAVE_GETCPUID @XERCES_HAVE_GETCPUID@

# Define to 1 if you have intrin.h */
#cmakedefine XERCES_HAVE_INTRIN_H @XERCES_HAVE_INTRIN_H@

# Define to 1 if we have inttypes.h */
#cmakedefine XERCES_HAVE_INTTYPES_H @XERCES_HAVE_INTTYPES_H@

# Define to have SSE2 instruction used at runtime */
#cmakedefine XERCES_HAVE_SSE2_INTRINSIC @XERCES_HAVE_SSE2_INTRINSIC@

# Define to 1 if we have sys/types.h */
#cmakedefine XERCES_HAVE_SYS_TYPES_H @XERCES_HAVE_SYS_TYPES_H@

# Define to have Xerces_autoconf_config.hpp include wchar.h */
#cmakedefine XERCES_INCLUDE_WCHAR_H @XERCES_INCLUDE_WCHAR_H@

# Define if there is support for L"widestring" */
#cmakedefine XERCES_LSTRSUPPORT @XERCES_LSTRSUPPORT@

# Define if the isstream library can be included as <iostream> */
#cmakedefine XERCES_NEW_IOSTREAMS @XERCES_NEW_IOSTREAMS@

# Define to have XMemory.hpp avoid declaring a matching operator delete for the placement operator new */
#cmakedefine XERCES_NO_MATCHING_DELETE_OPERATOR @XERCES_NO_MATCHING_DELETE_OPERATOR@

# Define if there is no native bool support in this environment */
#cmakedefine XERCES_NO_NATIVE_BOOL @XERCES_NO_NATIVE_BOOL@

# Define to use backslash as an extra path delimiter character */
#cmakedefine XERCES_PATH_DELIMITER_BACKSLASH @XERCES_PATH_DELIMITER_BACKSLASH@

# Define as the platform's export attribute */
#cmakedefine XERCES_PLATFORM_EXPORT @XERCES_PLATFORM_EXPORT@

# Define as the platform's import attribute */
#cmakedefine XERCES_PLATFORM_IMPORT @XERCES_PLATFORM_IMPORT@

# An appropriate signed 16 bit integer type */
#cmakedefine XERCES_S16BIT_INT @XERCES_S16BIT_INT@

# An appropriate signed 32 bit integer type */
#cmakedefine XERCES_S32BIT_INT @XERCES_S32BIT_INT@

# An appropriate signed 64 bit integer type */
#cmakedefine XERCES_S64BIT_INT @XERCES_S64BIT_INT@

# Define as the appropriate size_t type */
#cmakedefine XERCES_SIZE_T @XERCES_SIZE_T@

# Define as the appropriate ssize_t type */
#cmakedefine XERCES_SSIZE_T @XERCES_SSIZE_T@

# Define if the std namespace is supported */
#cmakedefine XERCES_STD_NAMESPACE @XERCES_STD_NAMESPACE@

# An appropriate unsigned 16 bit integer type */
#cmakedefine XERCES_U16BIT_INT @XERCES_U16BIT_INT@

# An appropriate unsigned 32 bit integer type */
#cmakedefine XERCES_U32BIT_INT @XERCES_U32BIT_INT@

# An appropriate unsigned 64 bit integer type */
#cmakedefine XERCES_U64BIT_INT @XERCES_U64BIT_INT@

# Define to use the POSIX file mgr */
#cmakedefine XERCES_USE_FILEMGR_POSIX @XERCES_USE_FILEMGR_POSIX@

# Define to use the Windows file mgr */
#cmakedefine XERCES_USE_FILEMGR_WINDOWS @XERCES_USE_FILEMGR_WINDOWS@

# Define to use the iconv-based MsgLoader */
#cmakedefine XERCES_USE_MSGLOADER_ICONV @XERCES_USE_MSGLOADER_ICONV@

# Define to use the ICU-based MsgLoader */
#cmakedefine XERCES_USE_MSGLOADER_ICU @XERCES_USE_MSGLOADER_ICU@

# Define to use the InMemory MsgLoader */
#cmakedefine XERCES_USE_MSGLOADER_INMEMORY @XERCES_USE_MSGLOADER_INMEMORY@

# Define to use the NoThread mutex mgr */
#cmakedefine XERCES_USE_MUTEXMGR_NOTHREAD @XERCES_USE_MUTEXMGR_NOTHREAD@

# Define to use the POSIX mutex mgr */
#cmakedefine XERCES_USE_MUTEXMGR_POSIX @XERCES_USE_MUTEXMGR_POSIX@

# Define to use the Windows mutex mgr */
#cmakedefine XERCES_USE_MUTEXMGR_WINDOWS @XERCES_USE_MUTEXMGR_WINDOWS@

# Define to use the Mac OS X CFURL NetAccessor */
#cmakedefine XERCES_USE_NETACCESSOR_CFURL @XERCES_USE_NETACCESSOR_CFURL@

# Define to use the CURL NetAccessor */
#cmakedefine XERCES_USE_NETACCESSOR_CURL @XERCES_USE_NETACCESSOR_CURL@

# Define to use the Sockets-based NetAccessor */
#cmakedefine XERCES_USE_NETACCESSOR_SOCKET @XERCES_USE_NETACCESSOR_SOCKET@

# Define to use the WinSock NetAccessor */
#cmakedefine XERCES_USE_NETACCESSOR_WINSOCK @XERCES_USE_NETACCESSOR_WINSOCK@

# Define to use the GNU iconv transcoder */
#cmakedefine XERCES_USE_TRANSCODER_GNUICONV @XERCES_USE_TRANSCODER_GNUICONV@

# Define to use the iconv transcoder */
#cmakedefine XERCES_USE_TRANSCODER_ICONV @XERCES_USE_TRANSCODER_ICONV@

# Define to use the ICU-based transcoder */
#cmakedefine XERCES_USE_TRANSCODER_ICU @XERCES_USE_TRANSCODER_ICU@

# Define to use the Mac OS UnicodeConverter-based transcoder */
#cmakedefine XERCES_USE_TRANSCODER_MACOSUNICODECONVERTER @XERCES_USE_TRANSCODER_MACOSUNICODECONVERTER@

# Define to use the Windows transcoder */
#cmakedefine XERCES_USE_TRANSCODER_WINDOWS @XERCES_USE_TRANSCODER_WINDOWS@

# Define to the 16 bit type used to represent Xerces UTF-16 characters */
#cmakedefine XERCES_XMLCH_T @XERCES_XMLCH_T@

# Define to empty if `const' does not conform to ANSI C. */
#cmakedefine const @const@

# Define to `__inline__' or `__inline' if that's what the C compiler calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#cmakedefine inline @inline@
#endif

# Define to `long int' if <sys/types.h> does not define. */
#cmakedefine off_t @off_t@

# Define to `unsigned int' if <sys/types.h> does not define. */
#cmakedefine size_t @size_t@

# Define to empty if the keyword `volatile' does not work. Warning: valid code using `volatile' can become incorrect without. Disable with care. */
#cmakedefine volatile @volatile@


ist( APPEND SOURCES "${CMAKE_CURRENT_BINARY_DIR}/config.h" )

add_to_sources( xercesc/dom )
add_to_sources( xercesc/framework )
add_to_sources( xercesc/internal )
add_to_sources( xercesc/parsers )
add_to_sources( xercesc/sax )
add_to_sources( xercesc/sax2 )
add_to_sources( xercesc/validators )
add_to_sources( xercesc/xinclude )

add_to_sources( xercesc/util/MsgLoaders/InMemory )
add_to_sources( xercesc/util/regx )

add_to_sources_no_rec( xercesc/util )
add_to_sources_no_rec( . )


# These files are included by hpp files and should not be directly compiled
file(GLOB to_remove xercesc/dom/impl/DOMDeepNodeListPool.c 
                    xercesc/framework/psvi/XSNamedMap.c 
                    xercesc/util/BaseRefVectorOf.c 
                    xercesc/util/CountedPointer.c 
                    xercesc/util/FlagJanitor.c 
                    xercesc/util/Hash2KeysSetOf.c 
                    xercesc/util/Janitor.c 
                    xercesc/util/KeyRefPair.c 
                    xercesc/util/KeyValuePair.c 
                    xercesc/util/LogicalPath.c 
                    xercesc/util/NameIdPool.c 
                    xercesc/util/RefArrayOf.c 
                    xercesc/util/RefArrayVectorOf.c 
                    xercesc/util/RefHash2KeysTableOf.c 
                    xercesc/util/RefHash3KeysIdPool.c 
                    xercesc/util/RefHashTableOf.c 
                    xercesc/util/RefStackOf.c 
                    xercesc/util/RefVectorOf.c 
                    xercesc/util/TransENameMap.c 
                    xercesc/util/ValueArrayOf.c 
                    xercesc/util/ValueHashTableOf.c 
                    xercesc/util/ValueStackOf.c 
                    xercesc/util/ValueVectorOf.c
					
                    # these are just not needed
                    towlower.c
                    towupper.c
                    )
                    
list(REMOVE_ITEM SOURCES ${to_remove} )

if( MSVC )
    add_to_sources( xercesc/util/Transcoders/Win32 )
    
    list( APPEND SOURCES
        xercesc/util/FileManagers/WindowsFileMgr.cpp
        xercesc/util/MutexManagers/WindowsMutexMgr.cpp )
        
    file( GLOB to_remove ./stricmp.c
                         ./strnicmp.c
                         )
    
    list( REMOVE_ITEM SOURCES ${to_remove} )
else()
    if( APPLE )
        add_to_sources( xercesc/util/Transcoders/Iconv )
    else()
        add_to_sources( xercesc/util/Transcoders/IconvGNU )
    endif()    
    
    list( APPEND SOURCES
        xercesc/util/FileManagers/PosixFileMgr.cpp
        xercesc/util/MutexManagers/PosixMutexMgr.cpp  )
endif()
        
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_library(Xerces ${SOURCES} ) 

add_definitions( -DXERCES_STATIC_LIBRARY
                 -DXERCES_BUILDING_LIBRARY
                 -DXERCES_USE_MSGLOADER_INMEMORY
                 -DHAVE_LIMITS_H
                 -DHAVE_SYS_TIMEB_H
                 -DHAVE_FTIME
                 -DHAVE_WCSUPR
                 -DHAVE_WCSLWR
                 -DHAVE_WCSICMP
                 -DHAVE_WCSNICMP
                 -DHAVE_STRING_H
                 -DHAVE_STRCASECMP
                 -DHAVE_STRNCASECMP
                 -DHAVE_WCHAR_H
                 -DHAVE_WCTYPE_H
                 -DHAVE_TOWLOWER
                 -DHAVE_TOWUPPER
		 -DHAVE_CPUID_H  )

if( MSVC )
    add_definitions( -DUNICODE -D_UNICODE )
    add_definitions( -D_CRT_SECURE_NO_DEPRECATE
                     -DXERCES_PATH_DELIMITER_BACKSLASH
                     -DXERCES_USE_TRANSCODER_WINDOWS
                     -DXERCES_USE_FILEMGR_WINDOWS   
                     -DXERCES_USE_MUTEXMGR_WINDOWS
                     -DHAVE_STRICMP
                     -DHAVE_STRNICMP
                   )
                     
    # xerces wants to disable these warnings
    add_definitions( /wd4996 )
    add_definitions( /wd4355 )
    
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t- /MP")
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL" ) 
    set_target_properties(Xerces PROPERTIES STATIC_LIBRARY_FLAGS "/LTCG" )
    
else()
    add_definitions( -DXERCES_USE_FILEMGR_POSIX
                     -DXERCES_USE_MUTEXMGR_POSIX 
                   )  
    
    if( APPLE )
        add_definitions( -DXERCES_USE_TRANSCODER_ICONV )
    else()
        add_definitions( -DXERCES_USE_TRANSCODER_GNUICONV )
    endif()
    
    if( CMAKE_COMPILER_IS_GNUCXX )
        # SSE2 autodetection sometimes fails on Linux, so we'll just
        # require the presence of SSE2. Everything since the year 2000 (Pentium 4)
        # has it, so it's not like we're leaving anyone out.
        add_definitions( -msse2 ) 
    endif()
                   
    # We need to link to pthreads on unix                                 
    target_link_libraries(Xerces pthread )
                       
endif()

set(XERCESC_H_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" CACHE PATH "" FORCE)
set(XERCESC_LIB_DBG "Xerces" CACHE STRING "" FORCE)
set(XERCESC_LIB "Xerces" CACHE STRING "" FORCE)
mark_as_advanced(XERCESC_H_PATH XERCESC_LIB_DBG XERCESC_LIB)
