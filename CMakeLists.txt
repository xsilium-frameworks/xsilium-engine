# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)
   
project(XSILIUM)
SET(XSILIUM 1.0)

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0012 NEW)
endif(COMMAND cmake_policy)

if (POLICY CMP0017)
    cmake_policy(SET CMP0017 OLD)
endif()

if (POLICY CMP0045)
    cmake_policy(SET CMP0045 OLD)
endif()

# ---------------------------------------------------------
set(CMAKE_MODULE_PATH
    ${XSILIUM_SOURCE_DIR}/CMake
    ${XSILIUM_SOURCE_DIR}/CMake/Utils
    ${XSILIUM_SOURCE_DIR}/CMake/Packages
    ${XSILIUM_SOURCE_DIR}/CMake/Templates
    )
include(MacroLogFeature)
include(ConfigXsilium)


configure_xsilium()

subdirs(Library)
subdirs(Engine)

#subdirs(Client)
#subdirs(SceneLoader)





