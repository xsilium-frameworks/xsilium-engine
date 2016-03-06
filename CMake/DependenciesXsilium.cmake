#######################################################################
# Find all necessary for project Xsilium
#######################################################################
include(FindPkgMacros)

#######################################################################
# Ogre Core dependencies
#######################################################################

# Find zlib
set(ZLIB_FOUND 1)
set(ZLIB_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/ZLib" )
set(ZLIB_LIBRARIES "ZLib")

# Find ZZIP
set(ZZip_FOUND 1)
set(ZZip_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/ZZipLib" )
set(ZZip_LIBRARIES "ZZipLib")


# Find FreeImage
set(FREEIMAGE_FOUND 1)
set(FREEIMAGE_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/FreeImage/Source")
set(FREEIMAGE_LIBRARIES "FreeImage" )
set(FreeImage_LIBRARIES "FreeImage" )
set( FREEIMAGE_DEFINITIONS_DYNAMIC "FREEIMAGE_EXPORTS" CACHE STRING "preprocessor definitions" )

# Find FreeType
set(FREETYPE_FOUND 1)
set(FREETYPE_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/Freetype/include" "${XSILIUM_DEP_DIR}/Freetype/include/freetype")
set(FREETYPE_LIBRARIES "freetype")

# Find X11
if (UNIX AND NOT APPLE AND NOT ANDROID AND NOT FLASHCC)
  find_package(X11)
  macro_log_feature(X11_FOUND "X11" "X Window system" "http://www.x.org" TRUE "" "")
  macro_log_feature(X11_Xt_FOUND "Xt" "X Toolkit" "http://www.x.org" TRUE "" "")
  find_library(XAW_LIBRARY NAMES Xaw Xaw7 PATHS ${OGRE_DEP_SEARCH_PATH} ${DEP_LIB_SEARCH_DIR} ${X11_LIB_SEARCH_PATH})
  macro_log_feature(XAW_LIBRARY "Xaw" "X11 Athena widget set" "http://www.x.org" TRUE "" "")
  mark_as_advanced(XAW_LIBRARY)
endif ()

# Find Boost
# Prefer static linking in all cases
if (WIN32)
	set(Boost_USE_STATIC_LIBS TRUE)
	set(boost_DIR "C:/boost")
else ()
	# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
	set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
endif ()
if (APPLE AND OGRE_BUILD_PLATFORM_APPLE_IOS)
    set(Boost_USE_MULTITHREADED OFF)
endif()
set(Boost_ADDITIONAL_VERSIONS "1.57" "1.57.0" "1.56" "1.56.0" "1.55" "1.55.0" "1.54" "1.54.0" "1.53" "1.53.0" "1.52" "1.52.0" "1.51" "1.51.0" "1.50" "1.50.0" "1.49" "1.49.0" "1.48" "1.48.0" "1.47" "1.47.0" "1.46" "1.46.0" "1.45" "1.45.0" "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40")
# Components that need linking (NB does not include header-only components like bind)
set(OGRE_BOOST_COMPONENTS thread date_time)
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
        set(OGRE_BOOST_COMPONENTS thread date_time system atomic chrono filesystem log log_setup serialization)
    else()
        set(OGRE_BOOST_COMPONENTS thread date_time system chrono filesystem serialization)
    endif()
    find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
endif()

if(Boost_VERSION GREATER 105200)
	# Use boost threading version 4 for boost 1.53 and above
	add_definitions( -DBOOST_THREAD_VERSION=4 )
endif()

if(Boost_FOUND AND NOT WIN32)
  list(REMOVE_DUPLICATES Boost_LIBRARIES)
endif()

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
	macro_log_feature(DirectX_FOUND "DirectX" "Support for the DirectXInput render system" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")
endif()

#######################################################################
# Additional features
#######################################################################
# Find Cg
if (NOT (OGRE_BUILD_PLATFORM_APPLE_IOS OR OGRE_BUILD_PLATFORM_WINRT OR ANDROID OR FLASHCC))
	if (WIN32)
		set(Cg_FOUND 1)
		set(Cg_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/Cg/include" )
		if (OGRE_PLATFORM_X64)
			set(Cg_LIBRARIES "${XSILIUM_DEP_DIR}/Cg/lib64/cg.lib")
		else ()
			set(Cg_LIBRARIES "${XSILIUM_DEP_DIR}/Cg/lib/cg.lib")
		endif()
	else ()
  		find_package(Cg)
  		macro_log_feature(Cg_FOUND "cg" "C for graphics shader language" "http://developer.nvidia.com/object/cg_toolkit.html" FALSE "" "")

	endif()
endif ()


# Find OIS
set(OIS_FOUND 1)
set(OIS_INCLUDE_DIRS "${XSILIUM_DEP_DIR}/ois/includes")
set(OIS_LIBRARIES "OIS")


#######################################################################
# Cegui Core dependencies
#######################################################################

# Find Iconv
set(ICONV_FOUND 1)
set (ICONV_INCLUDE_DIR "${XSILIUM_DEP_DIR}/Iconv/include")
set (ICONV_LIBRARIES "iconv")

# Find Rapidxml
set(RAPIDXML_FOUND 1)
set(RAPIDXML_INCLUDE_DIR "${XSILIUM_DEP_DIR}/Rapidxml")

#Ogre
set(OGRE_FOUND 1)
set(OGRE_INCLUDE_DIRS "${XSILIUM_SOURCE_DIR}/Library/Ogre/OgreMain/include" "${XSILIUM_BINARY_DIR}/Library/Ogre/include" )
set(OGRE_LIBRARIES OgreMain)

file (STRINGS "${XSILIUM_SOURCE_DIR}/Library/Ogre/OgreMain/include/OgrePrerequisites.h" _CEGUIOGREVERSIONDEFINES REGEX ".*#define OGRE_VERSION_.*[0-9]+")
foreach (ver MAJOR MINOR PATCH)
	set (CEGUI_FOUND_OGRE_VERSION_${ver} 0)
        if ("${_CEGUIOGREVERSIONDEFINES}" MATCHES ".*#define OGRE_VERSION_${ver} ([0-9]+).*")
            set (CEGUI_FOUND_OGRE_VERSION_${ver} "${CMAKE_MATCH_1}")
        endif()
endforeach()


#Component
#OGRE_Paging
set(OGRE_Paging_FOUND 1)
set(OGRE_Paging_INCLUDE_DIR "${XSILIUM_SOURCE_DIR}/Library/Ogre/Components/Paging/include")
set(OGRE_Paging_LIBRARIES "OgrePaging")

#OGRE_Terrain
set(OGRE_Terrain_FOUND 1)
set(OGRE_Terrain_INCLUDE_DIR "${XSILIUM_SOURCE_DIR}/Library/Ogre/Components/Terrain/include")
set(OGRE_Terrain_LIBRARIES "OgreTerrain")

#OGRE_Overlay
set(OGRE_Overlay_FOUND 1)
set(OGRE_Overlay_INCLUDE_DIR "${XSILIUM_SOURCE_DIR}/Library/Ogre/Components/Overlay/include")
set(OGRE_Overlay_LIBRARIES "OgreOverlay")

#OGRE_Volume
set(OGRE_Volume_FOUND 1)
set(OGRE_Volume_INCLUDE_DIR "${XSILIUM_SOURCE_DIR}/Library/Ogre/Components/Volume/include")
set(OGRE_Volume_LIBRARIES "OgreVolume")

#OGRE_Property
set(OGRE_Property_FOUND 1)
set(OGRE_Property_INCLUDE_DIR "${XSILIUM_SOURCE_DIR}/Library/Ogre/Components/Property/include")
set(OGRE_Property_LIBRARIES "OgreProperty")

#OGRE_RTShaderSystem
set(OGRE_RTShaderSystem_FOUND 1)
set(OGRE_RTShaderSystem_INCLUDE_DIR "${XSILIUM_SOURCE_DIR}/Library/Ogre/Components/RTShaderSystem/include")
set(OGRE_RTShaderSystem_LIBRARIES "OgreRTShaderSystem")

#OGRE_RenderSystems
set(OGRE_RenderSystems_FOUND 1)
set(OGRE_RenderSystems_INCLUDE_DIR "${XSILIUM_SOURCE_DIR}/Library/Ogre/RenderSystems/GL/include")
set(OGRE_RenderSystems_LIBRARIES "RenderSystem_GL")

#CEGUI
set(CEGUI_FOUND 1)
set(CEGUI_INCLUDE_DIRS "${XSILIUM_SOURCE_DIR}/Library/Cegui/cegui/include" "${XSILIUM_BINARY_DIR}/Library/Cegui/cegui/include")
set(CEGUI_LIBRARIES "CEGUIBase-0")

