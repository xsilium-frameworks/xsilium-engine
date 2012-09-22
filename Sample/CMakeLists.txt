include_directories(${CMAKE_SOURCE_DIR}/Engine)

set(CORE_SOURCE_FILES
    FrameworkXsilium.cpp
    BaseApplication.cpp    
)

set(CORE_HEADER_FILES
    FrameworkXsilium.h
    BaseApplication.h     
)

message ("CEGUI ${CEGUI_SOURCE}")

include_directories(${OGRE_INCLUDE_DIRS} ${OIS_INCLUDE_DIR} ${CEGUI_SOURCE})


link_libraries(
${OGRE_LIBRARIES} 
${OIS_LIBRARIES}
${CEGUI_BUILD}/libCEGUIBase.so
pcre
)


    ###########################################################################
    #                   Dynamically Linked Executable
    ###########################################################################
    add_executable(test ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})


#set_target_properties(test PROPERTIES
#        LINK_FLAGS "-framework Cocoa -framework IOKit -framework Carbon"
#    )

