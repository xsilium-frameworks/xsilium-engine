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
	Launcher.cpp
	Patcher/Patcher.cpp
	Repository/Repository.cpp
	Downloader/Downloader.cpp
	Downloader/Fetcher/Fetcher.cpp
	ResolvePaths/ResolvePaths.cpp
	Bspatch/bspatch.cpp
	Binreloc/binreloc.c
)

set(CORE_HEADER_FILES
    Launcher.h
    Patcher/Patcher.h
    Define.h
	MD5/md5.hpp
	Patch/PatchStructure.h
	Patch/PatchVersion.h
	Repository/Repository.h
	Utility/Utility.h
	Exception/Exception.h
	Downloader/Fetcher/Fetcher.h
	Downloader/Downloader.h
	ResolvePaths/ResolvePaths.h
	Binreloc/binreloc.h
)

include_directories(
${XSILIUM_INCLUDE} 
${BZIP2_INCLUDE_DIR}
.
)

find_library(CURL_LIBRARY NAMES curl curllib libcurl_imp curllib_static)


link_libraries(${XSILIUM_LIB} ${CURL_LIBRARY} ${BZIP2_LIBRARY_REL} ${LIBTAR_LIBRARY_REL})

ADD_EXECUTABLE(Launcher ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES} )


if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)

	
	set_target_properties(Launcher PROPERTIES LINK_FLAGS "-framework IOKit -framework Cocoa -framework Carbon -framework OpenGL -framework CoreVideo ")
endif()




