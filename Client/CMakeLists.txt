# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

set(CONTENT
	${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Data/datafiles
	${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Data/Media
	${CMAKE_CURRENT_BINARY_DIR}/dist/bin/plugins.cfg
	${CMAKE_CURRENT_BINARY_DIR}/dist/bin/resources.cfg
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
Login
Game
Shared
.
)

link_libraries(
	${XSILIUM_LIB}
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

else ()

	xsilium_add_executable(${TargetName} ${SRC})

endif()



