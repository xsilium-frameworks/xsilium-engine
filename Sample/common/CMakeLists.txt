set( CEGUI_TARGET_NAME ${CEGUI_SAMPLEHELPER_LIBNAME} )
set( CEGUI_SAMPLES_USE_OGRE TRUE)

set( CORE_SOURCE_FILES
    ./src/CEGuiBaseApplication.cpp
    ./src/CEGuiRendererSelector.cpp
    ./src/CEGuiSample.cpp
)

    list (APPEND CORE_SOURCE_FILES
        ./src/CEGuiOgreBaseApplication.cpp
    )

if (WIN32)
    list (APPEND CORE_SOURCE_FILES
        ./src/Win32AppHelper.cpp
        ./src/Win32CEGuiRendererSelector.cpp
    )
elseif (APPLE)
    list (APPEND CORE_SOURCE_FILES
        ./src/MacCEGuiRendererSelector.mm
    )
elseif (CEGUI_SAMPLES_USE_GTK2)
    list (APPEND CORE_SOURCE_FILES
        ./src/GTK2CEGuiRendererSelector.cpp
    )
else()
    list (APPEND CORE_SOURCE_FILES
        ./src/CLICEGuiRendererSelector.cpp
    )
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${OGRE_INCLUDE_DIRS} ${OIS_INCLUDE_DIR} ${CEGUI_SOURCE})

link_libraries(
${OGRE_LIBRARIES} 
${OIS_LIBRARIES}
${CEGUI_BUILD}/libCEGUIBase.so
${CEGUI_BUILD}/libCEGUIOgreRenderer.so
pcre
)

add_library(SampleCegui SHARED ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})




if (APPLE)
        set (CEGUI_EXTRA_FRAMEWORKS "${CEGUI_EXTRA_FRAMEWORKS} -framework IOKit -framework Cocoa")


    set_target_properties(${CEGUI_TARGET_NAME} PROPERTIES
        LINK_FLAGS ${CEGUI_EXTRA_FRAMEWORKS}
    )
endif()
