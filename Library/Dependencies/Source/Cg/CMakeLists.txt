set(Cg_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE PATH "" FORCE)

if (WIN32)
  # manually copy to build and install the correct DLL
  if (XSILIUM_PLATFORM_X64)
    set(CG_DLL bin64/cg.dll)
    set(Cg_LIBRARY_REL "${CMAKE_CURRENT_SOURCE_DIR}/lib64/cg.lib" CACHE PATH "" FORCE)
    set(Cg_LIBRARY_DBG "${CMAKE_CURRENT_SOURCE_DIR}/lib64/cg.lib" CACHE PATH "" FORCE)
  else ()
    set(CG_DLL bin/cg.dll)
    set(Cg_LIBRARY_REL "${CMAKE_CURRENT_SOURCE_DIR}/lib/cg.lib" CACHE PATH "" FORCE)
    set(Cg_LIBRARY_DBG "${CMAKE_CURRENT_SOURCE_DIR}/lib/cg.lib" CACHE PATH "" FORCE)
  endif ()
  install(FILES ${CG_DLL} DESTINATION bin/Release)
  install(FILES ${CG_DLL} DESTINATION bin/Debug)
  if (MINGW)
    file(COPY ${CG_DLL} DESTINATION ${XSILIUM_RUNTIME_OUTPUT})
  else ()
    file(COPY ${CG_DLL} DESTINATION ${XSILIUM_RUNTIME_OUTPUT}/Debug)
    file(COPY ${CG_DLL} DESTINATION ${XSILIUM_RUNTIME_OUTPUT}/Release)
  endif ()
elseif (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
  add_custom_target(Cg COMMAND 
    unzip lib/Cg.framework.zip -d ${XSILIUM_BINARY_DIR}/../${XSILIUM_LIB_DIRECTORY}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Unzipping Cg framework" VERBATIM
  )
elseif (UNIX)
  # manually install the correct .so
  if (XSILIUM_PLATFORM_X64)
    install(FILES lib64/libCg.so DESTINATION ${XSILIUM_LIB_DIRECTORY})
    set(Cg_LIBRARY_REL "${CMAKE_CURRENT_SOURCE_DIR}/lib64/libCg.so" CACHE PATH "" FORCE)
    set(Cg_LIBRARY_DBG "${CMAKE_CURRENT_SOURCE_DIR}/lib64/libCg.so" CACHE PATH "" FORCE)
  else ()
    install(FILES lib/libCg.so DESTINATION ${XSILIUM_LIB_DIRECTORY})
    set(Cg_LIBRARY_REL "${CMAKE_CURRENT_SOURCE_DIR}/lib/libCg.so" CACHE PATH "" FORCE)
    set(Cg_LIBRARY_DBG "${CMAKE_CURRENT_SOURCE_DIR}/lib/libCg.so" CACHE PATH "" FORCE)
  endif ()
endif ()
