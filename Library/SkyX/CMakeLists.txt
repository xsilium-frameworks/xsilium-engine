#-------------------------------------------------------------------
# This file is part of the CMake build system for SkyX
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

############################################################
# SkyX core library
############################################################

# define header and source files for the library
set (SKYX_HEADER_FILES
  Include/AtmosphereManager.h
  Include/BasicController.h
  Include/CloudsManager.h
  Include/ColorGradient.h
  Include/Controller.h
  Include/GPUManager.h
  Include/MeshManager.h
  Include/MoonManager.h
  Include/Prerequisites.h
  Include/SkyX.h
  Include/VCloudsManager.h
)

set (SKYX_SOURCE_FILES
  Source/AtmosphereManager.cpp
  Source/BasicController.cpp
  Source/CloudsManager.cpp
  Source/ColorGradient.cpp
  Source/GPUManager.cpp
  Source/MeshManager.cpp
  Source/MoonManager.cpp
  Source/SkyX.cpp
  Source/VCloudsManager.cpp
)

set (VCLOUDS_HEADER_FILES
  Include/VClouds/DataManager.h
  Include/VClouds/Ellipsoid.h
  Include/VClouds/FastFakeRandom.h
  Include/VClouds/GeometryBlock.h
  Include/VClouds/GeometryManager.h
  Include/VClouds/Lightning.h
  Include/VClouds/LightningManager.h
  Include/VClouds/VClouds.h
)

set (VCLOUDS_SOURCE_FILES
  Source/VClouds/DataManager.cpp
  Source/VClouds/Ellipsoid.cpp
  Source/VClouds/FastFakeRandom.cpp
  Source/VClouds/GeometryBlock.cpp
  Source/VClouds/GeometryManager.cpp
  Source/VClouds/Lightning.cpp
  Source/VClouds/LightningManager.cpp
  Source/VClouds/VClouds.cpp
)


# Create files groups for IDE.
source_group(Header\ Files\\VClouds FILES ${VCLOUDS_HEADER_FILES})
source_group(Source\ Files\\VClouds FILES ${VCLOUDS_SOURCE_FILES})

# Add include directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Include")
include_directories("${OGRE_INCLUDE_DIR}")


# Add needed definitions and nedmalloc include dir
add_definitions(-DSKYX_LIB -D_USRDLL)

if (UNIX)
  set(PLATFORM_LIBS dl)
endif()

# setup SkyX target
add_library(SkyX STATIC
  ${SKYX_HEADER_FILES}
  ${SKYX_SOURCE_FILES}
  ${VCLOUDS_HEADER_FILES}
  ${VCLOUDS_SOURCE_FILES}
)

target_link_libraries(SkyX ${OGRE_LIBRARIES})

set(SKYX_H_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Include" CACHE PATH "" FORCE)

set(SKYX_LIBRARY "SkyX" CACHE STRING "" FORCE)
