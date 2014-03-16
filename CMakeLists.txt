# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)
   
project(XSILIUM)
SET(XSILIUM 1.0)
set(OGRE_STATIC FALSE)

# Fix x64 issues on Linux
include(CheckTypeSize)
CHECK_TYPE_SIZE("void*" XSILIUM_PTR_SIZE BUILTIN_TYPES_ONLY)
if (XSILIUM_PTR_SIZE EQUAL 8)
  set(XSILIUM_PLATFORM_X64 TRUE)
else ()
  set(XSILIUM_PLATFORM_X64 FALSE)
endif ()

# Add -fPIC flag to x64 GCC builds
if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
  if (XSILIUM_PLATFORM_X64 AND NOT APPLE)
    add_definitions(-fPIC)
  endif ()
endif ()

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if (MSVC)
	add_definitions( -D_WINSOCKAPI_ )

	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
	add_definitions( -D_CRT_SECURE_NO_DEPRECATE )
	add_definitions( -DNOMINMAX)

	add_definitions( -D_VARIADIC_MAX=10 ) #vs2012 tuple issue with gtest
endif()

if (XSILIUM_BUILD_IPHONE)    
	add_definitions(-DARM_NEON_GCC_COMPATIBILITY=1)
endif()

# ---------------------------------------------------------
set(CMAKE_MODULE_PATH
    ${XSILIUM_SOURCE_DIR}/CMake
    ${XSILIUM_SOURCE_DIR}/CMake/Utils
    ${XSILIUM_SOURCE_DIR}/CMake/Packages
    ${XSILIUM_SOURCE_DIR}/CMake/Templates
    )
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)
include(ConfigXsilium)
include(ConfigTargets)
include(OgreAddTargets)

configure_xsilium(${XSILIUM_SOURCE_DIR} ${XSILIUM_SOURCE_DIR}/Library/Ogre )


set(XSILIUM_BULLET_LIBS BulletDynamics BulletCollision  LinearMath)	
set(XSILIUM_BULLET_INCLUDE ${XSILIUM_SOURCE_DIR}/bullet/src)
if (XSILIUM_COMPILE_SOFTBODY)
	list(APPEND XSILIUM_BULLET_LIBS BulletSoftBody)
endif()


IF(MSVC)

	#We statically link to reduce dependancies
	FOREACH(flag_var    CMAKE_CXX_FLAGS 
	                    CMAKE_CXX_FLAGS_DEBUG 
	                    CMAKE_CXX_FLAGS_RELEASE 
	                    CMAKE_CXX_FLAGS_MINSIZEREL 
	                    CMAKE_CXX_FLAGS_RELWITHDEBINFO
	                    CMAKE_C_FLAGS_DEBUG
	                    CMAKE_C_FLAGS_RELEASE
	                    CMAKE_C_FLAGS_MINSIZEREL 
	                    CMAKE_C_FLAGS_RELWITHDEBINFO
	                    )
		IF(${flag_var} MATCHES "/MT")
			STRING(REGEX REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
		ENDIF(${flag_var} MATCHES "/MT")
		IF(${flag_var} MATCHES "/MTd")
			STRING(REGEX REPLACE "/MTd" "/MDd" ${flag_var} "${${flag_var}}")
		ENDIF(${flag_var} MATCHES "/MTd")
	ENDFOREACH(flag_var)

ENDIF(MSVC)

set(XSILIUM_INCLUDE ${XSILIUM_OGRE_INCLUDE}
		            ${XSILIUM_SOURCE_DIR}/Library/Dependencies/Source/freetype/include
                    ${XSILIUM_SOURCE_DIR}/Engine/External/Ogre/supp
                    ${XSILIUM_BULLET_INCLUDE}
                    ${XSILIUM_DEP_INCLUDE}
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
                    ${RAPIDXML_H_PATH}
                    ${XSILIUM_GLRS_INCLUDE}
                    )

subdirs(Library)
subdirs(Engine)
#subdirs(Launcher)
subdirs(Client)





