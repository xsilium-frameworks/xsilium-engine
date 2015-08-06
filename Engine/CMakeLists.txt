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
	 ./Graphics/GraphicsMeteoManager.cpp
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
${Boost_INCLUDE_DIRS}
${OGRE_INCLUDE_DIRS}
${OIS_INCLUDE_DIR}
${SKYX_H_PATH}
${BULLET_INCLUDE_DIRS}
${HYDRAX_H_PATH}
${CEGUI_INCLUDE_DIRS}
${OGRE_Terrain_INCLUDE_DIR}
${PagedGeometry_INCLUDE_DIRS}
${RAPIDXML_INCLUDE_DIR}
${ENET_INCLUDE_DIR}
.
)

ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)

add_library(XsiliumEngine ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})

if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
	set_source_files_properties(${CORE_SOURCE_FILES} ${CORE_HEADER_FILES}  PROPERTIES COMPILE_FLAGS "-x objective-c++ ")
	set_target_properties(XsiliumEngine PROPERTIES LINK_FLAGS "-framework IOKit -framework Cocoa -framework Carbon")
endif()

set(XSILIUM_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "" FORCE)
set(XSILIUM_LIBRARY "XsiliumEngine" CACHE STRING "" FORCE)
mark_as_advanced(XSILIUM_INCLUDE XSILIUM_LIBRARY)
