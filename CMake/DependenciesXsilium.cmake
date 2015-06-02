#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------
#######################################################################
# Find all necessary and optional OGRE dependencies
#######################################################################

# OGRE_DEPENDENCIES_DIR can be used to specify a single base
# folder where the required dependencies may be found.
set(OGRE_DEPENDENCIES_DIR "" CACHE PATH "Path to prebuilt OGRE dependencies")
include(FindPkgMacros)
include(CEGUIMacros)

getenv_path(OGRE_DEPENDENCIES_DIR)
if(OGRE_BUILD_PLATFORM_APPLE_IOS)
  set(OGRE_DEP_SEARCH_PATH 
    ${OGRE_DEPENDENCIES_DIR}
    ${ENV_OGRE_DEPENDENCIES_DIR}
    "${OGRE_BINARY_DIR}/iOSDependencies"
    "${OGRE_SOURCE_DIR}/iOSDependencies"
    "${OGRE_BINARY_DIR}/../iOSDependencies"
    "${OGRE_SOURCE_DIR}/../iOSDependencies"
  )
elseif(OGRE_BUILD_PLATFORM_ANDROID)
  set(OGRE_DEP_SEARCH_PATH 
    ${OGRE_DEPENDENCIES_DIR}
    ${ENV_OGRE_DEPENDENCIES_DIR}
    "${OGRE_BINARY_DIR}/AndroidDependencies"
    "${OGRE_SOURCE_DIR}/AndroidDependencies"
    "${OGRE_BINARY_DIR}/../AndroidDependencies"
    "${OGRE_SOURCE_DIR}/../AndroidDependencies"
  )
else()
  set(OGRE_DEP_SEARCH_PATH 
    ${OGRE_DEPENDENCIES_DIR}
    ${ENV_OGRE_DEPENDENCIES_DIR}
    "${OGRE_BINARY_DIR}/Dependencies"
    "${OGRE_SOURCE_DIR}/Dependencies"
    "${OGRE_BINARY_DIR}/../Dependencies"
    "${OGRE_SOURCE_DIR}/../Dependencies"
  )
endif()

message(STATUS "Search path: ${OGRE_DEP_SEARCH_PATH}")

# Set hardcoded path guesses for various platforms
if (UNIX)
  set(OGRE_DEP_SEARCH_PATH ${OGRE_DEP_SEARCH_PATH} /usr/local)
  # Ubuntu 11.10 has an inconvenient path to OpenGL libraries
  set(OGRE_DEP_SEARCH_PATH ${OGRE_DEP_SEARCH_PATH} /usr/lib/${CMAKE_SYSTEM_PROCESSOR}-linux-gnu)
endif ()

# give guesses as hints to the find_package calls
set(CMAKE_PREFIX_PATH ${OGRE_DEP_SEARCH_PATH} ${CMAKE_PREFIX_PATH})
set(CMAKE_FRAMEWORK_PATH ${OGRE_DEP_SEARCH_PATH} ${CMAKE_FRAMEWORK_PATH})


#######################################################################
# Core dependencies
#######################################################################

# Find zlib
if(NOT XSILIUM_USE_STATIC_ZLIB)
	find_package(ZLIB)
	macro_log_feature(ZLIB_FOUND "ZLib" "Support for the ZLib library" "http://www.zlib.net/" FALSE "" "")
else()
	set(ZLIB_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/ZLib" )
	set(ZLIB_LIBRARIES "ZLib")
	set(ZLIB_FOUND 1)
endif()

if (ZLIB_FOUND)
	# Find zziplib
	if(NOT XSILIUM_USE_STATIC_ZZIP)
		find_package(ZZip)
  		macro_log_feature(ZZip_FOUND "zziplib" "Extract data from zip archives" "http://zziplib.sourceforge.net" FALSE "" "")
	else()
		set(ZZip_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/ZZipLib" )
		set(ZZip_LIBRARIES "ZZipLib")
		set(ZZip_FOUND 1)
	endif()	
endif ()

# Find FreeImage
if(NOT XSILIUM_USE_STATIC_FREEIMAGE)
	
	find_package(FreeImage)
	macro_log_feature(FREEIMAGE_FOUND "FreeImage" "Support for the FreeImage library" "http://freeimage.sourceforge.net/" FALSE "" "")

else()
	set(FreeImage_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/FreeImage/Source")
	set(FreeImage_LIBRARIES "FreeImage")
	set(FreeImage_FOUND 1)
endif()

set(FREEIMAGE_INCLUDE_DIRS "${FreeImage_INCLUDE_DIRS}")
set(FREEIMAGE_LIBRARIES "${FreeImage_LIBRARIES}")
set(FREEIMAGE_FOUND "${FreeImage_FOUND}")



# Find FreeType
if(NOT XSILIUM_USE_STATIC_FREETYPE)
	find_package(Freetype)
	macro_log_feature(FREETYPE_FOUND "freetype" "Portable font engine" "http://www.freetype.org" FALSE "" "")
else()
	set(FREETYPE_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/freetype/include")
	set(FREETYPE_LIBRARIES "freetype")
	set(FREETYPE_FOUND 1)
endif()

# Find X11
if (UNIX AND NOT APPLE AND NOT ANDROID AND NOT FLASHCC)
  find_package(X11)
  macro_log_feature(X11_FOUND "X11" "X Window system" "http://www.x.org" TRUE "" "")
  macro_log_feature(X11_Xt_FOUND "Xt" "X Toolkit" "http://www.x.org" TRUE "" "")
  find_library(XAW_LIBRARY NAMES Xaw Xaw7 PATHS ${OGRE_DEP_SEARCH_PATH} ${DEP_LIB_SEARCH_DIR} ${X11_LIB_SEARCH_PATH})
  macro_log_feature(XAW_LIBRARY "Xaw" "X11 Athena widget set" "http://www.x.org" TRUE "" "")
  mark_as_advanced(XAW_LIBRARY)
endif ()

# Ogg
set(OGG_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/ogg/include" "${CMAKE_BINARY_DIR}/Library/Dependencies/Source/ogg/include" )
set(OGG_LIBRARIES "ogg")

#######################################################################
# RenderSystem dependencies
#######################################################################

# Find OpenGL
if(NOT ANDROID AND NOT FLASHCC)
  find_package(OpenGL)
  macro_log_feature(OPENGL_FOUND "OpenGL" "Support for the OpenGL render system" "http://www.opengl.org/" FALSE "" "")
endif()

# Find OpenGL 3+
find_package(OpenGL)
macro_log_feature(OPENGL_FOUND "OpenGL 3+" "Support for the OpenGL 3+ render system" "http://www.opengl.org/" FALSE "" "")

# Find OpenGL ES 1.x
find_package(OpenGLES)
macro_log_feature(OPENGLES_FOUND "OpenGL ES 1.x" "Support for the OpenGL ES 1.x render system (DEPRECATED)" "http://www.khronos.org/opengles/" FALSE "" "")

# Find OpenGL ES 2.x
find_package(OpenGLES2)
macro_log_feature(OPENGLES2_FOUND "OpenGL ES 2.x" "Support for the OpenGL ES 2.x render system" "http://www.khronos.org/opengles/" FALSE "" "")

# Find OpenGL ES 3.x
find_package(OpenGLES3)
macro_log_feature(OPENGLES3_FOUND "OpenGL ES 3.x" "Support for the OpenGL ES 2.x render system with OpenGL ES 3 support" "http://www.khronos.org/opengles/" FALSE "" "")

# Find DirectX
if(WIN32)
	find_package(DirectX)
	macro_log_feature(DirectX9_FOUND "DirectX9" "Support for the DirectX render system" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")

	find_package(DirectX11)
	macro_log_feature(DirectX11_FOUND "DirectX11" "Support for the DirectX11 render system" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")
	
	find_package(DirectXInput)
 	macro_log_feature(Direct_FOUND "DirectInput/XInput" "Support for the DirectInput/XInput" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")

endif()

#######################################################################
# Additional features
#######################################################################

# Find Cg
if (NOT (OGRE_BUILD_PLATFORM_APPLE_IOS OR OGRE_BUILD_PLATFORM_WINRT OR ANDROID OR FLASHCC))
  find_package(Cg)
  macro_log_feature(Cg_FOUND "cg" "C for graphics shader language" "http://developer.nvidia.com/object/cg_toolkit.html" FALSE "" "")
endif ()

# Find Boost
# Prefer static linking in all cases
if (WIN32 OR APPLE)
	set(Boost_USE_STATIC_LIBS TRUE)
else ()
	# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
	set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
endif ()
if (APPLE AND OGRE_BUILD_PLATFORM_APPLE_IOS)
    set(Boost_USE_MULTITHREADED OFF)
endif()
set(Boost_ADDITIONAL_VERSIONS "1.56" "1.55" "1.55.0" "1.54" "1.54.0" "1.53" "1.53.0" "1.52" "1.52.0" "1.51" "1.51.0" "1.50" "1.50.0" "1.49" "1.49.0" "1.48" "1.48.0" "1.47" "1.47.0" "1.46" "1.46.0" "1.45" "1.45.0" "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40")
# Components that need linking (NB does not include header-only components like bind)
set(OGRE_BOOST_COMPONENTS thread date_time system filesystem log)
find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
if (NOT Boost_FOUND)
	# Try again with the other type of libs
	if(Boost_USE_STATIC_LIBS)
		set(Boost_USE_STATIC_LIBS OFF)
	else()
		set(Boost_USE_STATIC_LIBS ON)
	endif()
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
endif()

if(Boost_FOUND AND Boost_VERSION GREATER 104900)
    if(Boost_VERSION GREATER 105300)
        set(OGRE_BOOST_COMPONENTS thread date_time system atomic chrono filesystem log serialization)
    else()
        set(OGRE_BOOST_COMPONENTS thread date_time system chrono filesystem serialization)
    endif()
    find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
endif()

if(Boost_VERSION GREATER 105200)
	if(WIN32 OR APPLE)
		#boost threading version 4
		add_definitions( -DBOOST_THREAD_VERSION=4 )
	else()
		#boost threading version 4 et Boost log dynamic
		add_definitions( -DBOOST_LOG_DYN_LINK -DBOOST_THREAD_VERSION=4 )
	endif()
endif()

if(Boost_FOUND AND NOT WIN32)
  list(REMOVE_DUPLICATES Boost_LIBRARIES)
endif()

# Optional Boost libs (Boost_${COMPONENT}_FOUND
macro_log_feature(Boost_FOUND "boost" "Boost (general)" "http://boost.org" FALSE "" "")
macro_log_feature(Boost_THREAD_FOUND "boost-thread" "Used for threading support" "http://boost.org" FALSE "" "")
macro_log_feature(Boost_DATE_TIME_FOUND "boost-date_time" "Used for threading support" "http://boost.org" FALSE "" "")
if(Boost_VERSION GREATER 104900)
    macro_log_feature(Boost_SYSTEM_FOUND "boost-system" "Used for threading support" "http://boost.org" FALSE "" "")
    macro_log_feature(Boost_CHRONO_FOUND "boost-chrono" "Used for threading support" "http://boost.org" FALSE "" "")
	if(Boost_VERSION GREATER 105300)
		macro_log_feature(Boost_ATOMIC_FOUND "boost-atomic" "Used for threading support" "http://boost.org" FALSE "" "")
		macro_log_feature(Boost_LOG_FOUND "boost-log" "Used for logging" "http://boost.org" FALSE "" "")
	endif()
endif()

# POCO
find_package(POCO)
macro_log_feature(POCO_FOUND "POCO" "POCO framework" "http://pocoproject.org/" FALSE "" "")

# ThreadingBuildingBlocks
find_package(TBB)
macro_log_feature(TBB_FOUND "tbb" "Threading Building Blocks" "http://www.threadingbuildingblocks.org/" FALSE "" "")

# GLSL-Optimizer
find_package(GLSLOptimizer)
macro_log_feature(GLSL_Optimizer_FOUND "GLSL Optimizer" "GLSL Optimizer" "http://github.com/aras-p/glsl-optimizer/" FALSE "" "")

# HLSL2GLSL
find_package(HLSL2GLSL)
macro_log_feature(HLSL2GLSL_FOUND "HLSL2GLSL" "HLSL2GLSL" "http://hlsl2glslfork.googlecode.com/" FALSE "" "")

#######################################################################
# Cegui
#######################################################################

# Find PCRE
find_package(PCRE)
find_package(Fribidi)


# iconv
set(ICONV_INCLUDE_DIR "${XSILIUM_DEP_DIR}/libiconv/include" "${CMAKE_BINARY_DIR}/Library/Dependencies/Source/libiconv/include" )
set(ICONV_LIBRARIES "iconv")



set(RAPIDXML_H_PATH "${XSILIUM_DEP_DIR}/rapidxml-1.13")
find_package(RapidXML)

find_package(Lua51)
find_package(TOLUAPP)


#Ogre
set(OGRE_FOUND 1)
set(OGRE_INCLUDE_DIR "${OGRE_SOURCE_DIR}/OgreMain/include" "${OGRE_BINARY_DIR}/include" )
set(OGRE_LIBRARIES OgreMain)

#Component
#OGRE_Paging
set(OGRE_Paging_FOUND 1)
set(OGRE_Paging_INCLUDE_DIR "${OGRE_SOURCE_DIR}/Components/Paging/include")
set(OGRE_Paging_LIBRARIES "OgrePaging")

#OGRE_Terrain
set(OGRE_Terrain_FOUND 1)
set(OGRE_Terrain_INCLUDE_DIR "${OGRE_SOURCE_DIR}/Components/Terrain/include")
set(OGRE_Terrain_LIBRARIES "OgreTerrain")

#OGRE_Overlay
set(OGRE_Overlay_FOUND 1)
set(OGRE_Overlay_INCLUDE_DIR "${OGRE_SOURCE_DIR}/Components/Overlay/include")
set(OGRE_Overlay_LIBRARIES "OgreOverlay")

#OGRE_Volume
set(OGRE_Volume_FOUND 1)
set(OGRE_Volume_INCLUDE_DIR "${OGRE_SOURCE_DIR}/Components/Volume/include")
set(OGRE_Volume_LIBRARIES "OgreVolume")

#OGRE_Property
set(OGRE_Property_FOUND 1)
set(OGRE_Property_INCLUDE_DIR "${OGRE_SOURCE_DIR}/Components/Property/include")
set(OGRE_Property_LIBRARIES "OgreProperty")

#OGRE_RTShaderSystem
set(OGRE_RTShaderSystem_FOUND 1)
set(OGRE_RTShaderSystem_INCLUDE_DIR "${OGRE_SOURCE_DIR}/Components/RTShaderSystem/include")
set(OGRE_RTShaderSystem_LIBRARIES "OgreRTShaderSystem")

#OGRE_RenderSystems
set(OGRE_RenderSystems_FOUND 1)
set(OGRE_RenderSystems_INCLUDE_DIR "${OGRE_SOURCE_DIR}/RenderSystems/GL/include")
set(OGRE_RenderSystems_LIBRARIES "RenderSystem_GL")



#######################################################################
# Xsilium dependencies
#######################################################################

# Find OIS
set(OIS_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/ois/includes")
set(OIS_LIBRARIES "OIS")

# Find CEGUI
set(CEGUI_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Library/Cegui/cegui/include" "${CMAKE_BINARY_DIR}/Library/Cegui/cegui/include" ) 

# Find OgrePaged
set(OGREPAGED_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Library/OgrePaged/include")
set(OGREPAGED_LIBRARIES "PagedGeometry")

#find Xsilium
set(XSILIUM_INCLUDE "${CMAKE_SOURCE_DIR}/Engine")
set(XSILIUM_LIBRARY "XsiliumEngine")

#Find Curl
#FIND_PACKAGE(CURL REQUIRED)

#Find Curl
set(CURL_INCLUDE "${CMAKE_SOURCE_DIR}/Library/Curl/include")
set(CURL_LIBRARY "curl")

#Find Librsync
set(RSYNC_INCLUDE "${CMAKE_SOURCE_DIR}/Library/Librsync")
set(RSYNC_LIBRARY "rsync-static")

#Find MD5
set(MD5_INCLUDE "${CMAKE_SOURCE_DIR}/Library/MD5")
set(MD5_LIBRARY "md5")

#Find Binreloc
set(BINRELOC_INCLUDE "${CMAKE_SOURCE_DIR}/Library/Binreloc")
set(BINRELOC_LIBRARY "binreloc")


# Display results, terminate if anything required is missing
MACRO_DISPLAY_FEATURE_LOG()

# Add library and include paths from the dependencies
include_directories(
  ${ZLIB_INCLUDE_DIRS}
  ${ZZip_INCLUDE_DIRS}
  ${FREEIMAGE_INCLUDE_DIRS}
  ${FREETYPE_INCLUDE_DIRS}
  ${OIS_INCLUDE_DIRS}
  ${Cg_INCLUDE_DIRS}
  ${X11_INCLUDE_DIR}
  ${DirectX_INCLUDE_DIRS}
  ${CppUnit_INCLUDE_DIRS}
  ${OGG_INCLUDE_DIRS}
)

link_directories(
  ${Cg_LIBRARY_DIRS}
  ${X11_LIBRARY_DIRS}
  ${DirectX_LIBRARY_DIRS}
  ${CppUnit_LIBRARY_DIRS}
)

if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif ()
