macro (configure_xsilium ROOT OGREPATH)
	#message(STATUS ${OGREPATH})
	set(GNUSTEP_SYSTEM_ROOT $ENV{GNUSTEP_SYSTEM_ROOT})

	# Use relative paths
	# This is mostly to reduce path size for command-line limits on windows
	if(WIN32)
  	# This seems to break Xcode projects so definitely don't enable on Apple builds
  		set(CMAKE_USE_RELATIVE_PATHS true)
  		set(CMAKE_SUPPRESS_REGENERATION true)
	endif()

	if (NOT CMAKE_OSX_ARCHITECTURES)
		set(CMAKE_OSX_ARCHITECTURES "${ARCHS_STANDARD_64_BIT}")
	endif()


	# Specify build paths
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${XSILIUM_BINARY_DIR}/lib")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${XSILIUM_BINARY_DIR}/lib")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${XSILIUM_BINARY_DIR}/bin")

	if (CMAKE_BUILD_TYPE STREQUAL "")
	  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
	  # differentiation between debug and release builds.
	  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
	endif ()
	
	set(XSILIUM_INSTALL_PREFIX ${ROOT})
	option(XSILIUM_COMPILE_SWIG				"Enable compile time SWIG generation."  OFF)
	option(XSILIUM_COMPILE_OGRE_SCRIPTS		"Automatically convert Blender TX to Ogre (.material, .font, .overlay... etc)" ON)
	option(XSILIUM_DEBUG_ASSERT				"Enable / Disable debug asserts." ON)
	option(XSILIUM_HEADER_GENERATOR			"Build Blender DNA to C++ generator."   OFF)
	option(XSILIUM_DISABLE_ZIP				"Disable external .zip resource loading" OFF)
	option(XSILIUM_USE_STATIC_ZLIB		"Compile and link statically ZLib and all its plugins" ON)	
	option(XSILIUM_USE_STATIC_ZZIP		"Compile and link statically ZZip and all its plugins" ON)	
	option(XSILIUM_USE_STATIC_FREEIMAGE		"Compile and link statically FreeImage and all its plugins" ON)
	option(XSILIUM_USE_STATIC_FREETYPE		"Compile and link statically freetype and all its plugins" ON)		
	option(XSILIUM_MINIMAL_FREEIMAGE_CODEC	"Compile minimal FreeImage Codec(PNG/JPEG/TGA)" OFF)
	option(XSILIUM_COMPILE_TINYXML			"Enable / Disable TinyXml builds" OFF)
	option(XSILIUM_GENERATE_BUILTIN_RES		"Generate build-in resources" OFF)
	option(XSILIUM_COMPILE_TCL				"Compile TemplateGenerator" OFF)
	option(XSILIUM_USE_PROCESSMANAGER       "Enable / Disable ProcessManager build" ON)
	option(XSILIUM_COMPILE_SOFTBODY			"Eanble / Disable Bullet Softbody build" OFF)
	option(XSILIUM_USE_NNODE				"Use Logic Node(It's Nodal Logic, not Blender LogicBrick)" OFF)
	option(XSILIUM_USE_OCTREE				"Use Octree SceneManager" ON)
	option(XSILIUM_USE_BSP					"USE BSP SceneManager"	ON)	
	option(XSILIUM_USE_PCZ					"USE PCZ SceneManager"	ON)
	option(XSILIUM_USE_PARTICLE				"Use Paritcle" ON)
	option(XSILIUM_COMPILE_OGRE_COMPONENTS	"Eanble compile additional Ogre components (RTShader, Terrain, Paging, ... etc)" ON)
	option(XSILIUM_USE_RTSHADER_SYSTEM		"Eanble shader system instead of fixed piped functions." OFF)
	option(XSILIUM_USE_COMPOSITOR			"Enable post effect by compositor (Bloom, BlackAndWhite, HDR, ...)" OFF)
	option(XSILIUM_USE_COMPOSITOR_TEX		"Add Compositor texture resources (NightVision, HeatVision, ...)" OFF)
	option(XSILIUM_COMPILE_OPTS				"Enable / Disable Opts builds" OFF)
        option(XSILIUM_BUILD_GL3PLUS				"Enable / Disable Opts builds" OFF)	
	set(OGRE_UNITY_FILES_PER_UNIT "40" CACHE STRING "Number of files per compilation unit in Unity build.")
	option(XSILIUM_CREATE_OGRE_DEPENDENCY_DIR	"Prepare Dependencies directory for Ogre prior to Ogre configuration and build" OFF)


	#Configuration Ogre
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

	# Set compiler specific build flags
	if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
  		check_cxx_compiler_flag(-msse OGRE_GCC_HAS_SSE)
  		if (OGRE_GCC_HAS_SSE)
    			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse")
  		endif ()
  		# This is a set of sensible warnings that provide meaningful output
  		set(OGRE_WARNING_FLAGS "-Wall -Winit-self -Wno-overloaded-virtual -Wcast-qual -Wwrite-strings -Wextra -Wno-unused-parameter -Wshadow -Wno-missing-field-initializers -Wno-long-long")
  		if (NOT APPLE)
      			set(OGRE_WARNING_FLAGS "${OGRE_WARNING_FLAGS} -Wno-unused-but-set-parameter")
  		endif ()
  		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OGRE_WARNING_FLAGS}")
	endif ()
	
	if (MSVC)
  		if (CMAKE_BUILD_TOOL STREQUAL "nmake")
    			# set variable to state that we are using nmake makefiles
			set(NMAKE TRUE)
  		endif ()
  		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
  		# Enable intrinsics on MSVC in debug mode
  		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Oi")
  		if (CMAKE_CL_64)
    			# Visual Studio bails out on debug builds in 64bit mode unless
			# this flag is set...
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj")
			set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /bigobj")
  		endif ()
  		if (OGRE_UNITY_BUILD)
    			# object files can get large with Unity builds
    			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
  		endif ()
  		if (MSVC_VERSION GREATER 1500 OR MSVC_VERSION EQUAL 1500)
    			option(OGRE_BUILD_MSVC_MP "Enable build with multiple processes in Visual Studio" TRUE)
  		else()
    			set(OGRE_BUILD_MSVC_MP FALSE CACHE BOOL "Compiler option /MP requires at least Visual Studio 2008 (VS9) or newer" FORCE)
  		endif()
  		if(OGRE_BUILD_MSVC_MP)
    			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  		endif ()
  		if(MSVC_VERSION GREATER 1400 OR MSVC_VERSION EQUAL 1400)
    			option(OGRE_BUILD_MSVC_ZM "Add /Zm256 compiler option to Visual Studio to fix PCH errors" TRUE)
  		else()
    			set(OGRE_BUILD_MSVC_ZM FALSE CACHE BOOL "Compiler option /Zm256 requires at least Visual Studio 2005 (VS8) or newer" FORCE)
  		endif()
  		if(OGRE_BUILD_MSVC_ZM)
    			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zm256")
  		endif ()
	endif ()
	if (MINGW)
  		add_definitions(-D_WIN32_WINNT=0x0500)
  		# set architecture to i686, since otherwise some versions of MinGW can't link
  		# the atomic primitives
  		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=i686")
  		# Fpermissive required to let some "non-standard" casting operations in the plugins pass
  		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
  		# disable this optimisation because it breaks release builds (reason unknown)
  		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-tree-slp-vectorize")
	endif ()

	if ((CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX) AND NOT MINGW)
  		# Test for GCC visibility
  		include(CheckCXXCompilerFlag)
  		check_cxx_compiler_flag(-fvisibility=hidden OGRE_GCC_VISIBILITY)
  		if (OGRE_GCC_VISIBILITY)
    			# determine gcc version
    			execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE OGRE_GCC_VERSION)
    			message(STATUS "Detected g++ ${OGRE_GCC_VERSION}")
    			message(STATUS "Enabling GCC visibility flags")
    			set(OGRE_GCC_VISIBILITY_FLAGS "-DOGRE_GCC_VISIBILITY -fvisibility=hidden")
    			set(XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN "YES")

    			# check if we can safely add -fvisibility-inlines-hidden
    			string(TOLOWER "${CMAKE_BUILD_TYPE}" OGRE_BUILD_TYPE)
    			if (OGRE_BUILD_TYPE STREQUAL "debug" AND OGRE_GCC_VERSION VERSION_LESS "4.2")
      				message(STATUS "Skipping -fvisibility-inlines-hidden due to possible bug in g++ < 4.2")
    			else ()
      				if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
        				message(STATUS "Skipping -fvisibility-inlines-hidden due to linker issues")
        				set(XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN[arch=x86_64] "YES")
      				else()
        				set(OGRE_GCC_VISIBILITY_FLAGS "${OGRE_GCC_VISIBILITY_FLAGS} -fvisibility-inlines-hidden")
        				set(XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN "YES")
      				endif()
    			endif ()
  		endif (OGRE_GCC_VISIBILITY)

  		# Fix x64 issues on Linux
  		if(OGRE_PLATFORM_X64 AND NOT APPLE)
    			add_definitions(-fPIC)
  		endif()
	endif ((CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX) AND NOT MINGW)

	# determine system endianess
	if (MSVC)
  		# This doesn't work on VS 2010
  		# MSVC only builds for intel anyway
  		set(OGRE_TEST_BIG_ENDIAN FALSE)
	else()
  		include(TestBigEndian)
  		test_big_endian(OGRE_TEST_BIG_ENDIAN)
	endif()

	if (OGRE_BUILD_PLATFORM_WINRT)
		# WinRT can only use the standard allocator
		set(OGRE_CONFIG_ALLOCATOR 1 CACHE STRING "Forcing Standard Allocator for WinRT" FORCE)
	else ()
		set(OGRE_CONFIG_ALLOCATOR 4 CACHE STRING
		"Specify the memory allocator to use. Possible values:
  		1 - Standard allocator
  		2 - nedmalloc
  		3 - User-provided allocator
  		4 - nedmalloc with pooling"
		)
	endif ()


	if (APPLE)
	
		# Set 10.4 as the base SDK by default
		set(XCODE_ATTRIBUTE_SDKROOT macosx10.7)
	
		if (NOT CMAKE_OSX_ARCHITECTURES)
			set(CMAKE_OSX_ARCHITECTURES ${ARCHS_STANDARD_32_64_BIT})
		endif()
	  
	endif ()


	set(XSILIUM_DEP_DIR ${ROOT}/Library/Dependencies/Source)
	set(XSILIUM_DEP_WIN_DIR ${ROOT}/Dependencies/Win32)
	
	
	set(OGRE_BINARY_DIR "${CMAKE_BINARY_DIR}")
	SET(OGRE_SOURCE_DIR ${OGREPATH})
	SET(OGRE_WORK_DIR ${OGRE_BINARY_DIR})
	set(OGRE_TEMPLATES_DIR ${ROOT}/CMake/Templates)
	SET(OGRE_DEPENDENCIES_DIR ${XSILIUM_DEP_DIR})
	set(OGRE_SDK_BUILD TRUE)
	
	set(XSILIUM_SOURCE_DIR ${ROOT})	
	set(XSILIUM_ANDROID_DEP_DIR ${ROOT}/Dependencies/Android)

	include(OgreConfigTargets)
	include(DependenciesXsilium)

 
	# Customise what to build
	cmake_dependent_option(OGRE_STATIC "Static build" FALSE "" TRUE)

	cmake_dependent_option(OGRE_BUILD_RENDERSYSTEM_D3D9 "Build Direct3D9 RenderSystem" TRUE "WIN32;DirectX9_FOUND;NOT OGRE_BUILD_PLATFORM_WINRT;NOT OGRE_BUILD_PLATFORM_WINDOWS_PHONE" FALSE)
	cmake_dependent_option(OGRE_BUILD_RENDERSYSTEM_D3D11 "Build Direct3D11 RenderSystem [EXPERIMENTAL]" TRUE "WIN32;DirectX11_FOUND  OR OGRE_BUILD_PLATFORM_WINRT OR OGRE_BUILD_PLATFORM_WINDOWS_PHONE" FALSE)
	cmake_dependent_option(OGRE_BUILD_RENDERSYSTEM_GL3PLUS "Build OpenGL 3+ RenderSystem [EXPERIMENTAL]" FALSE "OPENGL_FOUND; NOT OGRE_BUILD_RENDERSYSTEM_GLES; NOT OGRE_BUILD_RENDERSYSTEM_GLES2" FALSE)
	cmake_dependent_option(OGRE_BUILD_RENDERSYSTEM_GL "Build OpenGL RenderSystem" TRUE "OPENGL_FOUND;NOT OGRE_BUILD_PLATFORM_APPLE_IOS;NOT OGRE_BUILD_PLATFORM_WINRT;NOT OGRE_BUILD_PLATFORM_WINDOWS_PHONE" FALSE)
	cmake_dependent_option(OGRE_BUILD_RENDERSYSTEM_GLES "Build OpenGL ES 1.x RenderSystem" FALSE "OPENGLES_FOUND;NOT OGRE_BUILD_PLATFORM_WINRT;NOT OGRE_BUILD_PLATFORM_WINDOWS_PHONE" FALSE)
	cmake_dependent_option(OGRE_BUILD_RENDERSYSTEM_GLES2 "Build OpenGL ES 2.x RenderSystem" FALSE "OPENGLES2_FOUND;NOT OGRE_BUILD_PLATFORM_WINRT;NOT OGRE_BUILD_PLATFORM_WINDOWS_PHONE" FALSE)
	cmake_dependent_option(OGRE_BUILD_RENDERSYSTEM_STAGE3D "Build Stage3D RenderSystem" FALSE "FLASHCC" FALSE)
	cmake_dependent_option(OGRE_BUILD_PLATFORM_NACL "Build Ogre for Google's Native Client (NaCl)" FALSE "OPENGLES2_FOUND" FALSE)
	cmake_dependent_option(OGRE_BUILD_PLATFORM_WINRT "Build Ogre for Metro style application (WinRT)" FALSE "WIN32" FALSE)
	cmake_dependent_option(OGRE_BUILD_PLATFORM_WINDOWS_PHONE "Build Ogre for Windows Phone" FALSE "WIN32" FALSE)
	

	option(OGRE_BUILD_PLUGIN_BSP "Build BSP SceneManager plugin" TRUE)
	option(OGRE_BUILD_PLUGIN_OCTREE "Build Octree SceneManager plugin" TRUE)
	option(OGRE_BUILD_PLUGIN_PFX "Build ParticleFX plugin" TRUE)
	cmake_dependent_option(OGRE_BUILD_PLUGIN_PCZ "Build PCZ SceneManager plugin" TRUE "" FALSE)
	cmake_dependent_option(OGRE_BUILD_PLUGIN_CG "Build Cg plugin" TRUE "Cg_FOUND;NOT OGRE_BUILD_PLATFORM_APPLE_IOS" FALSE)
	cmake_dependent_option(OGRE_BUILD_COMPONENT_OVERLAY "Build Overlay component" TRUE "FREETYPE_FOUND OR OGRE_BUILD_PLATFORM_WINRT OR OGRE_BUILD_PLATFORM_WINDOWS_PHONE" FALSE)
	cmake_dependent_option(OGRE_BUILD_RTSHADERSYSTEM_CORE_SHADERS "Build RTShader System FFP core shaders" TRUE "OGRE_BUILD_COMPONENT_RTSHADERSYSTEM" FALSE)
	cmake_dependent_option(OGRE_BUILD_RTSHADERSYSTEM_EXT_SHADERS "Build RTShader System extensions shaders" TRUE "OGRE_BUILD_COMPONENT_RTSHADERSYSTEM" FALSE)


	cmake_dependent_option(OGRE_CONFIG_CONTAINERS_USE_CUSTOM_ALLOCATOR "STL containers in Ogre use the custom allocator" TRUE "" FALSE)
	option(OGRE_CONFIG_STRING_USE_CUSTOM_ALLOCATOR "Ogre String uses the custom allocator" FALSE)
	option(OGRE_CONFIG_MEMTRACK_DEBUG "Enable Ogre's memory tracker in debug mode" FALSE)
	option(OGRE_CONFIG_MEMTRACK_RELEASE "Enable Ogre's memory tracker in release mode" FALSE)
	# determine threading options
	include(PrepareThreadingOptions)
	cmake_dependent_option(OGRE_CONFIG_ENABLE_FREEIMAGE "Build FreeImage codec. If you disable this option, you need to provide your own image handling codecs." TRUE "FreeImage_FOUND OR OGRE_BUILD_PLATFORM_WINRT OR OGRE_BUILD_PLATFORM_WINDOWS_PHONE" FALSE)
	option(OGRE_CONFIG_ENABLE_DDS "Build DDS codec." TRUE)
	option(OGRE_CONFIG_ENABLE_PVRTC "Build PVRTC codec." FALSE)
	option(OGRE_CONFIG_ENABLE_ETC "Build ETC codec." FALSE)
	cmake_dependent_option(OGRE_CONFIG_ENABLE_ZIP "Build ZIP archive support. If you disable this option, you cannot use ZIP archives resource locations. The samples won't work." TRUE "ZZip_FOUND OR OGRE_BUILD_PLATFORM_WINRT OR 	OGRE_BUILD_PLATFORM_WINDOWS_PHONE" FALSE)
	option(OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE "Include Viewport orientation mode support." FALSE)
	cmake_dependent_option(OGRE_CONFIG_ENABLE_GLES2_CG_SUPPORT "Enable Cg support to ES 2 render system" FALSE "OGRE_BUILD_RENDERSYSTEM_GLES2" FALSE)
	cmake_dependent_option(OGRE_CONFIG_ENABLE_GLES2_GLSL_OPTIMISER "Enable GLSL optimiser use in GLES 2 render system" FALSE "OGRE_BUILD_RENDERSYSTEM_GLES2" FALSE)
	cmake_dependent_option(OGRE_CONFIG_ENABLE_GLES2_VAO_SUPPORT "Use VertexArrayObjects if possible." FALSE "OGRE_BUILD_RENDERSYSTEM_GLES2" FALSE)
	cmake_dependent_option(OGRE_CONFIG_ENABLE_GL_STATE_CACHE_SUPPORT "Enable OpenGL state cache management" FALSE "OGRE_BUILD_RENDERSYSTEM_GL OR OGRE_BUILD_RENDERSYSTEM_GLES OR OGRE_BUILD_RENDERSYSTEM_GLES2 OR OGRE_BUILD_RENDERSYSTEM_GL3PLUS" FALSE)
	cmake_dependent_option(OGRE_CONFIG_ENABLE_GLES3_SUPPORT "Enable OpenGL ES 3.x Features" FALSE "OPENGLES3_FOUND;OGRE_BUILD_RENDERSYSTEM_GLES2;NOT OGRE_BUILD_PLATFORM_WINRT;NOT OGRE_BUILD_PLATFORM_WINDOWS_PHONE" FALSE)
	cmake_dependent_option(OGRE_USE_BOOST "Use Boost extensions" TRUE "Boost_FOUND" FALSE)

	cmake_dependent_option(OGRE_INSTALL_PDB "Install debug pdb files" TRUE "MSVC" FALSE)
	cmake_dependent_option(OGRE_FULL_RPATH "Build executables with the full required RPATH to run from their install location." FALSE "NOT WIN32" FALSE)
	option(OGRE_PROFILING "Enable internal profiling support." FALSE)
	cmake_dependent_option(OGRE_CONFIG_STATIC_LINK_CRT "Statically link the MS CRT dlls (msvcrt)" FALSE "MSVC" FALSE)
	set(OGRE_LIB_DIRECTORY "lib${LIB_SUFFIX}" CACHE STRING "Install path for libraries, e.g. 'lib64' on some 64-bit Linux distros.")
	if (WIN32)
		option(OGRE_INSTALL_VSPROPS "Install Visual Studio Property Page." FALSE)
		if (OGRE_INSTALL_VSPROPS)
			configure_file(${OGRE_TEMPLATES_DIR}/OGRE.props.in ${OGRE_BINARY_DIR}/OGRE.props)
			install(FILES ${OGRE_BINARY_DIR}/OGRE.props DESTINATION "${CMAKE_INSTALL_PREFIX}")
		endif ()
	endif ()

	if (XSILIUM_COMPILE_OGRE_COMPONENTS)
		option(OGRE_BUILD_COMPONENT_PAGING "Build Ogre Paging Compoment" ON)
		option(OGRE_BUILD_COMPONENT_TERRAIN "Build Ogre Terrain Compoment" ON)
		option(OGRE_BUILD_COMPONENT_RTSHADERSYSTEM "Build Ogre RTShaderSystem Compoment" ON)
		option(OGRE_BUILD_COMPONENT_PROPERTY "Build Ogre Property Compoment(Required boost)" ON)
		option(OGRE_BUILD_COMPONENT_VOLUME "Build Volume component" ON)
		
	endif()


# configure plugins.cfg
if (NOT OGRE_BUILD_RENDERSYSTEM_D3D9)
  set(OGRE_COMMENT_RENDERSYSTEM_D3D9 "#")
endif ()
if (NOT OGRE_BUILD_RENDERSYSTEM_D3D11)
  set(OGRE_COMMENT_RENDERSYSTEM_D3D11 "#")
endif ()
if (CMAKE_SYSTEM_VERSION VERSION_LESS "6.0")
  set(OGRE_COMMENT_RENDERSYSTEM_D3D11 "#")
endif ()
if (NOT OGRE_BUILD_RENDERSYSTEM_GL)
  set(OGRE_COMMENT_RENDERSYSTEM_GL "#")
endif ()
if (NOT OGRE_BUILD_RENDERSYSTEM_GL3PLUS)
  set(OGRE_COMMENT_RENDERSYSTEM_GL3PLUS "#")
endif ()
if (NOT OGRE_BUILD_RENDERSYSTEM_GLES)
  set(OGRE_COMMENT_RENDERSYSTEM_GLES "#")
endif ()
if (NOT OGRE_BUILD_RENDERSYSTEM_GLES2)
  set(OGRE_COMMENT_RENDERSYSTEM_GLES2 "#")
endif ()
if (NOT OGRE_BUILD_PLUGIN_BSP)
  set(OGRE_COMMENT_PLUGIN_BSP "#")
endif ()
if (NOT OGRE_BUILD_PLUGIN_OCTREE)
  set(OGRE_COMMENT_PLUGIN_OCTREE "#")
endif ()
if (NOT OGRE_BUILD_PLUGIN_PCZ)
  set(OGRE_COMMENT_PLUGIN_PCZ "#")
endif ()
if (NOT OGRE_BUILD_PLUGIN_PFX)
  set(OGRE_COMMENT_PLUGIN_PARTICLEFX "#")
endif ()
if (NOT OGRE_BUILD_PLUGIN_CG)
  set(OGRE_COMMENT_PLUGIN_CG "#")
endif ()
if (NOT OGRE_BUILD_COMPONENT_TERRAIN)
  set(OGRE_COMMENT_COMPONENT_TERRAIN "#")
endif ()
if (NOT OGRE_BUILD_COMPONENT_RTSHADERSYSTEM)
  set(OGRE_COMMENT_COMPONENT_RTSHADERSYSTEM "#")
endif ()
if (NOT OGRE_BUILD_COMPONENT_VOLUME)
  set(OGRE_COMMENT_COMPONENT_VOLUME "#")
endif ()
if (NOT OGRE_BUILD_COMPONENT_TERRAIN OR NOT OGRE_BUILD_COMPONENT_PAGING)
  set(OGRE_COMMENT_SAMPLE_ENDLESSWORLD "#")
endif ()

if (APPLE)
  set(OGRE_MEDIA_DIR_DBG "Contents/Resources")
endif ()


# create resources.cfg
configure_file(${OGRE_TEMPLATES_DIR}/resources.cfg.in ${OGRE_BINARY_DIR}/bin/resources.cfg)
# create plugins.cfg
configure_file(${OGRE_TEMPLATES_DIR}/plugins.cfg.in ${OGRE_BINARY_DIR}/bin/plugins.cfg)


endmacro(configure_xsilium)

