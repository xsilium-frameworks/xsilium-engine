
set(CORE_SOURCE_FILES
    main.cpp
    Launcher.mm
    Launcher.cpp
)

set(CORE_HEADER_FILES
    Launcher.h
)

include_directories(
${XSILIUM_INCLUDE} 
${OGRE_INCLUDE_DIR}
${CEGUI_INCLUDE_DIR}
${RAPIDXML_INCLUDE_DIR}
${OGRE_RenderSystems_INCLUDE_DIR}
${OGRE_Overlay_INCLUDE_DIR}
.
)

if (APPLE)
	set_source_files_properties( ${CORE_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-x objective-c++")
endif()


link_libraries(	${XSILIUM_LIBRARY}
				${OGRE_LIBRARIES} 
			  )

ADD_EXECUTABLE(Launcher ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES} )


if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
	set_target_properties(Launcher PROPERTIES LINK_FLAGS "-framework IOKit -framework Cocoa -framework Carbon -framework OpenGL -framework CoreVideo ")
endif()




