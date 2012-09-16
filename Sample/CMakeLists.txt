include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/include)

  # Make sure all plugins are built
  if (OGRE_BUILD_PLUGIN_OCTREE)
	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} Plugin_OctreeSceneManager)
  endif ()
  if (OGRE_BUILD_PLUGIN_BSP)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} Plugin_BSPSceneManager)
  endif ()
  if (OGRE_BUILD_PLUGIN_CG)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} Plugin_CgProgramManager)
  endif (OGRE_BUILD_PLUGIN_CG)
  if (OGRE_BUILD_PLUGIN_PFX)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} Plugin_ParticleFX)
  endif ()
  
  if (OGRE_BUILD_PLUGIN_PCZ)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} Plugin_PCZSceneManager)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} Plugin_OctreeZone)
  endif ()
  
  if (OGRE_BUILD_COMPONENT_RTSHADERSYSTEM)
	add_definitions(-DUSE_RTSHADER_SYSTEM)
	ogre_add_component_include_dir(RTShaderSystem)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} OgreRTShaderSystem)
  endif ()
  
  if (OGRE_BUILD_COMPONENT_TERRAIN)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} OgreTerrain)
  endif ()

  if (OGRE_BUILD_RENDERSYSTEM_D3D9)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} RenderSystem_Direct3D9)
  endif ()
  if (OGRE_BUILD_RENDERSYSTEM_D3D11)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} RenderSystem_Direct3D11)
  endif ()
  if (OGRE_BUILD_RENDERSYSTEM_GL)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} RenderSystem_GL)
  endif ()
  if (OGRE_BUILD_RENDERSYSTEM_GLES)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} RenderSystem_GLES)
  endif ()
  if (OGRE_BUILD_RENDERSYSTEM_GLES2)
  	set(SAMPLE_DEPENDENCIES ${SAMPLE_DEPENDENCIES} RenderSystem_GLES2)
  endif ()
  if (APPLE)
    if (OGRE_BUILD_PLATFORM_APPLE_IOS)
      set(OGRE_LIBRARIES ${OGRE_LIBRARIES})
    else ()
      set(OGRE_LIBRARIES ${OGRE_LIBRARIES} IOKit)
    endif ()
  endif ()
  
  #add_subdirectory(Character)
  add_subdirectory(common)
  add_subdirectory(Demo6)
  

  
# Install sample sources
if (OGRE_INSTALL_SAMPLES_SOURCE)
  if (WIN32 OR APPLE)
    set(OGRE_SAMPLES_DIR Samples)
  elseif (UNIX)
    set(OGRE_SAMPLES_DIR share/OGRE/Samples)
  endif ()
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION ${OGRE_SAMPLES_DIR}
    REGEX "^CMakeLists.txt$" EXCLUDE
    PATTERN "Makefile.am" EXCLUDE
    PATTERN "Media" EXCLUDE
    PATTERN "bin" EXCLUDE
    PATTERN "setup" EXCLUDE
    PATTERN ".hg" EXCLUDE
	PATTERN "obj" EXCLUDE
	PATTERN "scripts" EXCLUDE
  )
  # install a new CMakeLists.txt file to allow building of samples
  configure_file(${OGRE_TEMPLATES_DIR}/SDK_CMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/../CMakeLists.txt @ONLY)
  configure_file(${OGRE_TEMPLATES_DIR}/SDK_Samples_CMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/../CMakeLists.txt DESTINATION ${OGRE_SAMPLES_DIR}/../)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt DESTINATION ${OGRE_SAMPLES_DIR})
endif ()

# Install sample headers, some people rely on these
file(GLOB SAMPLE_COMMON_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Common/include/*.h")
install(FILES ${SAMPLE_COMMON_HEADERS}
		DESTINATION include/OGRE)
		
if (MSVC)
  find_package(Wix)
  if (Wix_FOUND)
    # Create WiX setup for demo build
    configure_file(${OGRE_TEMPLATES_DIR}/demos.wxs.in ${CMAKE_CURRENT_BINARY_DIR}/demos.wxs @ONLY)
    configure_file(${OGRE_TEMPLATES_DIR}/demomedia.wxi.in ${CMAKE_CURRENT_BINARY_DIR}/demomedia.wxi @ONLY)
    configure_file(${OGRE_TEMPLATES_DIR}/DemoLicense.rtf ${CMAKE_CURRENT_BINARY_DIR}/DemoLicense.rtf COPYONLY)
    if (MSVC_VERSION EQUAL 1400)
      configure_file(${OGRE_TEMPLATES_DIR}/vcrt_vc8.wxi.in ${CMAKE_CURRENT_BINARY_DIR}/vcrt.wxi @ONLY)
    elseif(MSVC_VERSION EQUAL 1500)
      configure_file(${OGRE_TEMPLATES_DIR}/vcrt_vc9.wxi.in ${CMAKE_CURRENT_BINARY_DIR}/vcrt.wxi @ONLY)
    endif()
	# Configure files, set media dir temporarily
	set(OGRE_MEDIA_DIR_TMP ${OGRE_MEDIA_DIR_REL})
	set(OGRE_MEDIA_DIR_REL "Media")
    configure_file(${OGRE_TEMPLATES_DIR}/resources.cfg.in ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg @ONLY)
    configure_file(${OGRE_TEMPLATES_DIR}/quakemap.cfg.in ${CMAKE_CURRENT_BINARY_DIR}/quakemap.cfg @ONLY)
	# restore
	set(OGRE_MEDIA_DIR_REL ${OGRE_MEDIA_DIR_TMP})
    add_custom_target(demo_installer 
	  COMMAND ${Wix_BINARY_DIR}/candle demos.wxs 
	  COMMAND ${Wix_BINARY_DIR}/light -ext WixUIExtension -cultures:en-us -out OgreDemos_v${OGRE_VERSION_DASH_SEPARATED}.msi demos.wixobj
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Building demo installer" VERBATIM
    )
	# Make sure we build samples first
	add_dependencies(demo_installer SampleBrowser)
  endif()
endif()
