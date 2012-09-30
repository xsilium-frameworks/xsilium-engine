# Find CEGUI includes and library
#
# This module defines
#  CEGUI_INCLUDE_DIR
#  CEGUI_LIBRARY, the library to link against to use CEGUI.
#  CEGUILUA_LIBRARY, the library to link against to use the CEGUI script module.
#  CEGUI_TOLUA_LIBRARY, the library to link against to use Tolua++.
#  CEGUI_FOUND, If false, do not try to use CEGUI
#
# Input:
#  ${CEGUI_SOURCE}, CEGUI path source
#  ${CEGUI_BUILD}, CEGUI path build
#
# Created by Matt Williams to find OGRE libraries
# Copyright � 2007, Matt Williams
#
# Modified by Nicolas Schlumberger to find CEGUI libraries
# and make it run on the Tardis-Infrastucture of the ETH Zurich
# Copyright 2007, Nicolas Schlumberger

include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(CEGUI)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(CEGUI_SOURCE)
getenv_path(CEGUI_BUILD)

# Find CEGUI headers
FIND_PATH(CEGUI_INCLUDE_DIR CEGUI.h
  PATHS ${CEGUI_SOURCE}
  PATH_SUFFIXES include include/CEGUI
)

# Find CEGUI headers
FIND_PATH(CEGUI_INCLUDE_DIR CEGUI.h
  PATHS ${CEGUI_SOURCE}
  PATH_SUFFIXES include/CEGUI
)

# Find CEGUI library
FIND_LIBRARY(CEGUI_LIBRARY_OPTIMIZED
  NAMES CEGUIBase CEGUI
  PATHS ${CEGUI_BUILD}
  PATH_SUFFIXES lib bin
)
FIND_LIBRARY(CEGUI_LIBRARY_DEBUG
  NAMES
    CEGUIBased CEGUIBase_d CEGUIBaseD CEGUIBase_D
    CEGUId CEGUI_d CEGUID CEGUI_D
  PATHS ${CEGUI_BUILD}
  PATH_SUFFIXES lib bin
)

# Find CEGUILua headers
FIND_PATH(CEGUILUA_INCLUDE_DIR CEGUILua.h
  PATHS
    ${CEGUI_SOURCE}
    $ENV{CEGUILUADIR}
    ${CEGUI_INCLUDE_DIR}/ScriptingModules/LuaScriptModule
  PATH_SUFFIXES include include/CEGUI
)
# Find CEGUILua libraries
FIND_LIBRARY(CEGUILUA_LIBRARY_OPTIMIZED
  NAMES CEGUILua CEGUILuaScriptModule
  PATHS ${CEGUI_BUILD} $ENV{CEGUILUADIR}
  PATH_SUFFIXES lib bin
)
FIND_LIBRARY(CEGUILUA_LIBRARY_DEBUG
  NAMES CEGUILuad CEGUILua_d CEGUILuaScriptModuled CEGUILuaScriptModule_d
  PATHS ${CEGUI_BUILD} $ENV{CEGUILUADIR}
  PATH_SUFFIXES lib bin
)

# Find CEGUI Tolua++ include file
# We only need to add this path since we use tolua++ like a normal
# dependency but it is shipped with CEGUILua.
FIND_PATH(CEGUI_TOLUA_INCLUDE_DIR tolua++.h
  PATHS
    ${CEGUILUA_INCLUDE_DIR}
    # For newer CEGUI versions >= 0.7
    ${CEGUILUA_INCLUDE_DIR}/support/tolua++
    # For Mac OS X, tolua++ is a separate framework in the dependency package
    ${DEP_FRAMEWORK_DIR}
  NO_DEFAULT_PATH # Don't attempt to find tolua++ installed on the system
)
# Find CEGUI Tolua++ libraries
FIND_LIBRARY(CEGUI_TOLUA_LIBRARY_OPTIMIZED
  NAMES CEGUItoluapp tolua++ ceguitolua++ tolua++5.1
  PATHS ${CEGUI_BUILD} ${CEGUITOLUADIR}
  PATH_SUFFIXES lib bin
)
FIND_LIBRARY(CEGUI_TOLUA_LIBRARY_DEBUG
  NAMES CEGUItoluappd CEGUItoluapp_d tolua++d tolua++_d
  PATHS ${CEGUI_BUILD} ${CEGUITOLUADIR}
  PATH_SUFFIXES lib bin
)

# Newer versions of CEGUI have the renderer for OGRE shipped with them
  # Find CEGUI OGRE Renderer headers
  FIND_PATH(CEGUI_OGRE_RENDERER_INCLUDE_DIR Renderer.h
    PATHS
      ${CEGUI_HOME}
      $ENV{CEGUIOGRERENDERERDIR}
      ${CEGUI_INCLUDE_DIR}/RendererModules/Ogre
    PATH_SUFFIXES include include/CEGUI
  )
  # Find CEGUI OGRE Renderer libraries
  FIND_LIBRARY(CEGUI_OGRE_RENDERER_LIBRARY_OPTIMIZED
    NAMES CEGUIOgreRenderer
    PATHS ${CEGUI_BUILD} $ENV{CEGUIOGRERENDERERDIR}
    PATH_SUFFIXES lib bin
  )
  FIND_LIBRARY(CEGUI_OGRE_RENDERER_LIBRARY_DEBUG
    NAMES CEGUIOgreRendererd CEGUIOgreRenderer_d
    PATHS ${CEGUI_BUILD} $ENV{CEGUIOGRERENDERERDIR}
    PATH_SUFFIXES lib bin
  )
  SET(CEGUI_OGRE_RENDERER_REQUIRED_VARIABLES
    CEGUI_OGRE_RENDERER_INCLUDE_DIR
    CEGUI_OGRE_RENDERER_LIBRARY_OPTIMIZED
  )

set(CEGUI_LIBRARY
${CEGUI_LIBRARY_OPTIMIZED}
${CEGUI_OGRE_RENDERER_LIBRARY_OPTIMIZED}
)

set(CEGUILUA_LIBRARY
${CEGUILUA_LIBRARY_OPTIMIZED}
)

set(CEGUI_TOLUA_LIBRARY
${CEGUI_TOLUA_LIBRARY_OPTIMIZED}
)

add_parent_dir(CEGUI_INCLUDE_DIR CEGUI_INCLUDE_DIR)

set(CEGUI_INCLUDE_DIR 
"${CEGUI_BUILD}Library/Cegui/cegui/include"
${CEGUI_INCLUDE_DIR}
)

MARK_AS_ADVANCED(
  CEGUI_INCLUDE_DIR
  CEGUI_LIBRARY_OPTIMIZED
  CEGUI_LIBRARY_DEBUG
  CEGUILUA_INCLUDE_DIR
  CEGUILUA_LIBRARY_OPTIMIZED
  CEGUILUA_LIBRARY_DEBUG
  CEGUI_TOLUA_INCLUDE_DIR
  CEGUI_TOLUA_LIBRARY_OPTIMIZED
  CEGUI_TOLUA_LIBRARY_DEBUG
  CEGUI_OGRE_RENDERER_INCLUDE_DIR
  CEGUI_OGRE_RENDERER_LIBRARY_OPTIMIZED
  CEGUI_OGRE_RENDERER_LIBRARY_DEBUG
)
