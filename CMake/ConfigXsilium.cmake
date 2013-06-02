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
	option(XSILIUM_COMPILE_WXWIDGETS		"Enable / Disable wxWidgets builds" OFF)
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
	option(XSILIUM_USE_PARTICLE				"Use Paritcle" ON)
	option(XSILIUM_COMPILE_OGRE_COMPONENTS	"Eanble compile additional Ogre components (RTShader, Terrain, Paging, ... etc)" ON)
	option(XSILIUM_USE_RTSHADER_SYSTEM		"Eanble shader system instead of fixed piped functions." OFF)
	option(XSILIUM_USE_COMPOSITOR			"Enable post effect by compositor (Bloom, BlackAndWhite, HDR, ...)" OFF)
	option(XSILIUM_USE_COMPOSITOR_TEX		"Add Compositor texture resources (NightVision, HeatVision, ...)" OFF)
	option(XSILIUM_COMPILE_OPTS				"Enable / Disable Opts builds" OFF)
       option(XSILIUM_BUILD_GL3PLUS				"Enable / Disable Opts builds" OFF)	
	set(OGRE_UNITY_FILES_PER_UNIT "40" CACHE STRING "Number of files per compilation unit in Unity build.")
    
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
	endif()	
	
	
	if (XSILIUM_COMPILE_OGRE_COMPONENTS)
		option(OGRE_BUILD_COMPONENT_PAGING "Build Ogre Paging Compoment" ON)
		option(OGRE_BUILD_COMPONENT_TERRAIN "Build Ogre Terrain Compoment" ON)
		option(OGRE_BUILD_COMPONENT_OVERLAY "Build Ogre Overlay Compoment" ON)
		option(OGRE_BUILD_COMPONENT_VOLUME "Build Ogre Volume Compoment" ON)
		option(OGRE_BUILD_COMPONENT_RTSHADERSYSTEM "Build Ogre RTShaderSystem Compoment" OFF)
		option(OGRE_BUILD_COMPONENT_PROPERTY "Build Ogre Property Compoment(Required boost)" OFF)
	endif()


	set(OGRE_BUILD_PLUGIN_OCTREE TRUE CACHE BOOL "Forcing Plugins" )
	set(OGRE_BUILD_PLUGIN_BSP TRUE CACHE BOOL "Forcing Plugins" )
	set(OGRE_BUILD_PLUGIN_PFX TRUE CACHE BOOL "Forcing Plugins" )
	set(OGRE_BUILD_PLUGIN_PCZ TRUE CACHE BOOL "Forcing Plugins" )
	set(OGRE_BUILD_PLUGIN_CG TRUE CACHE BOOL "Forcing Plugins" )


	set(OGRE_USE_BOOST TRUE CACHE BOOL "Forcing use BOOST" ) 

	set(Boost_ADDITIONAL_VERSIONS "1.52.0 1.49.0 1.48.0")

	set(OGRE_BOOST_COMPONENTS thread date_time system filesystem)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)

	include_directories("${Boost_INCLUDE_DIRS}")
		
	include(DependenciesXsilium)
	include(MacroLogFeature)
		

	if (APPLE)
	
		# Set 10.4 as the base SDK by default
		set(XCODE_ATTRIBUTE_SDKROOT macosx10.4)
	
		if (NOT CMAKE_OSX_ARCHITECTURES)
			set(CMAKE_OSX_ARCHITECTURES "i386")
		endif()
	
		# Make sure that the OpenGL render system is selected for non-iPhone Apple builds
		
		set(XSILIUM_BUILD_GLRS    TRUE  CACHE BOOL "Forcing GLRS"   FORCE)
		set(XSILIUM_BUILD_GLESRS  FALSE CACHE BOOL "Forcing remove GLESRS"   FORCE)
        	set(XSILIUM_BUILD_GLES2RS FALSE CACHE BOOL "Forcing remove GLES2RS"   FORCE)
	endif ()

	set(OGRE_H_PATH 
	   ${OGREPATH}/OgreMain/include 
           ${OGREPATH}/Components/Terrain/include 
	   ${OGREPATH}/Components/Paging/include/
	   ${OGREPATH}/Components/Overlay/include 
	   ${OGREPATH}/Components/Volume/include 
           ${XSILIUM_BINARY_DIR}/include 
           ${XSILIUM_PLATFORM})	
		   
	set (RAPIDXML_H_PATH ${XSILIUM_SOURCE_DIR}/Library/Dependencies/Source/rapidxml-1.13 )

	set(XSILIUM_MINGW_DIRECT3D TRUE)
	if (CMAKE_COMPILER_IS_GNUCXX)
		# Some Issues with unresolved symbols
		set(XSILIUM_MINGW_DIRECT3D FALSE)
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
	

	set(OGRE_LIB OgreMain OgreTerrain )     	

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

# ---------------------------------------------------------
# Common base paths
set(XSILIUM_INCLUDE ${OGRE_H_PATH}
                    ${XSILIUM_SOURCE_DIR}/Engine
                    ${OIS_INCLUDE_DIR}
		    ${XSILIUM_SOURCE_DIR}/Library/Cegui/cegui/include
		    ${XSILIUM_SOURCE_DIR}/Library/Boost
		    ${XSILIUM_SOURCE_DIR}/Library/Enet
		    ${XSILIUM_BINARY_DIR}/Library/Cegui/cegui/include
		    ${XSILIUM_SOURCE_DIR}/Library/OgrePaged/include
		    ${XSILIUM_BINARY_DIR}/Library/OgrePaged/include
		    ${XSILIUM_SOURCE_DIR}/Library/Hydrax/include
		    ${XSILIUM_SOURCE_DIR}/Library/SkyX/Include
		    ${Cg_INCLUDE_DIR}
                    )

set(XSILIUM_LIB XsiliumEngine 
		${OGRE_LIB}
		CEGUIBase
		PagedGeometry 
		CEGUIOgreRenderer 
		SkyX 
		Hydrax 
		${Boost_LIBRARIES} 
		${Cg_LIBRARY_REL}
		${OIS_LIBRARY_REL} 
)



endmacro(configure_xsilium)

