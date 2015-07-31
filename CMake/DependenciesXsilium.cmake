#######################################################################
# Additional features
#######################################################################

#######################################################################
# Core dependencies
#######################################################################

# Find zlib
set(ZLIB_H_PATH "${XSILIUM_DEP_DIR}/ZLib" )

# Find ZZIP
set(ZZIP_H_PATH "${XSILIUM_DEP_DIR}/ZZipLib" )

# Find FreeImage
set(FREEIMAGE_H_PATH "${XSILIUM_DEP_DIR}/FreeImage/Source")
set(FREEIMAGE_LIB_STATIC "FreeImage" )
set(FREEIMAGE_LIB_STATIC_DBG "FreeImage" )
set(FREEIMAGE_LIB "FreeImage" )
set(FREEIMAGE_LIB_DBG "FreeImage" )

# Find FreeType
set(FREETYPE_H_PATH_ft2build "${XSILIUM_DEP_DIR}/Freetype/include")
set(FREETYPE_H_PATH_ftconfig "${XSILIUM_DEP_DIR}/Freetype/include")
set(FREETYPE_LIB_STATIC "freetype")
set(FREETYPE_LIB_STATIC_DBG "freetype")

# Find Rapidxml
set(RAPIDXML_H_PATH "${XSILIUM_DEP_DIR}/Rapidxml")

# Find OIS
set(OIS_H_PATH "${XSILIUM_DEP_DIR}/ois/includes")
set(OIS_LIB "OIS")


#Ogre
set(OGRE_INCLUDE_DIRS "${XSILIUM_SOURCE_DIR}/Library/Ogre/OgreMain/include" "${XSILIUM_BINARY_DIR}/Library/Ogre/include" )
set(OGRE_LIBRARIES OgreMain)

set(OGRE_H_PATH "${XSILIUM_SOURCE_DIR}/Library/Ogre/OgreMain/include")
set(OGRE_LIB "OgreMain")
set(OGRE_H_BUILD_SETTINGS_PATH "${XSILIUM_BINARY_DIR}/Library/Ogre/include" )

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
        set(OGRE_BOOST_COMPONENTS thread date_time system atomic chrono serialization log)
    else()
        set(OGRE_BOOST_COMPONENTS thread date_time system chrono serialization log)
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

#CEGUI
set(CEGUI_FOUND 1)
set(CEGUI_INCLUDE_DIRS "${XSILIUM_SOURCE_DIR}/Library/Cegui/cegui/include" "${XSILIUM_BINARY_DIR}/Library/Cegui/cegui/include")
set(CEGUI_LIBRARIES "CEGUIBase-0")

# Find DirectX
if(WIN32)
	find_package(DirectX)
	macro_log_feature(DirectX9_FOUND "DirectX9" "Support for the DirectX render system" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")

	find_package(DirectX11)
	macro_log_feature(DirectX11_FOUND "DirectX11" "Support for the DirectX11 render system" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")
	
	find_package(DirectXInput)
 	macro_log_feature(Direct_FOUND "DirectInput/XInput" "Support for the DirectInput/XInput" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")

endif()

