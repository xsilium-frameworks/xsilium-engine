# Copyright 2014 Google Inc. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
cmake_minimum_required(VERSION 2.8.7)

project(libvorbis)

set(libvorbis_dir ${dependencies_libvorbis_distr_dir})

if(WIN32)
  add_definitions(-D_USE_MATH_DEFINES)
endif()

# Include libogg header files.
include_directories(${OGG_INCLUDE_DIRS})

# Include libvorbis header files.
include_directories(include)
include_directories(lib)

set(libvorbis_SRCS
    lib/analysis.c
    lib/barkmel.c
    lib/bitrate.c
    lib/block.c
    lib/codebook.c
    lib/envelope.c
    lib/floor0.c
    lib/floor1.c
    lib/info.c
    lib/lookup.c
    lib/lpc.c
    lib/lsp.c
    lib/mapping0.c
    lib/mdct.c
    lib/psy.c
    lib/registry.c
    lib/res0.c
    lib/sharedbook.c
    lib/smallft.c
    lib/synthesis.c
    lib/vorbisenc.c
    lib/vorbisfile.c
    lib/window.c)
    # lib/tone.c

add_library(libvorbis ${libvorbis_SRCS})
target_link_libraries(libvorbis ${OGG_LIBRARIES})

