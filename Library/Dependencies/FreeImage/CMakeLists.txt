project(FreeImage)

file(GLOB_RECURSE sources_Utilities Utilities/*.cpp Utilities/*.h)

set(FreeImage_SOURCES
	
)

# need include directories for FreeImage and all the sub libs
include_directories(Source)
include_directories(Source/FreeImageToolkit)
include_directories(Source/LibJPEG)
include_directories(Source/LibMNG)
include_directories(Source/LibOpenJPEG)
include_directories(Source/LibPNG)
include_directories(Source/LibRawLite)
include_directories(Source/LibTIFF)
include_directories(Source/OpenEXR)
include_directories(Source/OpenEXR/Half)
include_directories(Source/OpenEXR/Iex)
include_directories(Source/OpenEXR/IlmImf)
include_directories(Source/OpenEXR/IlmThread)
include_directories(Source/OpenEXR/Imath)
include_directories(Source/ZLib)

add_definitions(-DOPJ_STATIC -DLIBRAW_NODLL -DNO_LCMS -DLIBRAW_LIBRARY_BUILD -DMNG_BUILD_SO -DFREEIMAGE_LIB)
add_library(FreeImage STATIC ${FreeImage_SOURCES})

if (APPLE)
 set_target_properties(FreeImage PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO")

 if(OGRE_BUILD_PLATFORM_APPLE_IOS)
  set_target_properties(FreeImage PROPERTIES XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT "NO")
 endif()
endif()

set(FreeImage_INCLUDE_DIR "${FreeImage_SOURCE_DIR}/Source" CACHE PATH "" FORCE)
set(FreeImage_LIBRARY_DBG FreeImage CACHE STRING "" FORCE)
set(FreeImage_LIBRARY_REL FreeImage CACHE STRING "" FORCE)

mark_as_advanced(FreeImage_INCLUDE_DIR FreeImage_LIBRARY_DBG FreeImage_LIBRARY_REL)
