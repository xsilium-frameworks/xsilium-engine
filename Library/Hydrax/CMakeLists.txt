# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

file(GLOB_RECURSE Hydrax_SOURCES_C src/*.cpp )
file(GLOB_RECURSE Hydrax_SOURCES_H include/*.h )

set(Hydrax_SOURCES
    ${Hydrax_SOURCES_C}
    ${Hydrax_SOURCES_H}
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${XSILIUM_INCLUDE} 
		    ${XSILIUM_FREETYPE_INCLUDE}
)

add_definitions(-DHYDRAX_LIB -D_USRDLL)

link_directories(${CMAKE_BINARY_DIR})

add_library(Hydrax SHARED ${Hydrax_SOURCES})

target_link_libraries(Hydrax ${OGRE_LIB})


set(HYDRAX_H_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE PATH "" FORCE)
set(HYDRAX_LIBRARY "Hydrax" CACHE STRING "" FORCE)
