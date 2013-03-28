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
    Compte/Compte.cpp
    Login/UI/LoginState.cpp 
    XsiliumApp.cpp
    Game/Chat/Interface/Chat.cpp
    Game/Chat/GestionnaireChat/GestionnaireChat.cpp
    Login/Authentification.cpp
    Game/GestionnaireMeteo/GestionnaireMeteo.cpp
    Game/GestionnaireMeteo/HydraxRttListener/HydraxRttListener.cpp
    Game/JeuxState.cpp
)

set(CORE_HEADER_FILES
    Login/UI/LoginState.h
    Compte/Compte.h
    XsiliumApp.h 
    Game/Chat/Interface/Chat.h
    Game/Chat/StructurePacket/PacketChat.h
    Game/Chat/GestionnaireChat/GestionnaireChat.h
    Login/Authentification.h
    Login/ListOfMessage/ListOfMessage.h
    Game/GestionnaireMeteo/GestionnaireMeteo.h
    Game/GestionnaireMeteo/HydraxRttListener/HydraxRttListener.h
    Game/JeuxState.h
)

include_directories(
${XSILIUM_INCLUDE} 
Login
Game
.
)


link_libraries(${XSILIUM_LIB} ${SKYX_LIBRARIES})

ADD_EXECUTABLE(XsiliumClient WIN32 MACOSX_BUNDLE ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES} )

configure_file(${XSILIUM_SOURCE_DIR}/CMake/Templates/resources.cfg.in ${CMAKE_CURRENT_BINARY_DIR}/dist/bin/resources.cfg)
configure_file(${XSILIUM_SOURCE_DIR}/CMake/Templates/plugins.cfg.in ${CMAKE_CURRENT_BINARY_DIR}/dist/bin/plugins.cfg)


if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)

	
	set_target_properties(XsiliumClient PROPERTIES LINK_FLAGS "-framework IOKit -framework Cocoa -framework Carbon -framework OpenGL -framework CoreVideo ")
endif()


if (APPLE)
        set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/OgreFramework.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++ ")

	   # Mac OS X bundle specific settings
   	set(MACOSX_BUNDLE true)
   	set(MACOSX_BUNDLE_BUNDLE_NAME "Xsilium Client")
   	set(MACOSX_BUNDLE_INFO_STRING "Xsilium game 0.0.1")
   	set(MACOSX_BUNDLE_BUNDLE_VERSION "0.0.1")
    	set_target_properties(XsiliumClient PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO")

  if (OGRE_BUILD_PLATFORM_APPLE_IOS)
    set(XSILIUM_CONTENTS_PATH ${OGRE_BINARY_DIR}/XsiliumClient.app)
  else()

        set (XSILIUM_CONTENTS_PATH ${CMAKE_CURRENT_BINARY_DIR}/XsiliumClient.app/Contents)
        add_custom_command(TARGET XsiliumClient POST_BUILD
                COMMAND mkdir ARGS -p ${XSILIUM_CONTENTS_PATH}/Frameworks
                COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/Ogre.framework
                ${XSILIUM_CONTENTS_PATH}/Frameworks/
                COMMAND ln ARGS -s -f ${Cg_LIBRARY_REL}
                ${XSILIUM_CONTENTS_PATH}/Frameworks/

		COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libCEGUIBase.dylib
                ${XSILIUM_CONTENTS_PATH}/Frameworks/
		COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libCEGUIXercesParser.dylib
                ${XSILIUM_CONTENTS_PATH}/Frameworks/
		COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libCEGUIOgreRenderer.dylib
                ${XSILIUM_CONTENTS_PATH}/Frameworks/
		COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libCEGUICoreWindowRendererSet.dylib
                ${XSILIUM_CONTENTS_PATH}/Frameworks/

                )
        # now cfg files
        add_custom_command(TARGET XsiliumClient POST_BUILD
                COMMAND mkdir ARGS -p ${XSILIUM_CONTENTS_PATH}/Resources
                COMMAND ln ARGS -s -f ${CMAKE_CURRENT_BINARY_DIR}/dist/bin/plugins.cfg
                ${XSILIUM_CONTENTS_PATH}/Resources/
                COMMAND ln ARGS -s -f ${CMAKE_CURRENT_BINARY_DIR}/dist/bin/resources.cfg
                ${XSILIUM_CONTENTS_PATH}/Resources/

		COMMAND ln ARGS -s -f ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/configKey.xml
                ${XSILIUM_CONTENTS_PATH}/Resources/

		COMMAND ln ARGS -s -f ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/datafiles
                ${XSILIUM_CONTENTS_PATH}/Resources/

		COMMAND ln ARGS -s -f ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Media
                ${XSILIUM_CONTENTS_PATH}/Resources/
                )

        # now plugins
        add_custom_command(TARGET XsiliumClient POST_BUILD
                COMMAND mkdir ARGS -p ${XSILIUM_CONTENTS_PATH}/Plugins)
        add_custom_command(TARGET XsiliumClient POST_BUILD
                COMMAND mkdir ARGS -p ${XSILIUM_CONTENTS_PATH}/Components)

                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libRenderSystem_GL.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Plugins/
                        )

                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libPlugin_BSPSceneManager.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Plugins/
                        )


                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libPlugin_CgProgramManager.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Plugins/
                        )


                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libPlugin_OctreeSceneManager.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Plugins/
                        )


                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libPlugin_PCZSceneManager.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Plugins/
                        )

                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libPlugin_OctreeZone.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Plugins/
                        )

                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libPlugin_ParticleFX.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Plugins/
                        )

        # Components

                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libOgrePaging.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Components/
                        )


                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libOgreProperty.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Components/
                        )


                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libOgreRTShaderSystem.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Components/
                        )


                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libOgreTerrain.1.8.1.dylib
                        ${XSILIUM_CONTENTS_PATH}/Components/
                        )


        # Add links for the sample plugins
  endif()
endif (APPLE)

