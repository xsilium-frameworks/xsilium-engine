set( InputManager_H
./InputManager/InputManager.h
)

set( InputManager_S
./InputManager/InputManager.cpp
)

set( Interface_H
./Interface/Interface.h
)

set( Interface_S
./Interface/Interface.cpp
)

set( Network_H
./Network/NetworkListener.h
./Network/NetworkManager.h
)

set( Network_S
./Network/NetworkManager.cpp
)

set( XsiliumEngine_H
./XsiliumFramework.h
)

set( XsiliumEngine_S
./XsiliumFramework.cpp
)

set (CORE_SOURCE_FILES 
${InputManager_S}
${Interface_S}
${Network_S}
${XsiliumEngine_S}
)

set (CORE_HEADER_FILES 
${InputManager_H}
${Interface_H}
${Network_H}
${XsiliumEngine_H}
)


include_directories(
${OGRE_INCLUDE_DIRS} 
${OIS_INCLUDE_DIR} 
${CEGUI_INCLUDE_DIR}
.
)

link_libraries(
${OGRE_LIBRARIES} 
${OIS_LIBRARIES}
${CEGUI_LIBRARY}
enet
)

add_library(XsiliumEngine ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})
