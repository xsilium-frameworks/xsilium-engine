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
	  set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
	endif ()

	set(XSILIUM_INSTALL_PREFIX ${ROOT})
	
	option(XSILIUM_COMPILE_SWIG				"Enable compile time SWIG generation."  OFF)
	option(XSILIUM_COMPILE_OGRE_SCRIPTS		"Automatically convert Blender TX to Ogre (.material, .font, .overlay... etc)" ON)
	option(XSILIUM_COMPILE_WXWIDGETS		"Enable / Disable wxWidgets builds" OFF)
	option(XSILIUM_DEBUG_ASSERT				"Enable / Disable debug asserts." ON)
	option(XSILIUM_HEADER_GENERATOR			"Build Blender DNA to C++ generator."   OFF)
	option(XSILIUM_DISABLE_ZIP				"Disable external .zip resource loading" ON)
	option(XSILIUM_USE_STATIC_FREEIMAGE		"Compile and link statically FreeImage and all its plugins" ON)	
	option(XSILIUM_MINIMAL_FREEIMAGE_CODEC	"Compile minimal FreeImage Codec(PNG/JPEG/TGA)" OFF)
	option(XSILIUM_COMPILE_TINYXML			"Enable / Disable TinyXml builds" OFF)
	option(XSILIUM_GENERATE_BUILTIN_RES		"Generate build-in resources" OFF)
	option(XSILIUM_COMPILE_TCL				"Compile TemplateGenerator" OFF)
	option(XSILIUM_USE_PROCESSMANAGER       "Enable / Disable ProcessManager build" ON)
	option(XSILIUM_COMPILE_SOFTBODY			"Eanble / Disable Bullet Softbody build" OFF)
	option(XSILIUM_USE_NNODE				"Use Logic Node(It's Nodal Logic, not Blender LogicBrick)" OFF)
	option(XSILIUM_USE_PARTICLE				"Use Paritcle" ON)
	option(XSILIUM_COMPILE_OGRE_COMPONENTS	"Eanble compile additional Ogre components (RTShader, Terrain, Paging, ... etc)" ON)
	option(XSILIUM_USE_RTSHADER_SYSTEM		"Eanble shader system instead of fixed piped functions." OFF)
	option(XSILIUM_USE_COMPOSITOR			"Enable post effect by compositor (Bloom, BlackAndWhite, HDR, ...)" OFF)
	option(XSILIUM_USE_COMPOSITOR_TEX		"Add Compositor texture resources (NightVision, HeatVision, ...)" OFF)
	option(XSILIUM_COMPILE_OPTS				"Enable / Disable Opts builds" OFF)	
	set(OGRE_UNITY_FILES_PER_UNIT "40" CACHE STRING "Number of files per compilation unit in Unity build.")
	
	if (APPLE)
		option(XSILIUM_BUILD_IPHONE	"Build Xsilium on iOS SDK"	OFF)
		option(XSILIUM_BUILD_IPHONE_UNIV "Support arm6 architecture for old device" OFF)
	endif()

	option(XSILIUM_BUILD_ANDROID	"Build Xsilium on Android SDK"	OFF)
	
	if (XSILIUM_BUILD_ANDROID OR XSILIUM_BUILD_IPHONE)
		set(XSILIUM_BUILD_MOBILE 1)
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


	set(OGRE_BUILD_PLUGIN_OCTREE TRUE CACHE BOOL "Forcing Plugins" )
	set(OGRE_BUILD_PLUGIN_BSP TRUE CACHE BOOL "Forcing Plugins" )
	set(OGRE_BUILD_PLUGIN_PFX TRUE CACHE BOOL "Forcing Plugins" )
	set(OGRE_BUILD_PLUGIN_PCZ TRUE CACHE BOOL "Forcing Plugins" )
	set(OGRE_BUILD_PLUGIN_CG TRUE CACHE BOOL "Forcing Plugins" )


	set(OGRE_USE_BOOST TRUE CACHE BOOL "Forcing use BOOST" ) 

	set(Boost_ADDITIONAL_VERSIONS "1.52.0 1.49.0 1.48.0")

	set(OGRE_BOOST_COMPONENTS thread date_time system)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)

	include_directories("${Boost_INCLUDE_DIRS}")

	find_package(Cg)
	
	set(XSILIUM_ZZIP_TARGET ZZipLib)
	set(XSILIUM_FREETYPE_TARGET freetype)
	set(XSILIUM_OIS_TARGET OIS)
	
	set(XSILIUM_DEP_DIR ${ROOT}/Library/Dependencies/Source)
	set(OGRE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
	set(OGRE_TEMPLATES_DIR ${ROOT}/CMake/Templates)
	set(OGRELITE_SOURCE_DIR ${OGREPATH})
	set(XSILIUM_ANDROID_DEP_DIR ${ROOT}/Library/Dependencies/Android)
	
	include(OgreConfigTargets)
	include(DependenciesXsilium)
	include(MacroLogFeature)


	if (NOT XSILIUM_USE_STATIC_FREEIMAGE)
	
		if(ZLIB_FOUND)
			set(XSILIUM_ZLIB_TARGET	${ZLIB_LIBRARY})
			set(XSILIUM_ZLIB_INCLUDE	${ZLIB_INCLUDE_DIR})
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
	
		set(XSILIUM_ZLIB_TARGET	zlib)
		set(XSILIUM_FREEIMAGE_TARGET FreeImage)
		set(XSILIUM_ZLIB_INCLUDE ${XSILIUM_DEP_DIR}/zlib)
		set(XSILIUM_FREEIMAGE_INCLUDE ${XSILIUM_DEP_DIR}/FreeImage/Source)        
		
	endif()

set (FREEIMAGE_H_PATH ${XSILIUM_FREEIMAGE_INCLUDE} )
set (FREEIMAGE_LIB ${XSILIUM_FREEIMAGE_TARGET} )
set (FREEIMAGE_LIB_DBG ${XSILIUM_FREEIMAGE_TARGET} )



set( XERCESC_H_PATH "${XSILIUM_DEP_DIR}/xerces-c" )
set( XERCESC_LIB "Xerces" )
set( XERCESC_LIB_DBG "Xerces" )

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

	
	if (NOT XSILIUM_USE_LUA)
		set(XSILIUM_COMPILE_SWIG FALSE CACHE BOOL "Disabling Swig" FORCE)
	endif()
	
	if (SAMPLES_LUA_EDITOR)
		set(XSILIUM_COMPILE_TINYXML TRUE CACHE BOOL "Forcing TinyXml" FORCE)
		set(SAMPLES_LUARUNTIME TRUE CACHE BOOL "Forcing LuaRuntime" FORCE)
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
		set(OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE FALSE CACHE BOOL "Forcing viewport orientation support for Android" FORCE)
		if (NOT OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE)
			set(OGRE_SET_DISABLE_VIEWPORT_ORIENTATIONMODE 1)
		endif()

		#message(${XSILIUM_BUILD_GLRS} "---" ${XSILIUM_BUILD_GLESRS} " --- " ${OPENGLES2_gl_LIBRARY})
		
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
	
		if (NOT OGRE_CONFIG_ENABLE_VIEWPORT_ORIENTATIONMODE)
			set(OGRE_SET_DISABLE_VIEWPORT_ORIENTATIONMODE 1)
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
		if(CMAKE_OSX_ARCHITECTURES MATCHES "x86_64" OR CMAKE_OSX_ARCHITECTURES MATCHES "ppc64")
			string(REPLACE "x86_64" "" CMAKE_OSX_ARCHITECTURES ${CMAKE_OSX_ARCHITECTURES})
			string(REPLACE "ppc64" "" CMAKE_OSX_ARCHITECTURES ${CMAKE_OSX_ARCHITECTURES})
		endif()
	
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
	set(XSILIUM_ZZIP_INCLUDE ${XSILIUM_DEP_DIR}/zziplib)
	set(XSILIUM_OIS_INCLUDE ${XSILIUM_DEP_DIR}/ois/includes)
	set(XSILIUM_OGRE_INCLUDE ${OGREPATH}/OgreMain/include ${OGREPATH}/Components/Terrain/include ${XSILIUM_BINARY_DIR}/include ${XSILIUM_PLATFORM})	
	set(OGRE_H_PATH ${XSILIUM_OGRE_INCLUDE})

	set(XSILIUM_DEP_INCLUDE
#		${XSILIUM_FREEIMAGE_INCLUDE} Conflicts with OpenSteer includes and needed by Ogre, not XSILIUM
		${XSILIUM_FREETYPE_INCLUDE}
		${XSILIUM_ZLIB_INCLUDE}
		${XSILIUM_OIS_INCLUDE}						
	)

	set(FREETYPE_H_PATH_ft2build ${XSILIUM_FREETYPE_INCLUDE} )
        set(FREETYPE_H_PATH_ftconfig ${XSILIUM_FREETYPE_INCLUDE} )
	set(FREETYPE_LIB ${XSILIUM_FREETYPE_TARGET} )
	set(FREETYPE_LIB_DBG ${XSILIUM_FREETYPE_TARGET} )

	message(STATUS "DEP_INCLUDES: ${XSILIUM_DEP_INCLUDE}")

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
	

	set(XSILIUM_OGRE_LIBS 
		OgreMain       
	)    
	set(OGRE_LIB ${XSILIUM_OGRE_LIBS})
	
	# ogre 1.8-compatability
	#list(APPEND XSILIUM_OGRE_LIBS OgreTerrain)  

	list(APPEND XSILIUM_OGRE_LIBS 	${XSILIUM_FREEIMAGE_TARGET} 
		${XSILIUM_FREETYPE_TARGET}
		${XSILIUM_GLRS_LIBS}        
		${XSILIUM_D3D9_LIBS}
		${XSILIUM_D3D11_LIBS}		
		${XSILIUM_OIS_TARGET}
		${XSILIUM_ZLIB_TARGET}
	)	

	if (XSILIUM_USE_RTSHADER_SYSTEM)
		list(APPEND XSILIUM_OGRE_LIBS		OgreRTShaderSystem)
		list(APPEND XSILIUM_OGRE_INCLUDE	${OGREPATH}/Components/RTShaderSystem/include)
	endif()

	if (NOT XSILIUM_DISABLE_ZIP)
		list(APPEND XSILIUM_OGRE_LIBS	${XSILIUM_ZZIP_TARGET})
		list(APPEND XSILIUM_DEP_INCLUDE ${XSILIUM_ZZIP_INCLUDE})
	endif()
		
	#Check Build Settings
	if (APPLE)
		if (XSILIUM_BUILD_IPHONE)
						
			if (XSILIUM_BUILD_GLRS)
				message(SEND_ERROR "Turn OFF XSILIUM_BUILD_GLRS Option for iOS")
			endif()
			if (NOT XSILIUM_BUILD_GLESRS AND NOT XSILIUM_BUILD_GLES2RS)
				message(SEND_ERROR "Turn ON XSILIUM_BUILD_GLESRS or XSILIUM_BUILD_GLES2RS Option for iOS")
			endif()
			
			if(VERSION STRLESS "2.8.2")
				message(ERROR "You should update the CMake 2.8.2 higher for iOS build.")
	  		endif()
	  
		else()
			
			if (NOT XSILIUM_BUILD_GLRS)
				message(SEND_ERROR "Turn ON XSILIUM_BUILD_GLRS Option for OS X")
			endif()
			if (XSILIUM_BUILD_GLESRS OR XSILIUM_BUILD_GLESRS)
				message(SEND_ERROR "Turn OFF XSILIUM_BUILD_GLESRS or XSILIUM_BUILD_GLES2RS Option for OS X")
			endif()

		endif()
	endif(APPLE)



endmacro(configure_xsilium)


macro(configure_rendersystem)

	if (OGRE_BUILD_RENDERSYSTEM_GL)
		
		include_directories(
			${XSILIUM_GLRS_ROOT}/include
			${XSILIUM_GLRS_ROOT}/src/GLSL/include
			${XSILIUM_GLRS_ROOT}/src/atifs/include
		)
	
		link_libraries(
			${XSILIUM_GLRS_LIBS} 
			${OPENGL_gl_LIBRARY}
			${OPENGL_glu_LIBRARY}
		)
		
	endif()

	if (OGRE_BUILD_RENDERSYSTEM_GLES)
		
		include_directories(
			${XSILIUM_GLESRS_ROOT}/include
			${XSILIUM_GLESRS_ROOT}/include/EAGL
		)
	
		link_libraries(
			${XSILIUM_GLESRS_LIBS} 
		)
		
	endif()

	if (OGRE_BUILD_RENDERSYSTEM_GLES2)
		
		include_directories(
			${XSILIUM_GLES2RS_ROOT}/include
			${XSILIUM_RTSHADERSYSTEM_INCLUDE}
		)
	
		link_libraries(
			${XSILIUM_GLES2RS_LIBS} 
		)
        
        if (MSVC)
            include_directories(${OPENGLES2_INCLUDE_DIR})
            #link_directories(${OPENGLES2_LIBRARY_PATH})
            list(APPEND XSILIUM_OGRE_LIBS ${OPENGLES_gl_LIBRARY})
            #message(STATUS ${XSILIUM_OGRE_LIBS})
        endif()
		
		message(STATUS "--------" ${XSILIUM_GLES2RS_LIBS} )
		
	endif()
	
	if (XSILIUM_BUILD_D3D9RS)

		include_directories(
			${XSILIUM_D3D9_ROOT}/include
		)
		
		link_libraries(
			${DirectX_D3D9_LIBRARY}
			${XSILIUM_D3D9_LIBS} 
		)
			
	endif()
	

	if (XSILIUM_BUILD_D3D11RS AND DirectX_D3D11_FOUND)
		
		include_directories(
			${XSILIUM_D3D11_ROOT}/include
		)
		
		link_libraries(
			${XSILIUM_D3D11_LIBS} 
			${DirectX_D3D10_LIBRARIES}
		)

	endif()
	
endmacro(configure_rendersystem)

