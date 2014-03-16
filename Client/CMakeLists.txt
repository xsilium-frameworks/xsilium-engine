# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

set(CONTENT
	${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Data/datafiles
	${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Data/Media
	${CMAKE_CURRENT_BINARY_DIR}/dist/bin/plugins.cfg
	${CMAKE_CURRENT_BINARY_DIR}/dist/bin/resources.cfg
#    ${CMAKE_CURRENT_BINARY_DIR}/dist/bin/configKey.xml
)
set(TargetName XsiliumClient)

if (APPLE)
	SET(EXETYPE MACOSX_BUNDLE)
	SET_SOURCE_FILES_PROPERTIES( ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/MainMenu.nib  PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
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

if (APPLE AND CMAKE_OSX_ARCHITECTURES MATCHES "x86_64" )
	
	set(CMAKE_CXX_FLAGS "-x objective-c++")
	list(APPEND CORE_SOURCE_FILES "SDK/OSX/XsiliumApp.mm")

endif()

 set(SRC 
	${CONTENT} 
	${CORE_SOURCE_FILES}  ${CORE_HEADER_FILES}
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
	)

else ()

	xsilium_add_executable(${TargetName} ${SRC})
	
	
#	IF (NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
#		ADD_CUSTOM_COMMAND(
#			TARGET ${TargetName} 
#			POST_BUILD
#			COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/Maps.blend ${CMAKE_CURRENT_BINARY_DIR}/Maps.blend
#			COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/Momo.blend ${CMAKE_CURRENT_BINARY_DIR}/Momo.blend
#			COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/Rat.blend ${CMAKE_CURRENT_BINARY_DIR}/Rat.blend
#		)
#	ENDIF ()

endif()

