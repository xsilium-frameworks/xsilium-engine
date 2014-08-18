#------------OLD---------------------------------------------
cmake_minimum_required(VERSION 2.6.2)

project(OGRELite)
include(PrecompiledHeader)

# determine Ogre version numbers
include(OgreGetVersion)
ogre_get_version(${OGRE_SOURCE_DIR}/OgreMain/include/OgrePrerequisites.h)
message(STATUS "Configuring OGRE ${OGRE_VERSION}")
# Configure version file for use by scripts
configure_file("${OGRE_TEMPLATES_DIR}/version.txt.in" "${OGRE_BINARY_DIR}/version.txt" @ONLY)

# Add OgreMain include path
include_directories("${OGRE_SOURCE_DIR}/OgreMain/include")
include_directories("${OGRE_BINARY_DIR}/include")
if (APPLE)
  if (OGRE_BUILD_PLATFORM_APPLE_IOS)
    include_directories("${OGRE_SOURCE_DIR}/OgreMain/include/iOS")

    # Set static early for proper dependency detection
    set(OGRE_STATIC TRUE)
  else ()
    include_directories("${OGRE_SOURCE_DIR}/OgreMain/include/OSX")
  endif ()
endif (APPLE)

if (WIN32 OR APPLE)
  if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # We don't want to install in default system location, install is really for the SDK, so call it that
    set(CMAKE_INSTALL_PREFIX
	  "${OGRE_BINARY_DIR}/sdk" CACHE PATH "OGRE install prefix" FORCE
    )
  endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)

# Set up iOS overrides.
if (OGRE_BUILD_PLATFORM_APPLE_IOS)
  include_directories("${OGRE_SOURCE_DIR}/OgreMain/include/iOS")

  # Set build variables
  set(XCODE_ATTRIBUTE_SDKROOT iphoneos)
  if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    execute_process(COMMAND xcodebuild -version -sdk "${XCODE_ATTRIBUTE_SDKROOT}" Path | head -n 1 OUTPUT_VARIABLE CMAKE_OSX_SYSROOT)
    string(REGEX REPLACE "(\r?\n)+$" "" CMAKE_OSX_SYSROOT "${CMAKE_OSX_SYSROOT}")
  else()
    set(CMAKE_OSX_SYSROOT iphoneos)
  endif()

  set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework CoreGraphics -framework QuartzCore -framework UIKit")
  set(XCODE_ATTRIBUTE_GCC_UNROLL_LOOPS "YES")
  set(XCODE_ATTRIBUTE_LLVM_VECTORIZE_LOOPS "YES")
  set(XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
  set(XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")
  set(OGRE_BUILD_RENDERSYSTEM_GLES TRUE CACHE BOOL "Forcing OpenGL ES RenderSystem for iOS" FORCE)
  set(OGRE_BUILD_RENDERSYSTEM_GLES2 TRUE CACHE BOOL "Forcing OpenGL ES 2 RenderSystem for iOS" FORCE)
  set(OGRE_STATIC TRUE CACHE BOOL "Forcing static build for iOS" FORCE)
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.\${PRODUCT_NAME:rfc1034identifier}")
  add_definitions(-mno-thumb)

  set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD_INCLUDING_64_BIT)")
  string (REPLACE "-msse" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
elseif (ANDROID)
  set(TargetPlatform "Android")
  set(OGRE_PLATFORM OGRE_PLATFORM_ANDROID)
  set(OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE FALSE CACHE BOOL "Disable viewport orientation Android" FORCE)

  if( NOT ANDROID_GLES_ONLY )
   set(OGRE_CONFIG_ENABLE_GLES2_VAO_SUPPORT FALSE CACHE BOOL "Disable VAO on Android" FORCE)
   set(OGRE_BUILD_RENDERSYSTEM_GLES2 TRUE CACHE BOOL "Forcing OpenGL ES 2 RenderSystem for Android" FORCE)
   set(OGRE_BUILD_RENDERSYSTEM_GLES FALSE CACHE BOOL "Disable OpenGL ES 1 RenderSystem for Android" FORCE)
  else()
   set(OGRE_BUILD_RENDERSYSTEM_GLES2 FALSE CACHE BOOL "Disable OpenGL ES 2 RenderSystem for Android" FORCE)
   set(OGRE_BUILD_RENDERSYSTEM_GLES TRUE CACHE BOOL "Forcing OpenGL ES 1 RenderSystem for Android" FORCE)
   set(OGRE_BUILD_COMPONENT_RTSHADERSYSTEM FALSE CACHE BOOL "Disable RTSS component on Android ES1" FORCE)
   set(OGRE_BUILD_COMPONENT_VOLUME FALSE CACHE BOOL "Disable volume component on Android ES1" FORCE)
   set(OGRE_BUILD_COMPONENT_PAGING FALSE CACHE BOOL "Disable paging component on FlashCC" FORCE)
   set(OGRE_BUILD_COMPONENT_TERRAIN FALSE CACHE BOOL "Disable terrain component on FlashCC" FORCE)
  endif()

  set(OGRE_BUILD_PLUGIN_PCZ FALSE CACHE BOOL "Disable pcz on Android" FORCE)
  set(OGRE_BUILD_PLUGIN_BSP FALSE CACHE BOOL "Disable bsp scenemanager on Android" FORCE)
  set(OGRE_BUILD_TESTS FALSE CACHE BOOL "Disable tests on Android" FORCE)
  set(OGRE_BUILD_TOOLS FALSE CACHE BOOL "Disable tools on Android" FORCE)
  set(OGRE_STATIC TRUE CACHE BOOL "Forcing static build for Android" FORCE)
elseif (FLASHCC)
  set(__FLASHCC__ TRUE)
  set(OGRE_PLATFORM OGRE_PLATFORM_FLASHCC)
  set(OGRE_BUILD_RENDERSYSTEM_STAGE3D TRUE CACHE BOOL "Enable Stage3D RenderSystem for FlashCC" FORCE)
  set(OGRE_BUILD_RENDERSYSTEM_GLES2 FALSE CACHE BOOL "Disable OpenGL ES 2 RenderSystem for FlashCC" FORCE)
  set(OGRE_BUILD_RENDERSYSTEM_GLES FALSE CACHE BOOL "Disable OpenGL ES 1 RenderSystem for FlashCC" FORCE)
  set(OGRE_BUILD_COMPONENT_PAGING FALSE CACHE BOOL "Disable paging component on FlashCC" FORCE)
  set(OGRE_BUILD_COMPONENT_TERRAIN FALSE CACHE BOOL "Disable terrain component on FlashCC" FORCE)
  set(OGRE_BUILD_COMPONENT_VOLUME FALSE CACHE BOOL "Disable volume component on FlashCC" FORCE)
  set(OGRE_BUILD_PLUGIN_PCZ FALSE CACHE BOOL "Disable pcz on FlashCC" FORCE)
  set(OGRE_BUILD_PLUGIN_BSP FALSE CACHE BOOL "Disable bsp scenemanager on FlashCC" FORCE)
  set(OGRE_BUILD_TESTS FALSE CACHE BOOL "Disable tests on FlashCC" FORCE)
  set(OGRE_BUILD_TOOLS FALSE CACHE BOOL "Disable tools on FlashCC" FORCE)
  set(OGRE_STATIC TRUE CACHE BOOL "Forcing static build for FlashCC" FORCE)
elseif (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)

  set(XCODE_ATTRIBUTE_SDKROOT macosx)
  if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    execute_process(COMMAND xcodebuild -version -sdk "${XCODE_ATTRIBUTE_SDKROOT}" Path | head -n 1 OUTPUT_VARIABLE CMAKE_OSX_SYSROOT)
    string(REGEX REPLACE "(\r?\n)+$" "" CMAKE_OSX_SYSROOT "${CMAKE_OSX_SYSROOT}")
  else()
    set(CMAKE_OSX_SYSROOT macosx)
  endif()

  if (NOT CMAKE_OSX_ARCHITECTURES)
    if(OGRE_BUILD_RENDERSYSTEM_GL3PLUS)
      if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
        set(CMAKE_OSX_ARCHITECTURES "${ARCHS_STANDARD_64_BIT}")
      else()
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD_64_BIT)")
      endif()
    else()
      if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
        set(CMAKE_OSX_ARCHITECTURES "${ARCHS_STANDARD_32_64_BIT}")
      else()
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD_32_64_BIT)")
      endif()
    endif()
  endif()

  # 10.7 is the minimum for libc++ support
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.7)
  
  if(APPLE)
	set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ ")
endif()

  # Make sure that the OpenGL render system is selected for non-iOS Apple builds
  set(OGRE_BUILD_RENDERSYSTEM_GLES FALSE)
  set(OGRE_BUILD_RENDERSYSTEM_GLES2 FALSE)
elseif (OGRE_BUILD_PLATFORM_WINRT)
  set(OGRE_BUILD_RENDERSYSTEM_D3D11 TRUE CACHE BOOL "Forcing Direct3D11 RenderSystem for WinRT" FORCE)
endif ()

if(OGRE_CONFIG_ENABLE_GLES3_SUPPORT)
  set(OGRE_CONFIG_ENABLE_GLES2_VAO_SUPPORT TRUE CACHE BOOL "Forcing VAO support for OpenGL ES 3" FORCE)
endif()

# Enable the PVRTC codec if OpenGL ES is being built
if(OGRE_BUILD_RENDERSYSTEM_GLES OR OGRE_BUILD_RENDERSYSTEM_GLES2)
  set(OGRE_CONFIG_ENABLE_PVRTC TRUE CACHE BOOL "Forcing PVRTC codec for OpenGL ES" FORCE)
  set(OGRE_CONFIG_ENABLE_ETC TRUE CACHE BOOL "Forcing ETC codec for OpenGL ES" FORCE)
endif()

# Enable the ETC codec if OpenGL 3+ is being built
if(OGRE_BUILD_RENDERSYSTEM_GL3PLUS)
  set(OGRE_CONFIG_ENABLE_ETC TRUE CACHE BOOL "Forcing ETC codec for OpenGL 3+" FORCE)
endif()

###################################################################
# configure global build settings based on selected build options
###################################################################
include(ConfigureBuild)

###################################################################
# disable (useless) compiler warnings on project level
###################################################################
if(MSVC)
	add_definitions( /wd4786 /wd4503 /wd4251 /wd4275 /wd4290 /wd4661 /wd4996 /wd4127 /wd4100)
endif()

##################################################################
# Now setup targets
##################################################################

# Setup OgreMain project
add_subdirectory(OgreMain)

# Setup RenderSystems
add_subdirectory(RenderSystems)

# Setup Plugins
add_subdirectory(PlugIns)

# Setup Components
add_subdirectory(Components)

# Provide CPack packaging target
include(Packaging)


# Show feature summary
include(FeatureSummary)

