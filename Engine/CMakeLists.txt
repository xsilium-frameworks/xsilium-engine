set( CORE_HEADER_FILES
	 ./Callback/Callback.h
	 ./Engine/Engine.h
	 ./Engine/EngineListenner.h
	 ./Event/EventManager.h
	 ./Event/Event.h
	 ./GameState/GameState.h
	 ./GameState/GameStateListener.h
	 ./GameState/GameStateManager.h
	 ./InputManager/InputManager.h	
	 ./Singleton/Singleton.h
)	 




set (CORE_SOURCE_FILES 
	 ./Callback/Callback.cpp
	 ./Engine/Engine.cpp
	 ./Event/EventManager.cpp
	 ./Event/Event.cpp
	 ./GameState/GameStateManager.cpp
	 ./InputManager/InputManager.cpp
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
.
)

link_libraries(
${OGRE_LIBRARIES}
${SKYX_LIBRARY}
${OGRE_Terrain_LIBRARIES}
${HYDRAX_LIBRARY}
${OGREPAGE_LIBRARY}
${OGRE_Paging_LIBRARIES}
CEGUIBase
CEGUIOgreRenderer
${OGRE_Overlay_LIBRARIES}
${ENET_LIBRARY}
${OGRE_RenderSystems_LIBRARIES}
${OIS_LIBRARIES}
"PagedGeometry"
)

#add_dependencies(XsiliumEngine ${OGRE_SAMPLES_LIST})

add_library(XsiliumEngine ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})

if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
	set_source_files_properties(${CORE_SOURCE_FILES} ${CORE_HEADER_FILES}  PROPERTIES COMPILE_FLAGS "-x objective-c++ ")
endif()
