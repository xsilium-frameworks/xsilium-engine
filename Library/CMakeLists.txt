add_subdirectory(Dependencies)
add_subdirectory(Enet)
add_subdirectory(Bullet)

find_package(Boost)

add_subdirectory(Ogre)

add_dependencies( OgreMain FreeImage freetype OIS pcre zlib zziplib)

find_package(OGRE)

set(FREETYPE_H_PATH_ft2build ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Source/freetype/include)

include_directories(${FREETYPE_H_PATH_ft2build})

set(PCRE_H_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Source/pcre;${CMAKE_BINARY_DIR}/Library/Dependencies/Source/pcre")

include_directories(${PCRE_H_PATH})

set(OGRE_H_PATH "${OGRE_INCLUDE_DIRS}")
set(OGRE_LIB "${OGRE_LIBRARIES}")



add_subdirectory(Cegui)

add_dependencies( CEGUIBase OgreMain )


