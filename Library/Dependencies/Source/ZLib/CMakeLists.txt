cmake_minimum_required(VERSION 2.4.4)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

project(zlib)

set(VERSION "1.2.8")

set(zlib_SOURCES
  adler32.c
  compress.c
  crc32.c
  crc32.h
  deflate.c
  deflate.h
  gzclose.c
  gzguts.h
  gzlib.c
  gzread.c
  gzwrite.c
  infback.c
  inffast.c
  inffast.h
  inffixed.h
  inflate.c
  inflate.h
  inftrees.c
  inftrees.h
  trees.c
  trees.h
  uncompr.c
  zconf.h
  zlib.h
  zutil.c
  zutil.h
)

add_library(ZLib STATIC ${zlib_SOURCES})

if (APPLE)
 set_target_properties(ZLib PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO")

 if(OGRE_BUILD_PLATFORM_APPLE_IOS)
  set_target_properties(ZLib PROPERTIES XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT "NO")
 endif()
endif()
