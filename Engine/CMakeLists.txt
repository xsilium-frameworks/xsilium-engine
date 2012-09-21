set( InputManager_H
./InputManager/InputManager.h
)

set( InputManager_S
./InputManager/InputManager.cpp
)

set (CORE_SOURCE_FILES 
${InputManager_S}
)

set (CORE_HEADER_FILES 
${InputManager_H}
)


include_directories(
InputManager/
)

include_directories(${OGRE_INCLUDE_DIRS} ${OIS_INCLUDE_DIR})

link_libraries(
${OGRE_LIBRARIES} 
${OIS_LIBRARIES}
)

add_library(XsiliumEngine ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})
