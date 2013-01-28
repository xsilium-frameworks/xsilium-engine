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

set( GameState_H
./GameState/GameStateManager.h
./GameState/GameState.h
)

set( GameState_S
./GameState/GameStateManager.cpp
)

set( SceneLoader_S
./DotSceneLoader/DotSceneLoader.cpp
)

set( SceneLoader_H
./DotSceneLoader/DotSceneLoader.h
./DotSceneLoader/rapidxml.h
)

set( Camera_H
./Camera/SdkCameraMan.h
)

set (CORE_SOURCE_FILES 
${InputManager_S}
${Interface_S}
${Network_S}
${XsiliumEngine_S}
${GameState_S}
${SceneLoader_S}
)

set (CORE_HEADER_FILES 
${InputManager_H}
${Interface_H}
${Network_H}
${XsiliumEngine_H}
${GameState_H}
${SceneLoader_H}
${Camera_H}
)


include_directories(
${XSILIUM_INCLUDE}
.
)

link_libraries(
${XSILIUM_LIB}
${CEGUI_LIBRARY}
${ENET_LIBRARY_REL}
)

add_library(XsiliumEngine ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})
