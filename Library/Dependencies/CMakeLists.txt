# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

project(Dependencies)
SET(Dependencies 1.0)

include(NoWarn)
subdirs(Source/ois)
subdirs(Source/freetype)
subdirs(Source/zlib)

if (XSILIUM_USE_STATIC_FREEIMAGE)
	subdirs(Source/FreeImage) 
endif()

if (NOT XSILIUM_DISABLE_ZIP)
	subdirs(Source/zziplib)
endif()

if(NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
    add_subdirectory(Source/Cg)
endif ()