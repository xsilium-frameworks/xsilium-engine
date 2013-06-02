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
)

set( Camera_H
./Camera/SdkCameraMan.h
)

set( Keyboard_H
./KeyboardMap/KeyboardMap.h
)

set( Keyboard_S
./KeyboardMap/KeyboardMap.cpp
)

#set( Rapidxml_H
#./rapidxml/rapidxml.h
#./rapidxml/rapidxml_print.h
#)

set( EventManager_H
./EventManager/EventManager.h
./EventManager/Event/Event.h
)

set( EventManager_S
./EventManager/EventManager.cpp
./EventManager/Event/Event.cpp
)

set( Entite_H
./Entite/Entite.h
./Entite/Perso/Personnage.h
./Entite/GestionnaireAnimation/Animation.h
#./Entite/Perso/GestionnaireMouvement/MouvementPersonnage.h

)

set( Entite_S
./Entite/Entite.cpp
./Entite/Perso/Personnage.cpp
./Entite/GestionnaireAnimation/Animation.cpp
#./Entite/Perso/GestionnaireMouvement/MouvementPersonnage.cpp
)


set (CORE_SOURCE_FILES 
${InputManager_S}
${Interface_S}
${Network_S}
${XsiliumEngine_S}
${GameState_S}
${SceneLoader_S}
${Keyboard_S}
${EventManager_S}
${Entite_S}
)

set (CORE_HEADER_FILES 
${InputManager_H}
${Interface_H}
${Network_H}
${XsiliumEngine_H}
${GameState_H}
${SceneLoader_H}
${Camera_H}
${Keyboard_H}
${Rapidxml_H}
${EventManager_H}
${Entite_H}
)


include_directories(
${XSILIUM_INCLUDE}
.
)

link_libraries(
${XSILIUM_LIB}
${ENET_LIBRARY_REL}
)

add_library(XsiliumEngine ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})

if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
	set_source_files_properties(${CORE_SOURCE_FILES} ${CORE_HEADER_FILES}  PROPERTIES COMPILE_FLAGS "-x objective-c++ ")
endif()
