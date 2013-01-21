project(enet)

file(GLOB_RECURSE enet_SOURCES_C src/*.c )
file(GLOB_RECURSE enet_SOURCES_H enet/*.h )

set(enet_SOURCES
    ${enet_SOURCES_C}
    ${enet_SOURCES_H}
)

include_directories(.)

add_library(enet SHARED ${enet_SOURCES})
if(MSVC)
message("Microsoft visual studio")
target_link_libraries( enet ws2_32 winmm)

endif(MSVC)
set(ENET_INCLUDE_DIR "${enet_SOURCE_DIR}" CACHE PATH "" FORCE)
set(ENET_LIBRARY_DBG "enet" CACHE STRING "" FORCE)
set(ENET_LIBRARY_REL "enet" CACHE STRING "" FORCE)
mark_as_advanced(ENET_INCLUDE_DIR ENET_LIBRARY_DBG ENET_LIBRARY_REL)
