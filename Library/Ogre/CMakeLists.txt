#------------OLD---------------------------------------------
cmake_minimum_required(VERSION 2.6.2)

# CMake 2.8.2 has a bug that creates unusable Xcode projects when using ARCHS_STANDARD_32_BIT
# to specify both armv6 and armv7.
if(OGRE_BUILD_PLATFORM_APPLE_IOS AND (CMAKE_VERSION VERSION_EQUAL 2.8.2) AND (CMAKE_GENERATOR STREQUAL "Xcode"))
	message(FATAL_ERROR "CMake 2.8.2 cannot create compatible Xcode projects for iOS, please download the latest version or an older release from http://www.cmake.org/files/")
endif()

project(OGRELITE)
include(PrecompiledHeader)


set(OgreLite 1.0)
set (OGRE_CONFIG_HEADER 1)
set (OGRE_SDK_BUILD 1)
set(OGRE_LIB_TYPE         SHARED)
set(OGRE_BINARY_DIR ${XSILIUM_BINARY_DIR})
SET(OGRE_SOURCE_DIR       ${OGRELITE_SOURCE_DIR})
include(OgreConfigTargets)

 
# Configure settings
set(OGRE_NO_ZIP_ARCHIVE 0)
set(OGRE_CONFIG_ENABLE_ZIP TRUE)
set(OGRE_CONFIG_ENABLE_FREEIMAGE TRUE)
set(OGRE_CONFIG_ENABLE_DDS       TRUE)


if (XSILIUM_USE_PARTICLE)
	set(OGRE_BUILD_PLUGIN_PFX        TRUE)
else()
	set(OGRE_BUILD_PLUGIN_PFX        FALSE)
endif()


if (CMAKE_COMPILER_IS_GNUCXX)

	check_cxx_compiler_flag(-msse OGRE_GCC_HAS_SSE)

	if (OGRE_GCC_HAS_SSE AND NOT OGRE_BUILD_PLATFORM_IPHONE)
		add_definitions(-msse)
	endif()

	if (WIN32)

		# So Mingw w32api-3.14 can find 
		# MonitorFromPoint in the Render system
		add_definitions(-D_WIN32_WINNT=0x0500)

	endif(WIN32)

endif (CMAKE_COMPILER_IS_GNUCXX)




# determine system endianess
if (MSVC)
  # This doesn't work on VS 2010
  # MSVC only builds for intel anyway
  set(OGRE_TEST_BIG_ENDIAN FALSE)
else()
  include(TestBigEndian)
  test_big_endian(OGRE_TEST_BIG_ENDIAN)
endif()

# determine threading options
include(PrepareThreadingOptions)

# configure threading options
set(OGRE_THREAD_PROVIDER 0)
if (OGRE_CONFIG_THREADS)
	if (UNIX)
		add_definitions(-pthread)
	endif ()

	if (OGRE_CONFIG_THREAD_PROVIDER STREQUAL "boost")
		set(OGRE_THREAD_PROVIDER 1)
		include_directories(${Boost_INCLUDE_DIRS})
		# On MSVC Boost usually tries to autolink boost libraries. However since
		# this behaviour is not available on all compilers, we need to find the libraries
		# ourselves, anyway. Disable auto-linking to avoid mess-ups.
		add_definitions(-DBOOST_ALL_NO_LIB)
        if (MINGW AND Boost_USE_STATIC_LIBS)
            # mingw needs this to link against static thread libraries
            add_definitions(-DBOOST_THREAD_USE_LIB)
        endif ()
		set(OGRE_THREAD_LIBRARIES ${Boost_LIBRARIES})
	endif ()

	if (OGRE_CONFIG_THREAD_PROVIDER STREQUAL "poco")
		set(OGRE_THREAD_PROVIDER 2)
		include_directories(${POCO_INCLUDE_DIRS})
		set(OGRE_THREAD_LIBRARIES ${POCO_LIBRARIES})
	endif ()

	if (OGRE_CONFIG_THREAD_PROVIDER STREQUAL "tbb")
		set(OGRE_THREAD_PROVIDER 3)
		include_directories(${TBB_INCLUDE_DIRS})
		if (WIN32)
			add_definitions(-D_WIN32_WINNT=0x0501)    
		endif ()

		set(OGRE_THREAD_LIBRARIES ${TBB_LIBRARIES})
	endif ()
endif()


set(OGRE_SET_DOUBLE 0)
set(OGRE_SET_ALLOCATOR ${OGRE_CONFIG_ALLOCATOR})
set(OGRE_SET_CONTAINERS_USE_ALLOCATOR 0)
set(OGRE_SET_STRING_USE_ALLOCATOR 0)
set(OGRE_SET_MEMTRACK_DEBUG 0)
set(OGRE_SET_MEMTRACK_RELEASE 0)
set(OGRE_SET_THREADS ${OGRE_CONFIG_THREADS})
set(OGRE_SET_THREAD_PROVIDER ${OGRE_THREAD_PROVIDER})
set(OGRE_SET_ALLOCATOR 4)
set(OGRE_SET_DISABLE_FREEIMAGE 0)
set(OGRE_SET_DISABLE_DDS 0)
set(OGRE_SET_DISABLE_PVRTC 0)
set(OGRE_SET_DISABLE_ETC1 0)
set(OGRE_SET_DISABLE_ZIP 0)
set(OGRE_SET_DISABLE_LIBCPP_SUPPORT 0)
set(OGRE_SET_DISABLE_VIEWPORT_ORIENTATIONMODE 1)
set(OGRE_SET_DISABLE_GLES2_CG_SUPPORT 0)
#todo test this
set(OGRE_SET_DISABLE_GLES2_GLSL_OPTIMISER 0)
set(OGRE_SET_NEW_COMPILERS 0)
set(OGRE_STATIC_LIB 0)
set(OGRE_SET_USE_BOOST 0)
set(OGRE_SET_PROFILING 0)
if (OGRE_CONFIG_DOUBLE)
  set(OGRE_SET_DOUBLE 1)
endif()
if (OGRE_CONFIG_CONTAINERS_USE_CUSTOM_ALLOCATOR)
  set(OGRE_SET_CONTAINERS_USE_ALLOCATOR 1)
endif ()
if (OGRE_CONFIG_STRING_USE_CUSTOM_ALLOCATOR)
  set(OGRE_SET_STRING_USE_ALLOCATOR 1)
endif ()
if (OGRE_CONFIG_MEMTRACK_DEBUG)
  set(OGRE_SET_MEMTRACK_DEBUG 1)
endif()
if (OGRE_CONFIG_MEMTRACK_RELEASE)
  set(OGRE_SET_MEMTRACK_RELEASE 1)
endif()
if (NOT OGRE_CONFIG_ENABLE_FREEIMAGE)
  set(OGRE_SET_DISABLE_FREEIMAGE 1)
endif()
if (NOT OGRE_CONFIG_ENABLE_DDS)
  set(OGRE_SET_DISABLE_DDS 1)
endif()
if (NOT OGRE_CONFIG_ENABLE_PVRTC)
  set(OGRE_SET_DISABLE_PVRTC 1)
endif()
if (NOT OGRE_CONFIG_ENABLE_ETC1)
  set(OGRE_SET_DISABLE_ETC1 1)
endif()
if (NOT OGRE_CONFIG_ENABLE_ZIP)
  set(OGRE_SET_DISABLE_ZIP 1)
endif()
if (NOT OGRE_CONFIG_ENABLE_LIBCPP_SUPPORT)
  set(OGRE_SET_DISABLE_LIBCPP_SUPPORT 1)
endif() 
if (OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE)
  set(OGRE_SET_DISABLE_VIEWPORT_ORIENTATIONMODE 0)
endif()
if (NOT OGRE_CONFIG_ENABLE_GLES2_CG_SUPPORT)
  set(OGRE_SET_DISABLE_GLES2_CG_SUPPORT 1)
endif()
if (NOT OGRE_CONFIG_ENABLE_GLES2_GLSL_OPTIMISER)
  set(OGRE_SET_DISABLE_GLES2_GLSL_OPTIMISER 1)
endif()
if(OGRE_CONFIG_NEW_COMPILERS)
  set(OGRE_SET_NEW_COMPILERS 1)
endif()
if (OGRE_STATIC)
  set(OGRE_STATIC_LIB 1)
endif()
if (OGRE_USE_BOOST)
  set(OGRE_SET_USE_BOOST 1)
endif()
if (OGRE_PROFILING)
  set(OGRE_SET_PROFILING 1)
endif()

if (OGRE_TEST_BIG_ENDIAN)
  set(OGRE_CONFIG_BIG_ENDIAN 1)
else ()
  set(OGRE_CONFIG_LITTLE_ENDIAN 1)
endif ()




# determine Ogre version numbers
include(OgreGetVersion)
ogre_get_version(${OGRE_SOURCE_DIR}/OgreMain/include/OgrePrerequisites.h)
message(STATUS "Configuring OGRE ${OGRE_VERSION}")

configure_file(${XSILIUM_SOURCE_DIR}/CMake/Templates/OgreBuildSettings.h.in ${XSILIUM_BINARY_DIR}/include/OgreBuildSettings.h)


include_directories(${OGRELITE_SOURCE_DIR}/OgreMain/include)

include_directories(${XSILIUM_BINARY_DIR}/include)
include_directories(${FREETYPE_H_PATH} ${FREEIMAGE_H_PATH} ${ZZIP_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR} )

if (APPLE)
  if (OGRE_BUILD_PLATFORM_IPHONE)
	include_directories(${OGRELITE_SOURCE_DIR}/OgreMain/include/iPhone)
	include_directories(${OGRELITE_SOURCE_DIR}/OgreMain/include/OSX)
  else ()
	include_directories(${OGRELITE_SOURCE_DIR}/OgreMain/include/OSX)
  endif()
endif()

subdirs(OgreMain RenderSystems PlugIns Components)
