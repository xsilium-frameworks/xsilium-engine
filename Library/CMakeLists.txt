# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

include(NoWarn)
subdirs(Dependencies)
#subdirs(Bullet)
subdirs(Enet)
subdirs(Ogre)
subdirs(OgrePaged)
subdirs(Cegui)
subdirs(Hydrax)
subdirs(SkyX)

#Update
subdirs(Curl)

#subdirs(Librsync)

# Incompatible win32 (strings.h -> Unix system)
#subdirs(MD5)
subdirs(Binreloc)