macro (configure_xsilium)
	
#####################################################################
# Set up the basic build environment
#####################################################################

	if (CMAKE_BUILD_TYPE STREQUAL "")
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  	# differentiation between debug and release builds.
  		set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
	endif ()


	# determine if we are compiling for a 32bit or 64bit system
	include(CheckTypeSize)
	CHECK_TYPE_SIZE("void*" OGRE_PTR_SIZE BUILTIN_TYPES_ONLY)
	if (OGRE_PTR_SIZE EQUAL 8)
  		set(OGRE_PLATFORM_X64 TRUE)
	else ()
  		set(OGRE_PLATFORM_X64 FALSE)
	endif ()

	if (NOT APPLE)
  	# Create debug libraries with _d postfix
  		set(CMAKE_DEBUG_POSTFIX "_d")
	endif ()

	if ((CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX) AND NOT MINGW)
	# Fix x64 issues on Linux
	if(OGRE_PLATFORM_X64 AND NOT APPLE)
	add_definitions(-fPIC)
	endif()
	endif ((CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX) AND NOT MINGW)

	# determine system endianess
	if (MSVC OR ANDROID OR EMSCRIPTEN)
  	# This doesn't work on VS 2010
  	# MSVC only builds for intel anyway
  		set(OGRE_TEST_BIG_ENDIAN FALSE)
	else()
  		include(TestBigEndian)
  		test_big_endian(OGRE_TEST_BIG_ENDIAN)
	endif()


	set(XSILIUM_DEP_DIR ${XSILIUM_SOURCE_DIR}/Library/Dependencies)
	set(XSILIUM_DEP_WIN_DIR ${XSILIUM_SOURCE_DIR}/Library/Dependencies/Win32)

	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

	include(DependenciesXsilium)



endmacro(configure_xsilium)

