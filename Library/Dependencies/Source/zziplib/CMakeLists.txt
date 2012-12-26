# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)


set(zziplib_SOURCES
  zzip/autoconf.h
  zzip/conf.h
  zzip/_config.h
  zzip/__debug.h
  zzip/dir.c
  zzip/__dirent.h
  zzip/err.c
  zzip/fetch.c
  zzip/fetch.h
  zzip/file.c
  zzip/file.h
  zzip/__fnmatch.h
  zzip/format.h
  zzip/fseeko.c
  zzip/fseeko.h
  zzip/__hints.h
  zzip/info.c
  zzip/info.h
  zzip/lib.h
  zzip/memdisk.c
  zzip/memdisk.h
  zzip/__mmap.h
  zzip/mmapped.c
  zzip/mmapped.h
  zzip/_msvc.h
  zzip/plugin.c
  zzip/plugin.h
  zzip/stat.c
  zzip/stdint.h
  zzip/types.h
  zzip/write.c
  zzip/write.h
  zzip/zip.c
  zzip/zzip32.h
  zzip/zzip.h
)

# need zlib includes
include_directories(${XSILIUM_ZLIB_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
  add_definitions(-D_MSC_VER)
endif ()

add_library(${XSILIUM_ZZIP_TARGET} STATIC ${zziplib_SOURCES})
config_target_if_iphone_build(${XSILIUM_ZZIP_TARGET} TRUE)



