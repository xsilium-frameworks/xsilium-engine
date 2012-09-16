include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../samples/common/include)

set(CORE_SOURCE_FILES
    Sample_Demo6.cpp    
)

set(CORE_HEADER_FILES
    Sample_Demo6.h    
)

include_directories(${OGRE_INCLUDE_DIRS} ${OIS_INCLUDE_DIR} ${CEGUI_SOURCE})


link_libraries(
${OGRE_LIBRARIES} 
${OIS_LIBRARIES}
${CEGUI_BUILD}/libCEGUIBase.so
${CMAKE_BINARY_DIR}/Sample/common/libSampleCegui.so
)


    ###########################################################################
    #                   Dynamically Linked Executable
    ###########################################################################
    add_executable(Demo6 ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})

