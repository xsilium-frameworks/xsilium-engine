# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

set(CONTENT
	${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/SampleBrowser_OSX.icns
)
set(TargetName XsiliumClient)

set(CORE_SOURCE_FILES
    main.cpp
    XsiliumApp.cpp
    Game/PlayState.cpp
    Game/Chat/GestionnaireChat.cpp
    Game/Gui/GuiChat.cpp
    Login/LoginState.cpp 
    Login/Authentification/GestionnaireAuth.cpp
    Login/Gui/GuiAuth.cpp
    Shared/Compte/Compte.cpp
)

set(CORE_HEADER_FILES
    XsiliumApp.h
    Game/PlayState.h
    Game/Chat/GestionnaireChat.h
    Game/Gui/GuiChat.h
    Login/LoginState.h
    Login/Authentification/GestionnaireAuth.h
    Login/Gui/GuiAuth.h
    Shared/Compte/Compte.h
)

if(WIN32)

	source_group(Main\\Source FILES ${CORE_SOURCE_FILES})
	source_group(Main\\Header FILES ${CORE_HEADER_FILES})

	source_group(Datafiles FILES ${CONTENT})
endif()

if (APPLE)
	list(APPEND CORE_SOURCE_FILES "SDK/OSX/XsiliumApp.mm")
	set_source_files_properties( ${CORE_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-x objective-c++")
endif()

 set(SRC  
	${CORE_SOURCE_FILES} 
	${CORE_HEADER_FILES}
	)

include_directories(
${XSILIUM_INCLUDE}
${ENET_INCLUDE_DIR} 
${CEGUI_INCLUDE_DIR}
${OGRE_INCLUDE_DIR}
${RAPIDXML_INCLUDE_DIR}
${OGRE_Overlay_INCLUDE_DIR}
${SKYX_H_PATH}
${HYDRAX_H_PATH}
${OGRE_Terrain_INCLUDE_DIR}
${OGRE_RenderSystems_INCLUDE_DIR}
${OGREPAGED_INCLUDE_DIRS}
${BULLET_INCLUDE_DIRS}
Login
Game
Shared
.
)

link_libraries(
	${XSILIUM_LIBRARY} ${DirectX_LIBRARY}
)
xsilium_add_executable(${TargetName} WIN32 ${SRC} ${RESOURCE_FILES})

if (APPLE)

	# On OS X, create .app bundle
	set_property(TARGET ${TargetName} PROPERTY MACOSX_BUNDLE TRUE)
	set_property(TARGET ${TargetName} PROPERTY MACOSX_BUNDLE_ICON_FILE SampleBrowser_OSX.icns)
	set_property(TARGET ${TargetName} PROPERTY MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Info.plist)
	set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ogre3d.\${PRODUCT_NAME:rfc1034identifier}")
    	set_target_properties(${TargetName} PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO")


	target_link_libraries(${TargetName} ${CoreVideo_LIBRARIES})

   	set_target_properties(${TargetName} PROPERTIES
        LINK_FLAGS "-framework IOKit -framework Cocoa -framework Carbon -framework CoreVideo -framework ApplicationServices ")

    # Add the path where the Ogre framework was found, if it has been found somewhere
    if(NOT ${OGRE_FRAMEWORK_PATH} STREQUAL "" AND OGRE_SDK_BUILD)
      set_target_properties(SampleBrowser PROPERTIES
        COMPILE_FLAGS "-F${OGRE_FRAMEWORK_PATH}"
        LINK_FLAGS "-F${OGRE_FRAMEWORK_PATH} -framework IOKit -framework Cocoa -framework Carbon -framework OpenGL -framework CoreVideo"
      )
    endif()
	# also, symlink frameworks so .app is standalone
	# NOTE: $(CONFIGURATION) is not resolvable at CMake run time, it's only 
	# valid at build time (hence parenthesis rather than braces)
	
    set(OGRE_OSX_BUILD_CONFIGURATION "$(PLATFORM_NAME)/$(CONFIGURATION)")
    set(OGRE_BUILT_FRAMEWORK "$(PLATFORM_NAME)/$(CONFIGURATION)")
	set (OGRE_SAMPLE_CONTENTS_PATH 
		${OGRE_BINARY_DIR}/bin/$(CONFIGURATION)/${TargetName}.app/Contents)
	add_custom_command(TARGET ${TargetName} POST_BUILD
		COMMAND mkdir ARGS -p ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks
		COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_BUILT_FRAMEWORK}/Ogre.framework 
		${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
		COMMAND ln ARGS -s -f ${Cg_LIBRARY_REL}
		${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
		)
	# now cfg files
	add_custom_command(TARGET ${TargetName} POST_BUILD
		COMMAND mkdir ARGS -p ${OGRE_SAMPLE_CONTENTS_PATH}/Resources
		COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/plugins.cfg 
		${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
		COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/resources.cfg 
		${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
		COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/samples.cfg 
		${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
		COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/quakemap.cfg 
		${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
		COMMAND ln ARGS -s -f ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Data/Media
		${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
		COMMAND ln ARGS -s -f ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/Data/datafiles
		${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
        COMMAND ditto 
		${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/SampleBrowser_OSX.icns ${OGRE_SAMPLE_CONTENTS_PATH}/Resources
		COMMAND cp 
		${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/configKey.xml ${OGRE_SAMPLE_CONTENTS_PATH}/Resources
		)

	# now plugins
	add_custom_command(TARGET ${TargetName} POST_BUILD
		COMMAND mkdir ARGS -p ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks
		COMMAND mkdir ARGS -p ${OGRE_SAMPLE_CONTENTS_PATH}/Plugins)

    set(FRAMEWORKS 
    	OgreOverlay
        OgrePaging
        OgreProperty
        OgreRTShaderSystem
        OgreTerrain
        OgreVolume
        Plugin_BSPSceneManager
        Plugin_CgProgramManager
        Plugin_OctreeSceneManager
        Plugin_OctreeZone
        Plugin_ParticleFX
        Plugin_PCZSceneManager
        RenderSystem_GL
        RenderSystem_GL3Plus
    )

    foreach(FWK ${FRAMEWORKS})
	add_custom_command(TARGET ${TargetName} POST_BUILD
        COMMAND ARGS if [ -d ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/${FWK}.framework ]\; then ln -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/${FWK}.framework ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/${FWK}.framework\; fi
		)
    endforeach(FWK)

    add_custom_command(TARGET ${TargetName} POST_BUILD
		COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/libCEGUIExpatParser.dylib
		${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
		COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/libCEGUICoreWindowRendererSet.dylib
		${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
		COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/libCEGUIBase.dylib
		${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
		COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/libCEGUIOgreRenderer.dylib
		${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
		)

endif()



