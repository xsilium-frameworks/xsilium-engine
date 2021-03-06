# Vorbis

[![Travis Build Status](https://travis-ci.org/xiph/vorbis.png?branch=master)](https://travis-ci.org/xiph/vorbis)
[![Jenkins Build Status](https://mf4.xiph.org/jenkins/job/libvorbis/badge/icon)](https://mf4.xiph.org/jenkins/job/libvorbis/)

Vorbis is a general purpose audio and music encoding format
contemporary to MPEG-4's AAC and TwinVQ, the next generation beyond
MPEG audio layer 3. Unlike the MPEG sponsored formats (and other
proprietary formats such as RealAudio G2 and Windows' flavor of the
month), the Vorbis CODEC specification belongs to the public domain.
All the technical details are published and documented, and any
software entity may make full use of the format without license
fee, royalty or patent concerns.

This package contains:

- libvorbis, a BSD-style license software implementation of
  the Vorbis specification by the Xiph.Org Foundation
  (https://www.xiph.org/)

- libvorbisfile, a BSD-style license convenience library
  built on Vorbis designed to simplify common uses

- libvorbisenc, a BSD-style license library that provides a simple,
  programmatic encoding setup interface

- example code making use of libogg, libvorbis, libvorbisfile and
  libvorbisenc

## What's here ##

This source distribution includes libvorbis and an example
encoder/player to demonstrate use of libvorbis as well as
documentation on the Ogg Vorbis audio coding format.

You'll need libogg (distributed separately) to compile this library.
A more comprehensive set of utilities is available in the vorbis-tools
package.

Directory:

- `lib` The source for the libraries, a BSD-license implementation of the public domain Ogg Vorbis audio encoding format.

- `include` Library API headers

- `debian` Rules/spec files for building Debian .deb packages

- `doc` Vorbis documentation

- `examples` Example code illustrating programmatic use of libvorbis, libvorbisfile and libvorbisenc

- `macosx` Project files for MacOS X.

- `win32` Win32 projects files and build automation

- `vq` Internal utilities for training/building new LSP/residue and auxiliary codebooks.

## Contact ##

The Ogg homepage is located at 'https://www.xiph.org/ogg/'.
Vorbis's homepage is located at 'https://www.xiph.org/vorbis/'.
Up to date technical documents, contact information, source code and
pre-built utilities may be found there.

The user website for Ogg Vorbis software and audio is http://vorbis.com/

## Building ##

#### Building from master ####

Development source is under git revision control at
https://git.xiph.org/vorbis.git. You will also need the
newest versions of autoconf, automake, libtool and pkg-config in
order to compile Vorbis from development source. A configure script
is provided for you in the source tarball distributions.

    ./autogen.sh
    ./configure
    make

and as root if desired:

    make install

This will install the Vorbis libraries (static and shared) into
/usr/local/lib, includes into /usr/local/include and API manpages
(once we write some) into /usr/local/man.

Documentation building requires xsltproc and pdfxmltex.

#### Building from tarball distributions ####

    ./configure
    make

and optionally (as root):

    make install

#### Building RPM packages ####

after normal configuring:

    make dist
    rpm -ta libvorbis-<version>.tar.gz

## License ##

THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.
USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS
GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE
IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.

THE OggVorbis SOURCE CODE IS COPYRIGHT (C) 1994-2015
by the Xiph.Org Foundation https://www.xiph.org/
