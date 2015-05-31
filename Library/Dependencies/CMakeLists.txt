# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

project(Dependencies)
SET(Dependencies 1.0)

include(NoWarn)
subdirs(Source/ois)
subdirs(Source/freetype)
subdirs(Source/rapidxml-1.13)
subdirs(Source/ZLib)
subdirs(Source/libiconv)


if (XSILIUM_USE_STATIC_FREEIMAGE)
	subdirs(Source/FreeImage) 
endif()



if (NOT XSILIUM_DISABLE_ZIP)
	subdirs(Source/ZZipLib)
endif()
