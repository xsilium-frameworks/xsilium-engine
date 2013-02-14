include_directories(${XSILIUM_INCLUDE})

if (UNIX)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/bin/datafiles
		DESTINATION ./
		CONFIGURATIONS All
	)
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION ./
		CONFIGURATIONS All
	)
endif(UNIX)

set(CORE_SOURCE_FILES
    main.cpp
    Login/UI/LoginState.cpp 
    XsiliumApp.cpp
    Console/Console.cpp
    Login/Authentification.cpp
    Game/GestionnaireMeteo/GestionnaireMeteo.cpp
    Game/GestionnaireMeteo/HydraxRttListener/HydraxRttListener.cpp
    Game/JeuxState.cpp
)

set(CORE_HEADER_FILES
    Login/UI/LoginState.h
    XsiliumApp.h 
    Console/Console.h
    Login/Authentification.h
    Login/ListOfMessage/ListOfMessage.h
    Game/GestionnaireMeteo/GestionnaireMeteo.h
    Game/GestionnaireMeteo/HydraxRttListener/HydraxRttListener.h
    Game/JeuxState.h
)

include_directories(
${XSILIUM_INCLUDE} 
Console 
Login
Game
.
)


link_libraries(
${XSILIUM_LIB} ${SKYX_LIBRARIES}
)

    add_executable(XsiliumClient
		   ${CORE_SOURCE_FILES}
		   ${CORE_HEADER_FILES}
                  )

if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)

set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/OgreFramework.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++ ")

set_property(TARGET XsiliumClient PROPERTY MACOSX_BUNDLE TRUE)

set_target_properties(XsiliumClient PROPERTIES
        LINK_FLAGS "-framework IOKit -framework Cocoa -framework Carbon -framework OpenGL -framework CoreVideo "
      )

 

set (XSILIUM_SAMPLE_CONTENTS_PATH
		${CMAKE_CURRENT_BINARY_DIR}/XsiliumClient.app/Contents)

add_custom_command(TARGET XsiliumClient POST_BUILD
		COMMAND mkdir ARGS -p ${XSILIUM_SAMPLE_CONTENTS_PATH}/Frameworks
		COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/Ogre.framework ${XSILIUM_SAMPLE_CONTENTS_PATH}/Frameworks/
		COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libCEGUIBase.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Frameworks/
		COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libCEGUIOgreRenderer.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Frameworks/
		COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libCEGUIXercesParser.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Frameworks/
		COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libCEGUICoreWindowRendererSet.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Frameworks/
		)
# now cfg files
add_custom_command(TARGET XsiliumClient POST_BUILD
		COMMAND mkdir ARGS -p ${XSILIUM_SAMPLE_CONTENTS_PATH}/Resources
		#COMMAND cp ARGS -R ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/plugins.cfg ${XSILIUM_SAMPLE_CONTENTS_PATH}/Resources/
		#COMMAND cp ARGS -R ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/resources.cfg ${XSILIUM_SAMPLE_CONTENTS_PATH}/Resources/
		COMMAND cp ARGS -R ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/datafiles ${XSILIUM_SAMPLE_CONTENTS_PATH}/Resources/datafiles
	       COMMAND cp ARGS -R ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Media ${XSILIUM_SAMPLE_CONTENTS_PATH}/Resources/media
		COMMAND cp ARGS -R ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/ogre.cfg ${XSILIUM_SAMPLE_CONTENTS_PATH}/Resources/
		)

add_custom_command(TARGET XsiliumClient POST_BUILD
		COMMAND mkdir ARGS -p ${XSILIUM_SAMPLE_CONTENTS_PATH}/Plugins)
add_custom_command(TARGET XsiliumClient POST_BUILD
		COMMAND mkdir ARGS -p ${XSILIUM_SAMPLE_CONTENTS_PATH}/Components)
		add_custom_command(TARGET XsiliumClient POST_BUILD
			COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libRenderSystem_GL.1.8.1.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Plugins/
			)
		add_custom_command(TARGET XsiliumClient POST_BUILD
			COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libPlugin_PCZSceneManager.1.8.1.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Plugins/
			)
		add_custom_command(TARGET XsiliumClient POST_BUILD
			COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libPlugin_ParticleFX.1.8.1.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Plugins/
			)
		add_custom_command(TARGET XsiliumClient POST_BUILD
			COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libPlugin_BSPSceneManager.1.8.1.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Plugins/
			)
		add_custom_command(TARGET XsiliumClient POST_BUILD
			COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libPlugin_BSPSceneManager.1.8.1.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Plugins/
			)
		add_custom_command(TARGET XsiliumClient POST_BUILD
			COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libPlugin_OctreeZone.1.8.1.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Plugins/
			)
		add_custom_command(TARGET XsiliumClient POST_BUILD
			COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libPlugin_OctreeSceneManager.1.8.1.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Plugins/
			)
		add_custom_command(TARGET XsiliumClient POST_BUILD
			COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libOgreTerrain.1.8.1.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Components/
			)
		add_custom_command(TARGET XsiliumClient POST_BUILD
			COMMAND cp ARGS -R ${CMAKE_BINARY_DIR}/lib/libOgrePaging.1.8.1.dylib ${XSILIUM_SAMPLE_CONTENTS_PATH}/Components/
			) 

endif()
