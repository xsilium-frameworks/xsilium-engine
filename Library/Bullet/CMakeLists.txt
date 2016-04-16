
PROJECT(BULLET_PHYSICS)

if(MSVC)
SET(BUILD_SHARED_LIBS FALSE)
else(UNIX)
SET(BUILD_SHARED_LIBS TRUE)
endif(MSVC)

set(CMAKE_MACOSX_RPATH 0)

SUBDIRS(  Extras )

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

#SUBDIRS(  Bullet3OpenCL Bullet3Serialize/Bullet2FileLoader Bullet3Dynamics Bullet3Collision Bullet3Geometry Bullet3Common )

SUBDIRS(  BulletSoftBody BulletCollision BulletDynamics LinearMath )

set(BULLET_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/Extras" CACHE PATH "" FORCE)

set(BULLET_LIBRARIES "LinearMath" "BulletCollision" "BulletDynamics" "BulletSoftBody" "ConvexDecomposition" CACHE STRING "" FORCE)

