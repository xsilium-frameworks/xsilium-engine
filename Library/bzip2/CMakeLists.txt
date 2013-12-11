project(bzip2)

file(GLOB_RECURSE bzip2_SOURCES_C src/*.c )
file(GLOB_RECURSE bzip2_SOURCES_H include/*.h )

set(bzip2_SOURCES
    ${bzip2_SOURCES_C}
    ${bzip2_SOURCES_H}
)

include_directories(include)

add_library(bzip2 STATIC ${bzip2_SOURCES})

set(BZIP2_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/" CACHE PATH "" FORCE)
set(BZIP2_LIBRARY_DBG "bzip2" CACHE STRING "" FORCE)
set(BZIP2_LIBRARY_REL "bzip2" CACHE STRING "" FORCE)
mark_as_advanced(BZIP2_INCLUDE_DIR BZIP2_LIBRARY_DBG BZIP2_LIBRARY_REL)
