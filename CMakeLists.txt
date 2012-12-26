# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

#SET(CMAKE_SUPPRESS_REGENERATION  1)
#SET(CMAKE_USE_RELATIVE_PATHS 1)
#SET(INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES 1)

project(XSILIUM)
SET(XSILIUM 1.0)
set(OGRE_STATIC TRUE)

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if (MSVC)
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
	add_definitions( -D_CRT_SECURE_NO_DEPRECATE )
	add_definitions( -DNOMINMAX)
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
include(ConfigIPhone)
include(OgreAddTargets)

configure_xsilium(${XSILIUM_SOURCE_DIR} ${XSILIUM_SOURCE_DIR}/Library/Ogre )


set(XSILIUM_BULLET_LIBS BulletDynamics BulletCollision  LinearMath)	
set(XSILIUM_BULLET_INCLUDE ${XSILIUM_SOURCE_DIR}/bullet/src)
if (XSILIUM_COMPILE_SOFTBODY)
	list(APPEND XSILIUM_BULLET_LIBS BulletSoftBody)
endif()


#if (APPLE)
#    if (${XCODE_VERSION} STRGREATER "4.0.0")
#        set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "4.2")
#    endif()
#endif()


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
		IF(${flag_var} MATCHES "/MD")
			STRING(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
		ENDIF(${flag_var} MATCHES "/MD")
		IF(${flag_var} MATCHES "/MDd")
			STRING(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
		ENDIF(${flag_var} MATCHES "/MDd")
	ENDFOREACH(flag_var)

ENDIF(MSVC)


# ---------------------------------------------------------
# Common base paths
set(XSILIUM_INCLUDE ${XSILIUM_OGRE_INCLUDE}
                    ${XSILIUM_SOURCE_DIR}/Engine
                    ${XSILIUM_DEP_INCLUDE}
		    ${XSILIUM_SOURCE_DIR}/Library/Cegui/cegui/include
		    ${XSILIUM_BINARY_DIR}/Library/Cegui/cegui/include
		    ${XSILIUM_SOURCE_DIR}/Library/OgrePaged/include
		    ${XSILIUM_BINARY_DIR}/Library/OgrePaged/include
                    )

set(XSILIUM_LIB XsiliumEngine ${XSILIUM_OGRE_LIBS} CEGUIBase PagedGeometry CEGUIOgreRenderer OgreTerrain )


subdirs(Library)
subdirs(Engine)
subdirs(Client)






