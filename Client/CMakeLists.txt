# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

set(CONTENT
	${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Data/datafiles
	${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Data/Media
)
set(TargetName XsiliumClient)

if (APPLE)
	SET(EXETYPE MACOSX_BUNDLE)
	SET_SOURCE_FILES_PROPERTIES( ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/MainMenu.nib  PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
	SET_SOURCE_FILES_PROPERTIES( ${CMAKE_CURRENT_BINARY_DIR}/dist/bin/Info.plist  PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
	SET_SOURCE_FILES_PROPERTIES(${CONTENT} PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
	SET (NibFile ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/MainMenu.nib )
	
endif()

set(CORE_SOURCE_FILES
    main.cpp
    XsiliumApp.cpp
    Shared/Compte/Compte.cpp
    Login/LoginState.cpp 
    Interface/GuiChat.cpp
    Game/Chat/GestionnaireChat/GestionnaireChat.cpp
    Interface/GuiErreur.cpp
    Interface/GuiProgression.cpp
    Interface/GuiLogin.cpp
    Login/Authentification/GestionnaireAuth.cpp
    Game/GestionnaireMeteo/GestionnaireMeteo.cpp
    Game/GestionnaireMeteo/HydraxRttListener/HydraxRttListener.cpp
    Game/JeuxState.cpp
)

set(CORE_HEADER_FILES
    XsiliumApp.h 
    Login/LoginState.h
    Shared/Compte/Compte.h
    Interface/GuiChat.h
    Game/Chat/StructurePacket/PacketChat.h
    Game/Chat/GestionnaireChat/GestionnaireChat.h
    Login/Authentification/GestionnaireAuth.h
    Interface/GuiErreur.h
    Interface/GuiProgression.h
    Interface/GuiLogin.h
    Login/ListOfMessage/ListOfMessage.h
    Game/GestionnaireMeteo/GestionnaireMeteo.h
    Game/GestionnaireMeteo/HydraxRttListener/HydraxRttListener.h
    Game/JeuxState.h
)

if(WIN32)

	source_group(Main\\Source FILES ${CORE_SOURCE_FILES})
	source_group(Main\\Header FILES ${CORE_HEADER_FILES})

	source_group(Datafiles FILES ${CONTENT})
endif()

if (APPLE)
	
	set(CMAKE_CXX_FLAGS "-x objective-c++")
	list(APPEND CORE_SOURCE_FILES "SDK/OSX/XsiliumApp.mm")

endif()

 set(SRC  
	${CORE_SOURCE_FILES} 
	${CORE_HEADER_FILES}
	)

include_directories(
${XSILIUM_INCLUDE}
${ENET_INCLUDE_DIR} 
${CEGUI_INCLUDE_DIR}
${CEGUI_BASE_LIBNAME}
${OGRE_INCLUDE_DIR}
${RAPIDXML_INCLUDE_DIR}
${OGRE_Overlay_INCLUDE_DIR}
${SKYX_H_PATH}
${HYDRAX_H_PATH}
${OGRE_Terrain_INCLUDE_DIR}
${OGRE_RenderSystems_INCLUDE_DIR}
Login
Game
Shared
.
)

link_libraries(
	${XSILIUM_LIBRARY}
	${ENET_LIBRARY}
	${OGRE_LIBRARIES}
	${OGRE_Overlay_LIBRARIES}
	${SKYX_LIBRARY}
	${HYDRAX_LIBRARY}
	${OGRE_Terrain_LIBRARIES}
	${OGRE_RenderSystems_LIBRARIES}
	${OIS_LIBRARIES}
)

if (APPLE)

	xsilium_add_executable(
		${TargetName} 
		MACOSX_BUNDLE
		${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/MainMenu.nib
		${SRC} 
		${CONTENT}
	)
	SET(XSILIUM_APPS "${CMAKE_CURRENT_BINARY_DIR}/${TargetName}.app")
	if(NOT CMAKE_GENERATOR STREQUAL Xcode)
		add_custom_command(TARGET ${TargetName} POST_BUILD
		COMMAND mkdir ARGS -p ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/configKey.xml ${XSILIUM_APPS}/Contents/Resources
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/Ogre.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/OgreTerrain.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/OgrePaging.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/RenderSystem_GL.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/Plugin_ParticleFX.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/Plugin_BSPSceneManager.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/Plugin_CgProgramManager.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/Plugin_PCZSceneManager.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/Plugin_OctreeZone.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/macosx/Plugin_OctreeSceneManager.framework ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/libCEGUIExpatParser.dylib ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/libCEGUICoreWindowRendererSet.dylib ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/libCEGUIBase.dylib ${XSILIUM_APPS}/Contents/Frameworks
		COMMAND cp ARGS -r ${XSILIUM_BINARY_DIR}/lib/libCEGUIOgreRenderer.dylib ${XSILIUM_APPS}/Contents/Frameworks
		
		)
	endif()

	if (NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
		set_target_properties(XsiliumClient PROPERTIES LINK_FLAGS "-framework IOKit -framework Cocoa -framework Carbon -framework OpenGL -framework CoreVideo ")
	endif()

else ()

	xsilium_add_executable(${TargetName} ${SRC})

endif()



