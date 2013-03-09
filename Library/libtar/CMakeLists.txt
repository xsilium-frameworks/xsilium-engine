project(libtar)

file(GLOB_RECURSE libtar_SOURCES_C src/*.c )
file(GLOB_RECURSE libtar_SOURCES_H include/*.h )

set(libtar_SOURCES
    ${libtar_SOURCES_C}
    ${libtar_SOURCES_H}
)

include_directories(include)

add_library(tar STATIC ${libtar_SOURCES})

set(LIBTAR_INCLUDE_DIR "${libtar_SOURCES_H}" CACHE PATH "" FORCE)
set(LIBTAR_LIBRARY_DBG "tar" CACHE STRING "" FORCE)
set(LIBTAR_LIBRARY_REL "tar" CACHE STRING "" FORCE)
mark_as_advanced(LIBTAR_INCLUDE_DIR LIBTAR_LIBRARY_DBG LIBTAR_LIBRARY_REL)
