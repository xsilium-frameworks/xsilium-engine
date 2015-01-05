# ---------------------------------------------------------	
cmake_minimum_required(VERSION 2.6)
	
#if (NOT DEFINED CMAKE_MACOSX_RPATH)
#   set(CMAKE_MACOSX_RPATH 0)
#endif()

	
file(GLOB_RECURSE Hydrax_SOURCES_C src/*.cpp )
	
file(GLOB_RECURSE Hydrax_SOURCES_H include/*.h )
		
set(Hydrax_SOURCES	
    ${Hydrax_SOURCES_C}	
    ${Hydrax_SOURCES_H}	
)	
	
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
	
include_directories("${OGRE_INCLUDE_DIR}")	
	
add_definitions(-DHYDRAX_LIB -D_USRDLL)
		
add_library(Hydrax STATIC ${Hydrax_SOURCES})	
	
target_link_libraries(Hydrax ${OGRE_LIBRARIES})		

	
set(HYDRAX_H_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE PATH "" FORCE)	
set(HYDRAX_LIBRARY "Hydrax" CACHE STRING "" FORCE)