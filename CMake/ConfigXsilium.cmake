macro (configure_xsilium ROOT OGREPATH)
	#message(STATUS ${OGREPATH})
	set(GNUSTEP_SYSTEM_ROOT $ENV{GNUSTEP_SYSTEM_ROOT})
	
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${XSILIUM_BINARY_DIR}/lib)
	
	if(APPLE OR GNUSTEP_SYSTEM_ROOT)
		if (WIN32 AND NOT CMAKE_COMPILER_IS_GNUCXX)
			set(XSILIUM_USE_COCOA FALSE CACHE BOOL "Forcing remove Use Cocoa" FORCE)
		else()
			option(XSILIUM_USE_COCOA	"Use Cocoa"	ON)
		endif()
	endif()
	
	if(XSILIUM_USE_COCOA)
		add_definitions(-DXSILIUM_USE_COCOA)
		if(GNUSTEP_SYSTEM_ROOT)
			include_directories(${GNUSTEP_SYSTEM_ROOT}/Library/Headers)
			link_directories(${GNUSTEP_SYSTEM_ROOT}/Library/Libraries)
			link_libraries("gnustep-base")
			link_libraries("objc")
		endif()
	endif()

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
	option(XSILIUM_USE_STATIC_FREEIMAGE		"Compile and link statically FreeImage and all its plugins" ON)	
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
	
	if (APPLE)
		option(XSILIUM_BUILD_IPHONE	"Build GameKit on iOS SDK"	OFF)
		option(XSILIUM_BUILD_IPHONE_UNIV "Support arm6 architecture for old devcie" OFF)
	endif()

	option(XSILIUM_BUILD_ANDROID	"Build GameKit on Android SDK" OFF)
	option(XSILIUM_BUILD_NACL		"Build GameKit on NACL" OFF)

	
	if (XSILIUM_BUILD_ANDROID OR XSILIUM_BUILD_IPHONE OR XSILIUM_BUILD_NACL)
		set(XSILIUM_BUILD_MOBILE 1) #Force use GLES2, not GL.
	endif()
    
    	if (XSILIUM_BUILD_GLES2RS)
        	set(XSILIUM_USE_RTSHADER_SYSTEM TRUE CACHE BOOL "Forcing RTShaderSystem" FORCE)
    	endif()
	
	if (XSILIUM_USE_RTSHADER_SYSTEM OR XSILIUM_USE_COMPOSITOR)
		set(XSILIUM_DISABLE_ZIP CACHE BOOL "Forcing ZZLib" FORCE)
	endif()
	
	if (XSILIUM_USE_RTSHADER_SYSTEM)
		set(OGRE_BUILD_COMPONENT_RTSHADERSYSTEM TRUE)
		set(RTSHADER_SYSTEM_BUILD_CORE_SHADERS 1)
		set(RTSHADER_SYSTEM_BUILD_EXT_SHADERS 1)				
		
		if (XSILIUM_BUILD_MOBILE)
			message(STATUS "mobile rtshader")
			set(OGRE_BUILD_RENDERSYSTEM_GLES CACHE BOOL "Forcing OpenGLES" FORCE)
			set(OGRE_BUILD_RENDERSYSTEM_GLES2 TRUE CACHE BOOL "Forcing OpenGLES2" FORCE)

			set(XSILIUM_BUILD_GLESRS  CACHE BOOL "Forcing remove GLES"   FORCE)
			set(XSILIUM_BUILD_GLES2RS TRUE CACHE BOOL "Forcing OpenGLES2" FORCE)
        endif()
	endif()	
	
	
	if (XSILIUM_COMPILE_OGRE_COMPONENTS)
		option(OGRE_BUILD_COMPONENT_PAGING "Build Ogre Paging Compoment" ON)
		option(OGRE_BUILD_COMPONENT_TERRAIN "Build Ogre Terrain Compoment" ON)
		#option(OGRE_BUILD_COMPONENT_RTSHADERSYSTEM "Build Ogre RTShaderSystem Compoment" OFF)
		option(OGRE_BUILD_COMPONENT_PROPERTY "Build Ogre Property Compoment(Required boost)" OFF)
	endif()
	
	set(XSILIUM_ZZIP_TARGET ZZipLib)
	set(XSILIUM_FREETYPE_TARGET freetype)
	set(XSILIUM_OIS_TARGET OIS)
	
	set(XSILIUM_DEP_DIR ${ROOT}/Library/Dependencies/Source)
	set(XSILIUM_DEP_WIN_DIR ${ROOT}/Dependencies/Win32)
	
	set(OGRE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
	SET(OGRE_SOURCE_DIR ${OGREPATH})
	SET(OGRE_WORK_DIR ${OGRE_BINARY_DIR})
	set(OGRE_TEMPLATES_DIR ${ROOT}/CMake/Templates)
	SET(OGRE_DEPENDENCIES_DIR ${XSILIUM_DEP_DIR})
	
	set(XSILIUM_SOURCE_DIR ${ROOT})	
	set(XSILIUM_ANDROID_DEP_DIR ${ROOT}/Dependencies/Android)

	set(OGRE_USE_BOOST TRUE CACHE BOOL "Forcing use BOOST" ) 

	set(Boost_ADDITIONAL_VERSIONS "1.52.0 1.49.0 1.48.0")
	set(Boost_USE_STATIC_LIBS        OFF)
	set(Boost_USE_MULTITHREADED      ON)
	set(Boost_USE_STATIC_RUNTIME     OFF)
	set(BOOST_ALL_DYN_LINK           ON)

	set(OGRE_BOOST_COMPONENTS chrono thread date_time system filesystem)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)

	include_directories("${Boost_INCLUDE_DIRS}")
	
	include(OgreConfigTargets)
	include(DependenciesXsilium)
	include(MacroLogFeature)


	if (NOT XSILIUM_USE_STATIC_FREEIMAGE)
	
		if(ZLIB_FOUND)
			set(XSILIUM_ZLIB_TARGET	${ZLIB_LIBRARY})
			set(XSILIUM_FREEIMAGE_INCLUDE	${ZLIB_INCLUDE_DIR})
		else()
			message("Zlib not found.")
			message("Package is mandatory, please install it or enable static FreeImage compilation.")
		endif()
		
		
		if(FreeImage_FOUND)
			set(XSILIUM_FREEIMAGE_TARGET	${FreeImage_LIBRARY})	
			set(XSILIUM_FREEIMAGE_INCLUDE	${FreeImage_INCLUDE_DIR})
		else()
			message("FreeImage not found")
			message("Package is mandatory, please install it or enable static FreeImage compilation.")
		endif()
		
	else()
	
		set(XSILIUM_ZLIB_TARGET	ZLib)
		set(XSILIUM_FREEIMAGE_TARGET FreeImage)
		set(XSILIUM_ZLIB_INCLUDE ${XSILIUM_DEP_DIR}/FreeImage/ZLib)
		set(XSILIUM_FREEIMAGE_INCLUDE ${XSILIUM_DEP_DIR}/FreeImage)        
		
	endif()

	set(FreeImage_LIBRARIES	${XSILIUM_FREEIMAGE_TARGET})
	set(ZLIB_LIBRARIES	${XSILIUM_ZLIB_TARGET})	
	set(ZZip_LIBRARIES	${XSILIUM_ZZIP_TARGET})

	if (APPLE)
		set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")	
		if (OGRE_BUILD_PLATFORM_IPHONE)
			option(XSILIUM_USE_COCOA "Use Cocoa" ON)
			set(XSILIUM_PLATFORM ${OGREPATH}/OgreMain/include/IPhone )
		else()
			set(XSILIUM_PLATFORM ${OGREPATH}/OgreMain/include/OSX )
		endif()
		
	else()
	
		if (UNIX)
			set(XSILIUM_PLATFORM ${OGREPATH}/OgreMain/include/GLX )
		elseif (WIN32)
			set(XSILIUM_PLATFORM ${OGREPATH}/OgreMain/include/WIN32 )
		endif()
		
	endif()
	
	
	if (XSILIUM_COMPILE_SWIG OR XSILIUM_GENERATE_BUILTIN_RES)
		set(XSILIUM_COMPILE_TCL TRUE CACHE BOOL "Forcing TCL"  FORCE)
	endif()
	
	if (XSILIUM_BUILD_MOBILE)
	   set(XSILIUM_BUILD_GLRS    CACHE BOOL "Forcing remove GL"   FORCE)
	endif()
		

	if (XSILIUM_BUILD_ANDROID)
	
		set(OGRE_BUILD_PLATFORM_ANDROID TRUE)

		set(XSILIUM_OPENAL_SOUND   CACHE BOOL "Forcing remove OpenAL"   FORCE)
		set(XSILIUM_BUILD_GLRS    FALSE CACHE BOOL "Forcing GLRS"   FORCE)
		set(XSILIUM_BUILD_GLESRS  FALSE CACHE BOOL "Forcing remove GLESRS"   FORCE)
        set(XSILIUM_BUILD_GLES2RS TRUE  CACHE BOOL "Forcing remove GLES2RS"   FORCE)
        
		set(XSILIUM_USE_RTSHADER_SYSTEM TRUE CACHE BOOL "Forcing RTShaderSystem for Android" FORCE)
		set(OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE TRUE CACHE BOOL "Forcing viewport orientation support for Android" FORCE)
		if (OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE)
			set(OGRE_SET_DISABLE_VIEWPORT_ORIENTATIONMODE 0)
		endif()

		#message(${XSILIUM_BUILD_GLRS} "---" ${XSILIUM_BUILD_GLESRS} " --- " ${OPENGLES2_gl_LIBRARY})
		
		elseif (XSILIUM_BUILD_NACL)
	
		set(OGRE_BUILD_PLATFORM_NACL TRUE)
		include_directories(${OPENGLES2_INCLUDE_DIR})
		#include_directories(${OGRE_SOURCE_DIR}/RenderSystems/GLES2/include)
		include_directories(${NACL_SDK_ROOT}/include)

		set(XSILIUM_OPENAL_SOUND   CACHE BOOL "Forcing remove OpenAL"   FORCE)
		
		set(XSILIUM_BUILD_GLRS    FALSE CACHE BOOL "Forcing GLRS"   FORCE)
		set(XSILIUM_BUILD_GLESRS  FALSE CACHE BOOL "Forcing remove GLESRS"   FORCE)
        set(XSILIUM_BUILD_GLES2RS TRUE  CACHE BOOL "Forcing remove GLES2RS"   FORCE)

		set(XSILIUM_MINIMAL_FREEIMAGE_CODEC  TRUE CACHE BOOL "Forcing FreeImage minimal codec" FORCE)
        
		set(XSILIUM_USE_RTSHADER_SYSTEM TRUE CACHE BOOL "Forcing RTShaderSystem for Android" FORCE)
	
	elseif (XSILIUM_BUILD_IPHONE)
	
		set(OGRE_BUILD_PLATFORM_IPHONE TRUE) #TODO: replace to OGRE_BUILD_APPLE_IOS 
		set(OGRE_BUILD_PLATFORM_APPLE_IOS TRUE)
		
		#copy from ogre3d build
		# Set up iPhone overrides.
		include_directories("${OGREPATH}/OgreMain/include/iPhone")
	
		# Set build variables
		set(CMAKE_OSX_SYSROOT iphoneos)
		set(CMAKE_OSX_DEPLOYMENT_TARGET "")
		set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework CoreGraphics -framework QuartzCore -framework UIKit")
		set(XCODE_ATTRIBUTE_SDKROOT iphoneos)
		set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.\${PRODUCT_NAME:rfc1034identifier}")
		set(OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE TRUE CACHE BOOL "Forcing viewport orientation support for iPhone" FORCE)
	
		# CMake 2.8.1 added the ability to specify per-target architectures.
		# As a side effect, it creates corrupt Xcode projects if you try do it for the whole project.
		if(VERSION STRLESS "2.8.1")
			set(CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
		else()
			if (XSILIUM_BUILD_IPHONE_UNIV)
				set(CMAKE_OSX_ARCHITECTURES "armv6;armv7;i386")
			else()
				set(CMAKE_OSX_ARCHITECTURES "armv7;i386")
			endif()
		endif()
	
		add_definitions(-fno-regmove)
		remove_definitions(-msse)
	
		if (OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE)
			set(OGRE_SET_DISABLE_VIEWPORT_ORIENTATIONMODE 0)
		endif()
	
		if (XSILIUM_BUILD_GLES2RS)
			set(XSILIUM_BUILD_GLESRS FALSE CACHE BOOL "Forcing remove GLESRS"   FORCE)
		else()
			set(XSILIUM_BUILD_GLESRS TRUE CACHE BOOL "Forcing GLESRS"   FORCE)
		endif()
		

	elseif (APPLE)
	
		# Set 10.4 as the base SDK by default
		set(XCODE_ATTRIBUTE_SDKROOT macosx10.4)
	
		if (NOT CMAKE_OSX_ARCHITECTURES)
			set(CMAKE_OSX_ARCHITECTURES "i386")
		endif()
	  
		# 10.6 sets x86_64 as the default architecture.
		# Because Carbon isn't supported on 64-bit and we still need it, force the architectures to ppc and i386
		#if(CMAKE_OSX_ARCHITECTURES MATCHES "x86_64" OR CMAKE_OSX_ARCHITECTURES MATCHES "ppc64")
		#	string(REPLACE "x86_64" "" CMAKE_OSX_ARCHITECTURES ${CMAKE_OSX_ARCHITECTURES})
		#	string(REPLACE "ppc64" "" CMAKE_OSX_ARCHITECTURES ${CMAKE_OSX_ARCHITECTURES})
		#endif()
	
		# Make sure that the OpenGL render system is selected for non-iPhone Apple builds
		
		set(XSILIUM_BUILD_GLRS    TRUE  CACHE BOOL "Forcing GLRS"   FORCE)
		set(XSILIUM_BUILD_GLESRS  FALSE CACHE BOOL "Forcing remove GLESRS"   FORCE)
        	set(XSILIUM_BUILD_GLES2RS FALSE CACHE BOOL "Forcing remove GLES2RS"   FORCE)
	endif ()


	if (XSILIUM_COMPILE_SWIG)
		include(RunSwig)
	endif()


	if (XSILIUM_COMPILE_TCL)	
		include(TemplateCompiler)
	endif()
	
	set(XSILIUM_FREETYPE_INCLUDE ${XSILIUM_DEP_DIR}/freetype/include)	
set(XSILIUM_ZZIP_INCLUDE ${XSILIUM_DEP_DIR}/ZZipLib)
	set(XSILIUM_OIS_INCLUDE ${XSILIUM_DEP_DIR}/OIS/include)
	set(XSILIUM_OGRE_INCLUDE ${OGREPATH}/OgreMain/include ${OGREPATH}/Components/Overlay/include ${OGREPATH}/Components/Paging/include ${OGREPATH}/Components/Terrain/include ${XSILIUM_BINARY_DIR}/include ${XSILIUM_PLATFORM})	
	
	set(XSILIUM_TINYXML_INCLUDE ${XSILIUM_DEP_DIR}/TinyXml)
	set(XSILIUM_DEP_INCLUDE
#		${XSILIUM_FREEIMAGE_INCLUDE}
		${XSILIUM_FREETYPE_INCLUDE}
		${XSILIUM_ZLIB_INCLUDE}
		${XSILIUM_OIS_INCLUDE}	
	)
	
	
	
	if (WIN32 AND NOT (XSILIUM_BUILD_ANDROID OR XSILIUM_BUILD_NACL))
		# Use static library. No SDK needed at build time.
		# Must have OpenAL32.dll installed on the system 
		# In order to use OpenAL sound.
		set(OPENAL_FOUND TRUE)
	endif()


	if (OPENAL_FOUND)
		option(XSILIUM_OPENAL_SOUND "Enable building of the OpenAL subsystem" ON)
		
		if (WIN32)
			add_definitions(-DAL_STATIC_LIB -DALC_STATIC_LIB)
			set(XSILIUM_OPENAL_INCLUDE ${XSILIUM_DEP_DIR}/OpenAL/)
			set(XSILIUM_OPENAL_LIBRARY OpenAL)
		else()
			set(XSILIUM_OPENAL_INCLUDE ${OPENAL_INCLUDE_DIR})
			set(XSILIUM_OPENAL_LIBRARY ${OPENAL_LIBRARY})
		endif()
	else()
		option(XSILIUM_OPENAL_SOUND "Enable building of the OpenAL subsystem" OFF)
	endif()

	set(XSILIUM_MINGW_DIRECT3D TRUE)
	if (CMAKE_COMPILER_IS_GNUCXX)
		# Some Issues with unresolved symbols
		set(XSILIUM_MINGW_DIRECT3D FALSE)
	endif()


	if (WIN32)
		if (NOT DirectX_FOUND OR NOT XSILIUM_MINGW_DIRECT3D)
			# Default use OIS without dinput 

			option(XSILIUM_OIS_WIN32_NATIVE "Enable building of the OIS Win32 backend" ON)
		else ()
			# Use standard OIS build.
			# CAUTION: For now there are some missing symbols, which work with native fine. So for now lets set it to native as default
			option(XSILIUM_OIS_WIN32_NATIVE "Enable building of the OIS Win32 backend" On)
		endif()
	endif()

	
	if (OPENGL_FOUND)
		option(XSILIUM_BUILD_GLRS "Enable the OpenGL render system" ON)
	endif()
	
	if (OPENGLES_FOUND)
		option(XSILIUM_BUILD_GLESRS "Enable the OpenGLES system" ON)
	endif()
	
    if (OPENGLES2_FOUND)
        if (MSVC)
            option(XSILIUM_BUILD_GLES2RS "Enable the OpenGLES2 system" OFF)
        else()
            option(XSILIUM_BUILD_GLES2RS "Enable the OpenGLES2 system" ON)
        endif()
        
        #mark_as_advanced(XSILIUM_BUILD_GLES2RS)
	endif()
	
	if (XSILIUM_BUILD_GLRS)
	   set(OGRE_BUILD_RENDERSYSTEM_GL TRUE  CACHE BOOL "Forcing OpenGL RenderSystem" FORCE)
	else()
	   set(OGRE_BUILD_RENDERSYSTEM_GL FALSE CACHE BOOL "Forcing remove OpenGL RenderSystem" FORCE)
	endif()
	
	if (XSILIUM_BUILD_GLESRS)
	   set(OGRE_BUILD_RENDERSYSTEM_GLES TRUE  CACHE BOOL "Forcing OpenGLES RenderSystem" FORCE)
	else()
	   set(OGRE_BUILD_RENDERSYSTEM_GLES FALSE CACHE BOOL "Forcing remove OpenGLES RenderSystem" FORCE)
	endif()
	
	if (XSILIUM_BUILD_GLES2RS)	   
	   set(OGRE_BUILD_RENDERSYSTEM_GLES2 TRUE  CACHE BOOL "Forcing OpenGLES2 RenderSystem" FORCE)       
	else()
	   set(OGRE_BUILD_RENDERSYSTEM_GLES2 FALSE CACHE BOOL "Forcing remove OpenGLES2 RenderSystem" FORCE)
	endif()

	if (XSILIUM_BUILD_GL3PLUS)	   
	   set(OGRE_BUILD_RENDERSYSTEM_GL3PLUS TRUE  CACHE BOOL "Forcing OpenGLES3PLUS RenderSystem" FORCE)       
	else()
	   set(OGRE_BUILD_RENDERSYSTEM_GL3PLUS FALSE CACHE BOOL "Forcing remove OpenGLES3PLUS RenderSystem" FORCE)
	endif()



	
	mark_as_advanced(
	   OGRE_BUILD_RENDERSYSTEM_GL 
	   OGRE_BUILD_RENDERSYSTEM_GLES 
	   OGRE_BUILD_RENDERSYSTEM_GLES2
	)

	if (OPENGL_FOUND AND XSILIUM_BUILD_GLRS)
		set(OGRE_BUILD_RENDERSYSTEM_GL  TRUE)
		set(XSILIUM_GLRS_LIBS           RenderSystem_GL)
		set(XSILIUM_GLRS_ROOT           ${OGREPATH}/RenderSystems/GL)
		set(XSILIUM_GLESRS_INCLUDE      ${OGREPATH}/RenderSystems/GLES/include)
		set(XSILIUM_GLRS_INCLUDE        ${OGREPATH}/RenderSystems/GL/include)
	endif()

	if (OPENGLES_FOUND AND XSILIUM_BUILD_GLESRS)		
		set(OGRE_BUILD_RENDERSYSTEM_GLES TRUE)
		set(XSILIUM_GLESRS_LIBS          RenderSystem_GLES)
		set(XSILIUM_GLESRS_ROOT          ${OGREPATH}/RenderSystems/GLES)
		set(XSILIUM_GLESRS_INCLUDE       ${OGREPATH}/RenderSystems/GLES/include)
		set(XSILIUM_GLRS_INCLUDE         ${OGREPATH}/RenderSystems/GL/include)
	endif()

	if (OPENGLES2_FOUND AND XSILIUM_BUILD_GLES2RS)	
		set(OGRE_BUILD_RENDERSYSTEM_GLES2  TRUE)
		set(XSILIUM_GLES2RS_LIBS           RenderSystem_GLES2)
		set(XSILIUM_GLES2RS_ROOT           ${OGREPATH}/RenderSystems/GLES2)
		set(XSILIUM_GLES2RS_INCLUDE        ${OGREPATH}/RenderSystems/GLES2/include)
		set(XSILIUM_RTSHADERSYSTEM_INCLUDE ${OGREPATH}/Components/RTShaderSystem/include)
		set(XSILIUM_GLRS_INCLUDE           ${OGREPATH}/RenderSystems/GL/include)
	endif()

	if (OPENGLES_FOUND AND XSILIUM_BUILD_GL3PLUS )		
		set(OGRE_BUILD_RENDERSYSTEM_GL3PLUS TRUE)
		set(XSILIUM_GLESRS_LIBS          RenderSystem_GLESPLUS)
		set(XSILIUM_GLESRS_ROOT          ${OGREPATH}/RenderSystems/GL3Plus)
		set(XSILIUM_GLESRS_INCLUDE       ${OGREPATH}/RenderSystems/GL3Plus/include)
		set(XSILIUM_GLRS_INCLUDE         ${OGREPATH}/RenderSystems/GL/include)
	endif()

	if (WIN32 AND XSILIUM_MINGW_DIRECT3D)

		if (DirectX_FOUND)
			option(XSILIUM_BUILD_D3D9RS	 "Enable the Direct3D 9 render system" ON)
			option(XSILIUM_BUILD_D3D11RS "Enable the Direct3D 11 render system" OFF)
		endif()

		if (DirectX_FOUND AND XSILIUM_BUILD_D3D9RS)
			set(OGRE_BUILD_RENDERSYSTEM_D3D9   TRUE)
			set(XSILIUM_D3D9_LIBS              RenderSystem_Direct3D9)
			set(XSILIUM_D3D9_ROOT              ${OGREPATH}/RenderSystems/Direct3D9)
			set(XSILIUM_DX9RS_INCLUDE          ${OGREPATH}/RenderSystems/Direct3D9/include)
		endif()


		if (DirectX_FOUND AND XSILIUM_BUILD_D3D11RS)
			set(OGRE_BUILD_RENDERSYSTEM_D3D11  TRUE)
			set(XSILIUM_D3D11_LIBS             RenderSystem_Direct3D11)
			set(XSILIUM_D3D11_ROOT             ${OGREPATH}/RenderSystems/Direct3D11)
			set(XSILIUM_DX11RS_INCLUDE         ${OGREPATH}/RenderSystems/Direct3D11/include)
		endif()


	endif()
	

	set(OGRE_LIB OgreMain OgreTerrain OgreOverlay OgrePaging )     	

	if (XSILIUM_USE_RTSHADER_SYSTEM)
		list(APPEND OGRE_LIBS		OgreRTShaderSystem)
	endif()
		
	#Check Build Settings
	if (APPLE)
		if ( NOT XSILIUM_BUILD_IPHONE)			
			if (NOT XSILIUM_BUILD_GLRS)
				message(SEND_ERROR "Turn ON XSILIUM_BUILD_GLRS Option for OS X")
			endif()
			if (XSILIUM_BUILD_GLESRS OR XSILIUM_BUILD_GLESRS)
				message(SEND_ERROR "Turn OFF XSILIUM_BUILD_GLESRS or XSILIUM_BUILD_GLES2RS Option for OS X")
			endif()
		endif()
	endif(APPLE)

set(XSILIUM_LIB ${OGRE_LIB}
		CEGUIBase
		PagedGeometry 
		CEGUIOgreRenderer 
		${SKYX_LIBRARY}  
		${HYDRAX_LIBRARY}   
		${Boost_LIBRARIES} 
		${Cg_LIBRARY_REL}
		${XSILIUM_OIS_TARGET}
		${XSILIUM_ZZIP_TARGET}
		${ENET_LIBRARY_REL}
)

if(WIN32 AND DirectX_FOUND)
list(APPEND XSILIUM_LIB ${XSILIUM_D3D9_LIBS}
		${XSILIUM_D3D11_LIBS}
)
endif()

set(XSILIUM_INCLUDE ${XSILIUM_OGRE_INCLUDE}
		    ${FREETYPE_H_PATH}
                    ${XSILIUM_BULLET_INCLUDE}
                    ${XSILIUM_DEP_INCLUDE}
                    ${XSILIUM_SOURCE_DIR}/Engine
                    ${OIS_INCLUDE_DIR}
		    ${ENET_INCLUDE_DIR}
		    ${XSILIUM_SOURCE_DIR}/Library/Cegui/cegui/include
		    ${XSILIUM_BINARY_DIR}/Library/Cegui/cegui/include
		    ${OGREPAGE_H_PATH}
		    ${HYDRAX_H_PATH}
		    ${SKYX_H_PATH}
		    ${Cg_INCLUDE_DIR}
                    ${RAPIDXML_H_PATH}
                    ${XSILIUM_GLRS_INCLUDE}
                    )

endmacro(configure_xsilium)

