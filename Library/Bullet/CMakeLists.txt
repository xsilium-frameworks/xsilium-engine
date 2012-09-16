cmake_minimum_required(VERSION 2.4)

PROJECT(BULLET_PHYSICS)
SET(BULLET_VERSION 2.75)


add_subdirectory(src/BulletCollision)
add_subdirectory(src/BulletDynamics)
add_subdirectory(src/LinearMath)
add_subdirectory(src/BulletSoftBody)

