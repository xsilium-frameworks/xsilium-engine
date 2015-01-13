/*
 * \file PhysicsConvert.h
 *
 *  Created on: \date 9 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_PHYSICS_PHYSICSCONVERT_H_
#define ENGINE_PHYSICS_PHYSICSCONVERT_H_

#include "LinearMath/btQuaternion.h"
#include "LinearMath/btVector3.h"
#include "Ogre.h"

namespace Engine {

/*
 *
 */
class PhysicsConvert {
public:
	PhysicsConvert();
	virtual ~PhysicsConvert();
    
	static btQuaternion toBullet(const Ogre::Quaternion &q);
	static btVector3 toBullet(const Ogre::Vector3 &v);

	static Ogre::Quaternion toOgre(const btQuaternion &q);
	static Ogre::Vector3 toOgre(const btVector3 &v);
};

} /* namespace Engine */

#endif /* ENGINE_PHYSICS_PHYSICSCONVERT_H_ */
