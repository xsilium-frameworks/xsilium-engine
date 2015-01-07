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

subdirs(Bullet)
subdirs(OgreBullet)

#Update
#subdirs(Curl)
#subdirs(Librsync)
#subdirs(MD5)
subdirs(Binreloc)
