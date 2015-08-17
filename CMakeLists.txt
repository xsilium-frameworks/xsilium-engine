# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)
   
project(XSILIUM)
SET(XSILIUM 1.0)

cmake_minimum_required(VERSION 2.6.2)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

if(CMAKE_VS_PLATFORM_NAME STREQUAL "Tegra-Android")
	set(CMAKE_LINK_LIBRARY_FLAG "")
endif()

# CMake 2.8.2 has a bug that creates unusable Xcode projects when using ARCHS_STANDARD_32_BIT
# to specify both armv6 and armv7.
if(OGRE_BUILD_PLATFORM_APPLE_IOS AND (CMAKE_VERSION VERSION_EQUAL 2.8.2) AND (CMAKE_GENERATOR STREQUAL "Xcode"))
	message(FATAL_ERROR "CMake 2.8.2 cannot create compatible Xcode projects for iOS, please download the latest version or an older release from http://www.cmake.org/files/")
endif()

# Use relative paths
# This is mostly to reduce path size for command-line limits on windows
if(WIN32)
  # This seems to break Xcode projects so definitely don't enable on Apple builds
  set(CMAKE_USE_RELATIVE_PATHS true)
  set(CMAKE_SUPPRESS_REGENERATION true)
endif()

if (APPLE AND NOT ANDROID)
  if(CMAKE_VERSION VERSION_LESS 3.0.0)
    include(CMakeForceCompiler)
    CMAKE_FORCE_C_COMPILER(clang GNU)
    CMAKE_FORCE_CXX_COMPILER(clang++ GNU)
  endif()
  SET(CMAKE_SIZEOF_VOID_P 4)
  set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif ()

# ---------------------------------------------------------
set(CMAKE_MODULE_PATH
    ${XSILIUM_SOURCE_DIR}/CMake
    ${XSILIUM_SOURCE_DIR}/CMake/Utils
    ${XSILIUM_SOURCE_DIR}/CMake/Packages
    ${XSILIUM_SOURCE_DIR}/CMake/Templates
    )
    
    
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)
include(MacroLogFeature)
include(OgreAddTargets)
include(OgreConfigTargets)
include(PreprocessorUtils)
include(SubModule)
include(ConfigXsilium)


configure_xsilium()

subdirs(Library)
subdirs(Engine)

subdirs(Client)
#subdirs(SceneLoader)





