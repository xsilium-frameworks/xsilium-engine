include_directories(${XSILIUM_INCLUDE})

if (UNIX)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/bin/datafiles
		DESTINATION ./
		CONFIGURATIONS All
	)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dist/bin/plugins.cfg
		${CMAKE_CURRENT_BINARY_DIR}/dist/bin/resources.cfg
		DESTINATION ./
		CONFIGURATIONS All
	)
endif(UNIX)


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
set( CEGUI_OGRE_RENDERER_LIBNAME CEGUIOgreRenderer)
set( CEGUI_BASE_LIBNAME CEGUIBase )

if (APPLE AND CMAKE_OSX_ARCHITECTURES MATCHES "x86_64" )

	list(APPEND CORE_SOURCE_FILES "SDK/OSX/XsiliumApp.mm")

endif()

include_directories(
${XSILIUM_INCLUDE} 
Login
Game
Shared
.
)

ADD_EXECUTABLE(XsiliumClient WIN32 MACOSX_BUNDLE ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES} )

target_link_libraries(XsiliumClient ${XSILIUM_LIB} ${XSILIUM_ZZIP_TARGET})
message(${XSILIUM_LIB} " :xsilium libraries XSILIUM_LIB...")

configure_file(${OGRE_TEMPLATES_DIR}/resources.cfg.in ${CMAKE_CURRENT_BINARY_DIR}/dist/bin/resources.cfg)
configure_file(${OGRE_TEMPLATES_DIR}/plugins.cfg.in ${CMAKE_CURRENT_BINARY_DIR}/dist/bin/plugins.cfg)


if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)

	
	set_target_properties(XsiliumClient PROPERTIES LINK_FLAGS "-framework IOKit -framework Cocoa -framework Carbon -framework OpenGL -framework CoreVideo ")
endif()


if (APPLE)
        set_source_files_properties(${CORE_SOURCE_FILES} ${CORE_HEADER_FILES}  PROPERTIES COMPILE_FLAGS "-x objective-c++ ")

	   # Mac OS X bundle specific settings
   	set_property(TARGET XsiliumClient PROPERTY MACOSX_BUNDLE true)
   	set_property(TARGET XsiliumClient PROPERTY MACOSX_BUNDLE_BUNDLE_NAME "Xsilium Client")
   	set_property(TARGET XsiliumClient PROPERTY MACOSX_BUNDLE_INFO_STRING "Xsilium game 0.0.1")
   	set_property(TARGET XsiliumClient PROPERTY MACOSX_BUNDLE_BUNDLE_VERSION "0.0.1")
   	set_property(TARGET XsiliumClient PROPERTY MACOSX_BUNDLE_ICON_FILE SampleBrowser_OSX.icns)
   	set_property(TARGET XsiliumClient PROPERTY MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Info.plist)
   	set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ogre3d.\${PRODUCT_NAME:rfc1034identifier}")
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
		COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libCEGUIRapidXMLParser.dylib
                ${XSILIUM_CONTENTS_PATH}/Frameworks/
		COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libCEGUIOgreRenderer.dylib
                ${XSILIUM_CONTENTS_PATH}/Frameworks/
		COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/libCEGUICoreWindowRendererSet.dylib
                ${XSILIUM_CONTENTS_PATH}/Frameworks/
                
                )
   
   # Components             
                
		add_custom_command(TARGET XsiliumClient POST_BUILD
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/RenderSystem_GL.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/OgreTerrain.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/OgrePaging.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/OgreOverlay.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/OgreVolume.framework
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
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/Plugin_BSPSceneManager.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
                        )


                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/Plugin_CgProgramManager.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
                        )


                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/Plugin_OctreeZone.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
                        )


                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/Plugin_PCZSceneManager.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
                        )

                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/Plugin_OctreeSceneManager.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
                        )

                add_custom_command(TARGET XsiliumClient POST_BUILD
                        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/Plugin_ParticleFX.framework
                        ${XSILIUM_CONTENTS_PATH}/Frameworks/
                        )
                        
                        
                 add_custom_command(TARGET XsiliumClient POST_BUILD
        				COMMAND ditto ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/SampleBrowser_OSX.icns ${XSILIUM_CONTENTS_PATH}/Resources
		)



        # Add links for the sample plugins
  endif()
endif (APPLE)

