################################################################################
# Top-level CMakeLists.txt file for Crazy Eddie's GUI System
################################################################################
cmake_minimum_required(VERSION 2.8)
if (POLICY CMP0017)
    cmake_policy(SET CMP0017 OLD)
endif()

if (POLICY CMP0045)
    cmake_policy(SET CMP0045 OLD)
endif()

include(CEGUIMacros)
include(CMakeDependentOption)

################################################################################
# Start of main Project definitions
################################################################################
project(cegui)

################################################################################
# Set up version information
################################################################################
set( CEGUI_VERSION_MAJOR 0)
set( CEGUI_VERSION_MINOR 8)
set( CEGUI_VERSION_PATCH 4)
set( CEGUI_VERSION ${CEGUI_VERSION_MAJOR}.${CEGUI_VERSION_MINOR}.${CEGUI_VERSION_PATCH} )

#
# This controls the binary versioning - which is different to release versions
# defined above.
#
# The following describes what these components are and how they are intended to
# be managed.
# 
#   - CURRENT: The binary interface version provided by the library.
#   - REVISION: Revision of binary interface specified in CURRENT
#   - AGE: Number of previous binary interfaces this library is compatible with.
#
# Prior to issuing a release, modify the values as follows:
#   - If there were any changes in the source, increase REVISION.
#   - If the interface changed at all, increase CURRENT and set REVISION to 0
#   - If the interface had binary compabilbe additions only (so no ABI breaking
#     changes) increase AGE, else set AGE to 0.
#
set( CEGUI_ABI_CURRENT 5)
set( CEGUI_ABI_REVISION 0)
set( CEGUI_ABI_AGE 3)
MATH( EXPR CEGUI_SOVERSION ${CEGUI_ABI_CURRENT}-${CEGUI_ABI_AGE} )
set( CEGUI_ABI_VERSION ${CEGUI_SOVERSION}.${CEGUI_ABI_AGE}.${CEGUI_ABI_REVISION} )


################################################################################
# Check for libs and other packages we might use.
################################################################################
# be sure to search the provided dependencies on Win32 and Mac OS X platforms
if ((WIN32 OR APPLE) AND NOT CMAKE_PREFIX_PATH)
    set (CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/dependencies" CACHE PATH "Path to dependencies")
    # prefer the dylib deps in the dependencies over some other framework
    set (CMAKE_FIND_FRAMEWORK LAST)
endif()


file (STRINGS "${OGRE_SOURCE_DIR}/OgreMain/include/OgrePrerequisites.h" _CEGUIOGREVERSIONDEFINES REGEX ".*#define OGRE_VERSION_.*[0-9]+")

    foreach (ver MAJOR MINOR PATCH)
        set (CEGUI_FOUND_OGRE_VERSION_${ver} 0)
        if ("${_CEGUIOGREVERSIONDEFINES}" MATCHES ".*#define OGRE_VERSION_${ver} ([0-9]+).*")
            set (CEGUI_FOUND_OGRE_VERSION_${ver} "${CMAKE_MATCH_1}")
        endif()
    endforeach()



################################################################################
# Define the configurable options
################################################################################
cmake_dependent_option( CEGUI_MSVC_STATIC_RUNTIME "Specifies whether to the static runtime (/MT and /MTd) or the DLL runtime (/MD and /MDd).
NOTE: This will also affect which set of dependency libraries are linked with." FALSE "MSVC" FALSE )
cmake_dependent_option( CEGUI_BUILD_SHARED_LIBS_WITH_STATIC_DEPENDENCIES "For WIN32 and APPLE where the dependency pack is used, prefer the static
dependency libs over the shared/dynamic ones.  NOTE: On Windows you also need to
be mindful of which C/C++ runtime setting has been used to compile the various
components - they must all match or you will get crashes, heap corruption and/or
other issues." FALSE "WIN32 OR APPLE" FALSE)
option( CEGUI_BUILD_STATIC_CONFIGURATION "Specifies whether the static configs will be built.  (NB: Shared configs are always built)" FALSE)
option( CEGUI_BUILD_STATIC_FACTORY_MODULE "For static CEGUI builds, specifies whether to include the getWindoFactoryModule method.  When false, the developer must provide a custom implementation of the method" FALSE)
# sanity check on static build option for factory method
if (CEGUI_BUILD_STATIC_FACTORY_MODULE AND NOT CEGUI_BUILD_STATIC_CONFIGURATION)
  message(SEND_ERROR "You may not enable CEGUI_BUILD_STATIC_FACTORY_MODULE without CEGUI_BUILD_STATIC_CONFIGURATION enabled.  CEGUI needs to be built statically if building the static factory method.")
endif()
option( CEGUI_CUSTOM_ALLOCATORS "If checked, CEGUI can use custom allocation. (for experienced developers only!)" FALSE )
cmake_dependent_option( CEGUI_CUSTOM_ALLOCATORS_DEBUG "If checked, CEGUI allocations will pass debug info to allocators. (only used if CEGUI_CUSTOM_ALLOCATORS is checked)" FALSE "CEGUI_CUSTOM_ALLOCATORS" FALSE )
set( CEGUI_CUSTOM_ALLOCATORS_INCLUDE "CEGUI/MemoryStdAllocator.h" CACHE STRING "Which include file contains memory allocators and allocation configuration. (only used if CEGUI_CUSTOM_ALLOCATORS is checked)
We have bundled 2 allocators, mostly for demonstrational purposes.
CEGUI/MemoryStdAllocator.h contains malloc allocator, use it as a starting point for your own allocators
CEGUI/MemoryOgreAllocator.h delegates allocation to Ogre, which may be useful to Ogre users (you will have to manually change linking options of CEGUIBase!)" )

set( CEGUI_STRING_CLASS 1 CACHE INT "Which string class should CEGUI use
1 - utf8 and utf32 aware inbuilt string,
2 - std::string without custom allocation,
3 - std::basic_string allocated according to allocator config" )

# sanity check std::basic_string and allocator and allocators actually being used
if (${CEGUI_STRING_CLASS} MATCHES 3 AND NOT CEGUI_CUSTOM_ALLOCATORS)
    message(SEND_ERROR "You requested std::basic_string allocated according to allocator as CEGUI::String even though CEGUI is not being built with custom allocators enabled!")
endif()

option( CEGUI_HAS_FREETYPE "Specifies whether to include Freetype font support" ${FREETYPE_FOUND} )
option( CEGUI_HAS_PCRE_REGEX "Specifies whether to include PCRE regexp matching for editbox string validation" ${PCRE_FOUND} )
option( CEGUI_HAS_MINIZIP_RESOURCE_PROVIDER "Specifies whether to build the minizip based resource provider" ${MINIZIP_FOUND} )
option( CEGUI_HAS_DEFAULT_LOGGER "Specifies whether to build the DefaultLogger implementation" TRUE)

option( CEGUI_BUILD_XMLPARSER_EXPAT "Specifies whether to build the Expat based XMLParser module" ${EXPAT_FOUND} )
option( CEGUI_BUILD_XMLPARSER_XERCES "Specifies whether to build the Xerces-C++ based XMLParser module" ${XERCESC_FOUND} )
option( CEGUI_BUILD_XMLPARSER_LIBXML2 "Specifies whether to build the libxml2 based XMLParser module" ${LIBXML2_FOUND} )
option( CEGUI_BUILD_XMLPARSER_RAPIDXML "Specifies whether to build the RapidXML based XMLParser module" ${RAPIDXML_FOUND} )
option( CEGUI_BUILD_XMLPARSER_TINYXML "Specifies whether to build the TinyXML based XMLParser module" ${TINYXML_FOUND} )

option( CEGUI_BUILD_IMAGECODEC_SILLY "Specifies whether to build the SILLY based ImageCodec module" ${SILLY_FOUND} )
option( CEGUI_BUILD_IMAGECODEC_DEVIL "Specifies whether to build the DevIL based ImageCodec module" ${IL_FOUND} )
option( CEGUI_BUILD_IMAGECODEC_FREEIMAGE "Specifies whether to build the FreeImage based ImageCodec module" ${FREEIMAGE_FOUND} )
option( CEGUI_BUILD_IMAGECODEC_CORONA "Specifies whether to build the Corona based ImageCodec module" ${CORONA_FOUND} )
option( CEGUI_BUILD_IMAGECODEC_STB "Specifies whether to build the STB based ImageCodec module" TRUE )
option( CEGUI_BUILD_IMAGECODEC_TGA "Specifies whether to build the based TGA only ImageCodec module" TRUE )
option( CEGUI_BUILD_IMAGECODEC_PVR "Specifies whether to build the PVR only ImageCodec module" ${PVRTOOLS_FOUND} )

cegui_dependent_option( CEGUI_BUILD_RENDERER_OPENGL "Specifies whether to build the OpenGL renderer module" "OPENGL_FOUND;GLM_FOUND;GLEW_FOUND" )
cegui_dependent_option( CEGUI_BUILD_RENDERER_OPENGL3 "Specifies whether to build the OpenGL 3+ (core profile) renderer module" "OPENGL_FOUND;GLM_FOUND;GLEW_FOUND")
option( CEGUI_BUILD_RENDERER_OGRE "Specifies whether to build the Ogre renderer module" ${OGRE_FOUND} )
option( CEGUI_BUILD_RENDERER_IRRLICHT "Specifies whether to build the Irrlicht renderer module" ${IRRLICHT_FOUND} )
option( CEGUI_BUILD_RENDERER_DIRECTFB "Specifies whether to build the DirectFB renderer module (not supported!)" FALSE )
cegui_dependent_option( CEGUI_BUILD_RENDERER_DIRECT3D9 "Specifies whether to build the Direct3D 9 renderer module" "DIRECTXSDK_FOUND;NOT DIRECTXSDK_MAX_D3D LESS 9" )
cegui_dependent_option( CEGUI_BUILD_RENDERER_DIRECT3D10 "Specifies whether to build the Direct3D 10 renderer module" "DIRECTXSDK_FOUND;NOT DIRECTXSDK_MAX_D3D LESS 10" )
cegui_dependent_option( CEGUI_BUILD_RENDERER_DIRECT3D11 "Specifies whether to build the Direct3D 11 renderer module" "DIRECTXSDK_FOUND;D3DX11EFFECTS_FOUND;NOT DIRECTXSDK_MAX_D3D LESS 11" )
option( CEGUI_BUILD_RENDERER_NULL "Specifies whether to build the null renderer module" FALSE )
option( CEGUI_BUILD_RENDERER_OPENGLES "Specifies whether to build the OpenGLES renderer module" FALSE )

cegui_dependent_option( CEGUI_BUILD_LUA_MODULE "Specifies whether to build the Lua based script module" "LUA51_FOUND;TOLUAPP_FOUND" )
cegui_dependent_option( CEGUI_BUILD_LUA_GENERATOR "Specifies whether to build the custom tolua binding generator 'toluappcegui'" "LUA51_FOUND;TOLUAPP_FOUND" )

cegui_dependent_option( CEGUI_BUILD_PYTHON_MODULES "Specifies whether to build the Python extension module(s)" "PYTHONINTERP_FOUND;PYTHONLIBS_FOUND;Boost_PYTHON_FOUND" )

option( CEGUI_OPTION_SAFE_LUA_MODULE "Specifies whether to enable extra validation in the Lua script module in non-debug builds" FALSE )

cegui_dependent_option( CEGUI_USE_FRIBIDI "Specifies whether bi-directional text will be supported via the fribidi library." "FRIBIDI_FOUND" )
cegui_dependent_option( CEGUI_USE_MINIBIDI "Specifies whether bi-directional text will be supported via the embedded minibidi." FALSE )

# sanity check on bidi options
if (CEGUI_USE_MINIBIDI AND CEGUI_USE_FRIBIDI)
    message(SEND_ERROR "You may not enable both CEGUI_USE_FRIBIDI and CEGUI_USE_MINIBIDI. Please choose only one of these options.")
endif()

if (WIN32 OR APPLE)
    set (CEGUI_BUILD_SUFFIX "_d" CACHE STRING "String holding a suffix appended to the name of output binaries (under CMake build, only used for debug).")
else()
    set (CEGUI_BUILD_SUFFIX "" CACHE STRING "String holding a suffix appended to the name of output binaries (under CMake build, only used for debug).")
endif()

if (CEGUI_BUILD_SUFFIX)
    set (CEGUI_HAS_BUILD_SUFFIX TRUE)
    set (CMAKE_DEBUG_POSTFIX ${CEGUI_BUILD_SUFFIX})
endif()

# Apple OS X specific options
if (APPLE)
    set( CEGUI_APPLE_DYLIB_INSTALL_PATH "@executable_path/../Frameworks" CACHE STRING "Specifies the install rpath for dylibs and frameworks." )
    set( CEGUI_APPLE_SYMLINK_DEPENDENCIES_TO_SAMPLE_APPS TRUE CACHE BOOL "Specifies how to reference the dylibs, frameworks and datafiles in the sample app bundles:
    TRUE: specifies that the files will be symlinked (saves space, but apps are not truly stand-alone)
    FALSE: specifies that actual copies of the files will be used" )
    option( CEGUI_APPLE_DYLIB_SET_VERSION_INFO "Specifies whether to set VERSION and SOVERSION for libraries." FALSE )
endif()

# regression and performance tests
cmake_dependent_option( CEGUI_BUILD_TESTS "Specifies whether to build the regression and performance tests." FALSE "Boost_UNIT_TEST_FRAMEWORK_FOUND" FALSE )

option( CEGUI_INSTALL_WITH_RPATH "Specifies whether to install with RPATH set to the install location (TRUE) or with no RPATH set (FALSE)." FALSE )

################################################################################
# Define vars holding the names for all the libs we can build for CEGUI.
################################################################################
# Core lib name
cegui_set_library_name( CEGUI_BASE_LIBNAME CEGUIBase )

# Renderer module names.
cegui_set_library_name( CEGUI_OPENGL_RENDERER_LIBNAME CEGUIOpenGLRenderer )
cegui_set_library_name( CEGUI_OPENGL3_RENDERER_LIBNAME CEGUIOpenGL3Renderer )
cegui_set_library_name( CEGUI_OGRE_RENDERER_LIBNAME CEGUIOgreRenderer)
cegui_set_library_name( CEGUI_IRRLICHT_RENDERER_LIBNAME CEGUIIrrlichtRenderer )
cegui_set_library_name( CEGUI_DIRECT3D9_RENDERER_LIBNAME CEGUIDirect3D9Renderer )
cegui_set_library_name( CEGUI_DIRECT3D10_RENDERER_LIBNAME CEGUIDirect3D10Renderer )
cegui_set_library_name( CEGUI_DIRECT3D11_RENDERER_LIBNAME CEGUIDirect3D11Renderer )
cegui_set_library_name( CEGUI_NULL_RENDERER_LIBNAME CEGUINullRenderer )
cegui_set_library_name( CEGUI_OPENGLES_RENDERER_LIBNAME CEGUIOpenGLESRenderer )
cegui_set_library_name( CEGUI_DIRECTFB_RENDERER_LIBNAME CEGUIDirectFBRenderer )

# XML parser module names
cegui_set_module_name( CEGUI_EXPAT_PARSER_LIBNAME CEGUIExpatParser )
cegui_set_module_name( CEGUI_TINYXML_PARSER_LIBNAME CEGUITinyXMLParser )
cegui_set_module_name( CEGUI_XERCES_PARSER_LIBNAME CEGUIXercesParser )
cegui_set_module_name( CEGUI_RAPIDXML_PARSER_LIBNAME CEGUIRapidXMLParser )
cegui_set_module_name( CEGUI_LIBXML2_PARSER_LIBNAME CEGUILibXMLParser )

# ImageCodec module names
cegui_set_module_name( CEGUI_SILLY_IMAGECODEC_LIBNAME CEGUISILLYImageCodec )
cegui_set_module_name( CEGUI_DEVIL_IMAGECODEC_LIBNAME CEGUIDevILImageCodec )
cegui_set_module_name( CEGUI_FREEIMAGE_IMAGECODEC_LIBNAME CEGUIFreeImageImageCodec )
cegui_set_module_name( CEGUI_CORONA_IMAGECODEC_LIBNAME CEGUICoronaImageCodec )
cegui_set_module_name( CEGUI_TGA_IMAGECODEC_LIBNAME CEGUITGAImageCodec )
cegui_set_module_name( CEGUI_STB_IMAGECODEC_LIBNAME CEGUISTBImageCodec )
cegui_set_module_name( CEGUI_PVR_IMAGECODEC_LIBNAME CEGUIPVRImageCodec )

# WindowRenderer set module names
cegui_set_module_name( CEGUI_CORE_WR_LIBNAME CEGUICoreWindowRendererSet )

# Scripting module names and related items.
cegui_set_executable_name( CEGUI_TOLUAPP_GENERATOR_EXENAME toluappcegui )
cegui_set_library_name( CEGUI_LUA_SCRIPTMODULE_LIBNAME CEGUILuaScriptModule )

set( CEGUI_PYCEGUI_CORE_LIBNAME PyCEGUI )
set( CEGUI_PYCEGUI_OPENGL_RENDERER_LIBNAME PyCEGUIOpenGLRenderer )
set( CEGUI_PYCEGUI_OGRE_RENDERER_LIBNAME PyCEGUIOgreRenderer )
set( CEGUI_PYCEGUI_NULL_RENDERER_LIBNAME PyCEGUINullRenderer )


# Additional lib names
cegui_set_library_name( CEGUI_COMMON_DIALOGS_LIBNAME CEGUICommonDialogs )

################################################################################
# Select one of the XML parser modules to be the default, warning if none are
# available.
################################################################################
if (CEGUI_BUILD_XMLPARSER_EXPAT)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "ExpatParser" CACHE STRING "Specifies the XMLParser module to use as the default" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_EXPAT_PARSER_LIBNAME} CACHE STRING "Specifies xml parser library to link to samples in static builds." )
elseif (CEGUI_BUILD_XMLPARSER_XERCES)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "XercesParser" CACHE STRING "Specifies the XMLParser module to use as the default" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_XERCES_PARSER_LIBNAME} CACHE STRING "Specifies xml parser library to link to samples in static builds." )
elseif (CEGUI_BUILD_XMLPARSER_LIBXML2)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "LibXMLParser" CACHE STRING "Specifies the XMLParser module to use as the default" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_LIBXML2_PARSER_LIBNAME} CACHE STRING "Specifies xml parser library to link to samples in static builds." )
elseif (CEGUI_BUILD_XMLPARSER_RAPIDXML)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "RapidXMLParser" CACHE STRING "Specifies the XMLParser module to use as the default" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_RAPIDXML_PARSER_LIBNAME} CACHE STRING "Specifies xml parser library to link to samples in static builds." )
elseif (CEGUI_BUILD_XMLPARSER_TINYXML)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "TinyXMLParser" CACHE STRING "Specifies the XMLParser module to use as the default" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_TINYXML_PARSER_LIBNAME} CACHE STRING "Specifies xml parser library to link to samples in static builds." )
else()
    message(WARNING "None of the XML parser modules are going to be built.
You should ensure that CEGUI_OPTION_DEFAULT_XMLPARSER is set to something
appropriate.")
endif()

cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_XMLPARSER "ExpatParser" CEGUI_BUILD_XMLPARSER_EXPAT)
cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_XMLPARSER "XercesParser" CEGUI_BUILD_XMLPARSER_XERCES)
cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_XMLPARSER "LibXMLParser" CEGUI_BUILD_XMLPARSER_LIBXML2)
cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_XMLPARSER "RapidXMLParser" CEGUI_BUILD_XMLPARSER_RAPIDXML)
cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_XMLPARSER "TinyXMLParser" CEGUI_BUILD_XMLPARSER_TINYXML)

if (CEGUI_BUILD_STATIC_CONFIGURATION)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_EXPAT_PARSER_LIBNAME} CEGUI_BUILD_XMLPARSER_EXPAT)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_XERCES_PARSER_LIBNAME} CEGUI_BUILD_XMLPARSER_XERCES)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_LIBXML2_PARSER_LIBNAME} CEGUI_BUILD_XMLPARSER_LIBXML2)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_RAPIDXML_PARSER_LIBNAME} CEGUI_BUILD_XMLPARSER_RAPIDXML)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_TINYXML_PARSER_LIBNAME} CEGUI_BUILD_XMLPARSER_TINYXML)
endif()

################################################################################
# Select one of the image codec modules to be the default, warning if none are
# available.
################################################################################
if (CEGUI_BUILD_IMAGECODEC_SILLY)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "SILLYImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_SILLY_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_DEVIL)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "DevILImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_DEVIL_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_FREEIMAGE)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "FreeImageImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_FREEIMAGE_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_STB)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "STBImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_STB_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_CORONA)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "CoronaImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_CORONA_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_TGA)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "TGAImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_TGA_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
else()
message(WARNING "None of the image codec modules are going to be built.
You should ensure that CEGUI_OPTION_DEFAULT_IMAGECODEC is set to something
appropriate.")
endif()

cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_IMAGECODEC "SILLYImageCodec" CEGUI_BUILD_IMAGECODEC_SILLY)
cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_IMAGECODEC "DevILImageCodec" CEGUI_BUILD_IMAGECODEC_DEVIL)
cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_IMAGECODEC "FreeImageImageCodec" CEGUI_BUILD_IMAGECODEC_FREEIMAGE)
cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_IMAGECODEC "STBImageCodec" CEGUI_BUILD_IMAGECODEC_STB)
cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_IMAGECODEC "CoronaImageCodec" CEGUI_BUILD_IMAGECODEC_CORONA)
cegui_defaultmodule_sanity_test(CEGUI_OPTION_DEFAULT_IMAGECODEC "TGAImageCodec" CEGUI_BUILD_IMAGECODEC_TGA)

if (CEGUI_BUILD_STATIC_CONFIGURATION)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_SILLY_IMAGECODEC_LIBNAME} CEGUI_BUILD_IMAGECODEC_SILLY)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_DEVIL_IMAGECODEC_LIBNAME} CEGUI_BUILD_IMAGECODEC_DEVIL)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_FREEIMAGE_IMAGECODEC_LIBNAME} CEGUI_BUILD_IMAGECODEC_FREEIMAGE)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_STB_IMAGECODEC_LIBNAME} CEGUI_BUILD_IMAGECODEC_STB)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_CORONA_IMAGECODEC_LIBNAME} CEGUI_BUILD_IMAGECODEC_CORONA)
    cegui_defaultmodule_sanity_test(CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_TGA_IMAGECODEC_LIBNAME} CEGUI_BUILD_IMAGECODEC_TGA)
endif()

################################################################################
# Add main header locations (for everything we build)
################################################################################
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/cegui/include
    ${CMAKE_CURRENT_SOURCE_DIR}/cegui/include
)


################################################################################
# Adjust configuration based on option settings
################################################################################
# Windows specific config
if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DNOMINMAX)

    if (MSVC)
        cegui_set_msvc_runtime_flags()
    endif()
endif()

# set build output locations
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

if (WIN32)
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/RelWithDebInfo")
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug")
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Release")
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/MinSizeRel")
	
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release")
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MinSizeRel")
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RelWithDebInfo")
	
else()
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

# set up install sub-directories
if (CMAKE_SIZEOF_VOID_P EQUAL 8 AND EXISTS "${CMAKE_INSTALL_PREFIX}/lib64")
    set( CEGUI_LIB_INSTALL_DIR lib64 )
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4 AND EXISTS "${CMAKE_INSTALL_PREFIX}/lib32")
    set( CEGUI_LIB_INSTALL_DIR lib32 )
else()
    set( CEGUI_LIB_INSTALL_DIR lib )
endif()

set( CEGUI_VER_INSTALL_SUBDIR "/${CMAKE_PROJECT_NAME}-${CEGUI_VERSION_MAJOR}" )
set( CEGUI_DATA_INSTALL_DIR "share${CEGUI_VER_INSTALL_SUBDIR}" )
set( CEGUI_DOC_INSTALL_DIR "share/doc${CEGUI_VER_INSTALL_SUBDIR}" )

set( CEGUI_PKGCONFIG_INSTALL_DIR "${CEGUI_LIB_INSTALL_DIR}/pkgconfig" )
set( CEGUI_MODULE_INSTALL_DIR "${CEGUI_LIB_INSTALL_DIR}/${CMAKE_PROJECT_NAME}-${CEGUI_VERSION_MAJOR}.${CEGUI_VERSION_MINOR}" )
set( CEGUI_SAMPLE_INSTALL_DIR "${CEGUI_MODULE_INSTALL_DIR}" ) # TODO: put into /samples subdir!
set( CEGUI_INCLUDE_INSTALL_DIR "include${CEGUI_VER_INSTALL_SUBDIR}" )

################################################################################
# Deal with files we generate from template files
################################################################################
configure_file( cegui/include/CEGUI/Version.h.in cegui/include/CEGUI/Version.h )
configure_file( cegui/include/CEGUI/Config.h.in cegui/include/CEGUI/Config.h )
configure_file( cegui/include/CEGUI/ModuleConfig.h.in cegui/include/CEGUI/ModuleConfig.h )

if (UNIX AND NOT APPLE)
    configure_file( cegui/CEGUI.pc.in cegui/CEGUI-${CEGUI_VERSION_MAJOR}.pc @ONLY )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cegui/CEGUI-${CEGUI_VERSION_MAJOR}.pc DESTINATION ${CEGUI_PKGCONFIG_INSTALL_DIR})

    if (CEGUI_BUILD_RENDERER_NULL)
        configure_file( cegui/CEGUI-NULL.pc.in cegui/CEGUI-${CEGUI_VERSION_MAJOR}-NULL.pc @ONLY )
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cegui/CEGUI-${CEGUI_VERSION_MAJOR}-NULL.pc DESTINATION ${CEGUI_PKGCONFIG_INSTALL_DIR})
    endif()
    if (CEGUI_BUILD_RENDERER_IRRLICHT)
        configure_file( cegui/CEGUI-IRRLICHT.pc.in cegui/CEGUI-${CEGUI_VERSION_MAJOR}-IRRLICHT.pc @ONLY )
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cegui/CEGUI-${CEGUI_VERSION_MAJOR}-IRRLICHT.pc DESTINATION ${CEGUI_PKGCONFIG_INSTALL_DIR})
    endif()
    if (CEGUI_BUILD_RENDERER_OGRE)
        configure_file( cegui/CEGUI-OGRE.pc.in cegui/CEGUI-${CEGUI_VERSION_MAJOR}-OGRE.pc @ONLY )
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cegui/CEGUI-${CEGUI_VERSION_MAJOR}-OGRE.pc DESTINATION ${CEGUI_PKGCONFIG_INSTALL_DIR})
    endif()
    if (CEGUI_BUILD_RENDERER_OPENGL)
        configure_file( cegui/CEGUI-OPENGL.pc.in cegui/CEGUI-${CEGUI_VERSION_MAJOR}-OPENGL.pc @ONLY )
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cegui/CEGUI-${CEGUI_VERSION_MAJOR}-OPENGL.pc DESTINATION ${CEGUI_PKGCONFIG_INSTALL_DIR})
    endif()
    if (CEGUI_BUILD_RENDERER_OPENGL3)
        configure_file( cegui/CEGUI-OPENGL3.pc.in cegui/CEGUI-${CEGUI_VERSION_MAJOR}-OPENGL3.pc @ONLY )
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cegui/CEGUI-${CEGUI_VERSION_MAJOR}-OPENGL3.pc DESTINATION ${CEGUI_PKGCONFIG_INSTALL_DIR})
    endif()
    if (CEGUI_BUILD_LUA_MODULE)
        configure_file( cegui/CEGUI-LUA.pc.in cegui/CEGUI-${CEGUI_VERSION_MAJOR}-LUA.pc @ONLY )
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cegui/CEGUI-${CEGUI_VERSION_MAJOR}-LUA.pc DESTINATION ${CEGUI_PKGCONFIG_INSTALL_DIR})
    endif()
endif()

################################################################################
# descend into subdirs
################################################################################
add_subdirectory(cegui/src)
add_subdirectory(cegui/src/RendererModules)
add_subdirectory(cegui/src/XMLParserModules)
add_subdirectory(cegui/src/ImageCodecModules)
add_subdirectory(cegui/src/WindowRendererSets)
add_subdirectory(cegui/src/ScriptModules)

add_subdirectory(cegui/src/CommonDialogs)

