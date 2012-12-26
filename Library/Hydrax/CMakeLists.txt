# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

file(GLOB_RECURSE Hydrax_SOURCES_C src/*.cpp )
file(GLOB_RECURSE Hydrax_SOURCES_H include/*.h )

set(Hydrax_SOURCES
    ${Hydrax_SOURCES_C}
    ${Hydrax_SOURCES_H}
)

include_directories(include)
include_directories(${XSILIUM_OGRE_INCLUDE})

add_library(Hydrax ${Hydrax_SOURCES})
