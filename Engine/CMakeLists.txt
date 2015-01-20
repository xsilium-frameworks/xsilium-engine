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
	 ./Graphics/GraphicsMouvementManager.h
	 ./Graphics/GraphicsObjet.h
	 ./Graphics/GraphicsObjetManager.h
	 ./Graphics/GraphicsSky.h
	 ./Graphics/GraphicsWater.h
	 ./Graphics/GraphicsSceneLoader.h
	 ./Gui/GuiManager.h
	 ./Gui/GuiInput.h
	 ./Gui/GuiListenner.h
	 ./Input/InputManager.h
 	 ./Input/KeyboardManager.h	
	 ./Input/KeyboardMap.h
	 ./Logging/LogManager.h
	 ./Network/Opcode/Opcode.h
	 ./Network/NetworkListener.h
	 ./Network/NetworkManager.h
	 ./Network/MessagePacket.h
	 ./Singleton/Singleton.h
  	 ./Physics/PhysicsConvert.h
  	 ./Physics/PhysicsDebugDrawer.h
  	 ./Physics/PhysicsDynamicLines.h
  	 ./Physics/PhysicsDynamicRenderable.h
  	 ./Physics/PhysicsEntite.h
  	 ./Physics/PhysicsManager.h
  	 ./Physics/PhysicsMotionState.h
)	 




set (CORE_SOURCE_FILES 
	 ./Callback/Callback.cpp
	 ./Engine/Engine.cpp
	 ./Event/EventManager.cpp
	 ./Event/Event.cpp
	 ./GameState/GameStateManager.cpp
	 ./Graphics/GraphicsAnimation.cpp
	 ./Graphics/GraphicsCamera.cpp
	 ./Graphics/GraphicsEntite.cpp
	 ./Graphics/GraphicsEntiteManager.cpp
	 ./Graphics/GraphicsHydraxRttListener.cpp
	 ./Graphics/GraphicsManager.cpp
	 ./Graphics/GraphicsMouvementManager.cpp
	 ./Graphics/GraphicsObjet.cpp
	 ./Graphics/GraphicsObjetManager.cpp
 	 ./Graphics/GraphicsSceneLoader.cpp
	 ./Graphics/GraphicsSky.cpp
	 ./Graphics/GraphicsWater.cpp
 	 ./Gui/GuiManager.cpp
 	 ./Gui/GuiInput.cpp
 	 ./Gui/GuiListenner.cpp
	 ./Input/InputManager.cpp
	 ./Input/KeyboardManager.cpp
	 ./Input/KeyboardMap.cpp
	 ./Logging/LogManager.cpp
	 ./Network/NetworkListener.cpp
	 ./Network/NetworkManager.cpp
 	 ./Network/MessagePacket.cpp
 	 ./Physics/PhysicsConvert.cpp
  	 ./Physics/PhysicsDebugDrawer.cpp
  	 ./Physics/PhysicsDynamicLines.cpp
  	 ./Physics/PhysicsDynamicRenderable.cpp
  	 ./Physics/PhysicsEntite.cpp
  	 ./Physics/PhysicsManager.cpp
  	 ./Physics/PhysicsMotionState.cpp
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
${BULLET_INCLUDE_DIRS}
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
${BULLET_LIBRARIES}
)

#add_dependencies(XsiliumEngine ${OGRE_SAMPLES_LIST})

add_library(XsiliumEngine ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})

if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
	set_source_files_properties(${CORE_SOURCE_FILES} ${CORE_HEADER_FILES}  PROPERTIES COMPILE_FLAGS "-x objective-c++ ")
endif()
