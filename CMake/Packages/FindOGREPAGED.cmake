# Find CEGUI includes and library
#
# This module defines
#  OGRE_PAGED_INCLUDE_DIR
#  OGRE_PAGED_LIBRARY, the library to link against to use CEGUI.
#  OGRE_PAGED_FOUND, If false, do not try to use CEGUI
#
# Input:
#  ${OGRE_PAGED_SOURCE}, OGRE_PAGED path source
#  ${OGRE_PAGED_BUILD}, OGRE_PAGED path build
#
# Created by Matt Williams to find OGRE libraries
# Copyright � 2007, Matt Williams
#
# Modified by Nicolas Schlumberger to find OGRE_PAGED libraries
# and make it run on the Tardis-Infrastucture of the ETH Zurich
# Copyright 2007, Nicolas Schlumberger

include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(OGRE_PAGED)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(OGRE_PAGED_SOURCE)
getenv_path(OGRE_PAGED_BUILD)

# Find OGRE_PAGED headers
FIND_PATH(OGRE_PAGED_INCLUDE_DIR PagedGeometry.h
  PATHS ${OGRE_PAGED_SOURCE}
  PATH_SUFFIXES include
)

# Find OGRE_PAGED library
FIND_LIBRARY(OGRE_PAGED_LIBRARY_OPTIMIZED
  NAMES PagedGeometry
  PATHS ${OGRE_PAGED_BUILD}
  PATH_SUFFIXES lib bin
)

if ("${OGRE_PAGED_LIBRARY_OPTIMIZED}" STREQUAL "OGRE_PAGED_LIBRARY_OPTIMIZED-NOTFOUND")
set(OGRE_PAGED_LIBRARY_OPTIMIZED "")
endif()

set(OGRE_PAGED_LIBRARY
${OGRE_PAGED_LIBRARY_OPTIMIZED}
)

set(OGRE_PAGED_INCLUDE_DIR 
"${OGRE_PAGED_BUILD}include/"
${OGRE_PAGED_INCLUDE_DIR}
)

MARK_AS_ADVANCED(
  OGRE_PAGED_INCLUDE_DIR
  OGRE_PAGED_LIBRARY_OPTIMIZED
)
