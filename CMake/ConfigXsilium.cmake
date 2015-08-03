macro (configure_xsilium)
	if (NOT CMAKE_OSX_ARCHITECTURES)
		set(CMAKE_OSX_ARCHITECTURES "${ARCHS_STANDARD_64_BIT}")
	endif()

# determine if we are compiling for a 32bit or 64bit system
	include(CheckTypeSize)
	CHECK_TYPE_SIZE("void*" XSILIUM_PTR_SIZE BUILTIN_TYPES_ONLY)
	if (XSILIUM_PTR_SIZE EQUAL 8)
  		set(XSILIUM_PLATFORM_X64 TRUE)
	else ()
  		set(XSILIUM_PLATFORM_X64 FALSE)
	endif ()

# Add -fPIC flag to x64 GCC builds
	if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
  		if (XSILIUM_PLATFORM_X64 AND NOT APPLE)
    			add_definitions(-fPIC)
  		endif ()
	endif ()


	# Specify build paths
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

	if (CMAKE_BUILD_TYPE STREQUAL "")
	  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
	  # differentiation between debug and release builds.
	  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
	endif ()

	set(XSILIUM_DEP_DIR ${XSILIUM_SOURCE_DIR}/Library/Dependencies)
	set(XSILIUM_DEP_WIN_DIR ${XSILIUM_SOURCE_DIR}/Library/Dependencies/Win32)

	include(DependenciesXsilium)



endmacro(configure_xsilium)

