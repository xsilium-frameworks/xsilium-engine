project(Cg)

if (WIN32)
  set(Cg_HOME ${Cg_SOURCE_DIR} CACHE PATH "")

  # manually copy to build and install the correct DLL
  if (OGRE_PLATFORM_X64)
    set(CG_DLL bin64/cg.dll)
  else ()
    set(CG_DLL bin/cg.dll)
  endif ()
  install(FILES ${CG_DLL} DESTINATION bin/Release)
  install(FILES ${CG_DLL} DESTINATION bin/Debug)
  if (MINGW)
    file(COPY ${CG_DLL} DESTINATION ${XSILIUM_RUNTIME_OUTPUT})
  else ()
    file(COPY ${CG_DLL} DESTINATION ${XSILIUM_RUNTIME_OUTPUT}/Debug)
    file(COPY ${CG_DLL} DESTINATION ${XSILIUM_RUNTIME_OUTPUT}/Release)
  endif ()
endif ()

mark_as_advanced(Cg_HOME)