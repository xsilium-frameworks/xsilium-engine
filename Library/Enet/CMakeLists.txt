project(enet)

file(GLOB_RECURSE enet_SOURCES_C src/*.c )
file(GLOB_RECURSE enet_SOURCES_H enet/*.h )

set(enet_SOURCES
    ${enet_SOURCES_C}
    ${enet_SOURCES_H}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(enet STATIC ${enet_SOURCES})
if(WIN32)
	target_link_libraries( enet ws2_32 winmm)
endif(WIN32)

set(ENET_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "" FORCE)
set(ENET_LIBRARY "enet" CACHE STRING "" FORCE)
mark_as_advanced(ENET_INCLUDE_DIR ENET_LIBRARY)
