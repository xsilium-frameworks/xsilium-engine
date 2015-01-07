/*
 * \file PhysicsManager.h
 *
 *  Created on: \date 7 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_PHYSICS_PHYSICSMANAGER_H_
#define ENGINE_PHYSICS_PHYSICSMANAGER_H_


#include "OgreBulletDynamicsRigidBody.h"				 // for OgreBullet
#include "Singleton/Singleton.h"

namespace Engine {

/*
 *
 */
class PhysicsManager : public Singleton<PhysicsManager> {

	friend class Singleton<PhysicsManager>;

public:
	PhysicsManager();
	virtual ~PhysicsManager();

	void initPhysics(Ogre::SceneManager *sceneMgr,Ogre::Vector3 gravityVector,Ogre::AxisAlignedBox bounds);

	void update(float dt);

	OgreBulletDynamics::DynamicsWorld * getWorld();

	void addShape(OgreBulletCollisions::CollisionShape * shape);
	void removeShape(OgreBulletCollisions::CollisionShape * shape);

	void addBody(OgreBulletDynamics::RigidBody * body);
	void removeBody(OgreBulletDynamics::RigidBody * body);


private:
	OgreBulletDynamics::DynamicsWorld *mWorld;	// OgreBullet World
	OgreBulletCollisions::DebugDrawer *debugDrawer;


	std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
	std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;
};

} /* namespace Engine */

#endif /* ENGINE_PHYSICS_PHYSICSMANAGER_H_ */
