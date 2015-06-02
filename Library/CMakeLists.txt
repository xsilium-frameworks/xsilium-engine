# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

include(NoWarn)
subdirs(Dependencies)
subdirs(Enet)
subdirs(Ogre)
subdirs(OgrePaged)
subdirs(Cegui)
subdirs(Hydrax)
subdirs(SkyX)
subdirs(openal-soft)
#subdirs(OgreOggSound)
subdirs(Bullet)

#Update
#subdirs(Curl)
#subdirs(Librsync)
#subdirs(MD5)
subdirs(Binreloc)
