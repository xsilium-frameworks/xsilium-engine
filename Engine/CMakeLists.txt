set( CORE_HEADER_FILES
	 ./Callback/Callback.h
	 ./Engine/Engine.h
	 ./Engine/EngineListenner.h
	 ./Event/EventManager.h
	 ./Event/Event.h
	 ./GameState/GameState.h
	 ./GameState/GameStateListener.h
	 ./GameState/GameStateManager.h
	 ./Graphics/GraphicsAnimation.h
	 ./Graphics/GraphicsCamera.h
	 ./Graphics/GraphicsEntiteManager.h
	 ./Graphics/GraphicsEntite.h
	 ./Graphics/GraphicsHydraxRttListener.h
	 ./Graphics/GraphicsManager.h
	 ./Graphics/GraphicsMeteoManager.h
	 ./Graphics/GraphicsObjet.h
	 ./Graphics/GraphicsObjetManager.h
	 ./Graphics/GraphicsSceneLoader.h
	 ./Gui/GuiManager.h
	 ./Input/InputManager.h	
	 ./Input/KeyboardMap.h
	 ./Input/InputGui.h
	 ./Network/Opcode/Opcode.h
	 ./Network/StructurePacket/StructureGeneral.h
	 ./Network/NetworkListener.h
	 ./Network/NetworkManager.h
	 ./Singleton/Singleton.h
)	 




set (CORE_SOURCE_FILES 
	 ./Callback/Callback.cpp
	 ./Engine/Engine.cpp
	 ./Event/EventManager.cpp
	 ./Event/Event.cpp
	 ./GameState/GameStateManager.cpp
	 ./Graphics/GraphicsAnimation.cpp
	 ./Graphics/GraphicsEntite.cpp
	 ./Graphics/GraphicsEntiteManager.cpp
	 ./Graphics/GraphicsHydraxRttListener.cpp
	 ./Graphics/GraphicsManager.cpp
	 ./Graphics/GraphicsMeteoManager.cpp
	 ./Graphics/GraphicsObjet.cpp
	 ./Graphics/GraphicsObjetManager.cpp
 	 ./Graphics/GraphicsSceneLoader.cpp
 	 ./Gui/GuiManager.cpp
	 ./Input/InputManager.cpp
	 ./Input/InputGui.cpp
	 ./Input/KeyboardMap.cpp
	 ./Network/NetworkListener.cpp
	 ./Network/NetworkManager.cpp
)

include_directories(
${OGRE_INCLUDE_DIR}
${RAPIDXML_INCLUDE_DIR}
${SKYX_H_PATH}
${OGRE_Terrain_INCLUDE_DIR}
${HYDRAX_H_PATH}
${OGREPAGE_H_PATH}
${OGRE_Paging_INCLUDE_DIR}
${CEGUI_INCLUDE_DIR}
${OGRE_Overlay_INCLUDE_DIR}
${ENET_INCLUDE_DIR}
${OGRE_RenderSystems_INCLUDE_DIR}
${OGREPAGED_INCLUDE_DIRS}
.
)

link_libraries(
${OGRE_LIBRARIES}
${SKYX_LIBRARY}
${OGRE_Terrain_LIBRARIES}
${HYDRAX_LIBRARY}
${OGREPAGE_LIBRARY}
${OGRE_Paging_LIBRARIES}
CEGUIBase-0
CEGUIOgreRenderer-0
${OGRE_Overlay_LIBRARIES}
${ENET_LIBRARY}
${OGRE_RenderSystems_LIBRARIES}
${OIS_LIBRARIES}
${OGREPAGED_LIBRARIES}
)

#add_dependencies(XsiliumEngine ${OGRE_SAMPLES_LIST})

add_library(XsiliumEngine ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})

if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
	set_source_files_properties(${CORE_SOURCE_FILES} ${CORE_HEADER_FILES}  PROPERTIES COMPILE_FLAGS "-x objective-c++ ")
endif()
