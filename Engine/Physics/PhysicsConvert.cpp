/*
 * \file PhysicsConvert.cpp
 *
 *  Created on: \date 9 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "PhysicsConvert.h"

namespace Engine {

PhysicsConvert::PhysicsConvert() {
	// TODO Auto-generated constructor stub

}

PhysicsConvert::~PhysicsConvert() {
	// TODO Auto-generated destructor stub
}

btQuaternion PhysicsConvert::toBullet(const Ogre::Quaternion &q)
{
	return btQuaternion(q.x, q.y, q.z, q.w);
}
btVector3 PhysicsConvert::toBullet(const Ogre::Vector3 &v)
{
	return btVector3(v.x, v.y, v.z);
}

Ogre::Quaternion PhysicsConvert::toOgre(const btQuaternion &q)
{
	return Ogre::Quaternion(q.w(), q.x(), q.y(), q.z());
}
Ogre::Vector3 PhysicsConvert::toOgre(const btVector3 &v)
{
	return Ogre::Vector3(v.x(), v.y(), v.z());
}

} /* namespace Engine */
