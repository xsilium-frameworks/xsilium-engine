/*
 * \file GraphicsGravity.h
 *
 *  Created on: \date 6 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_GRAPHICS_GRAPHICSGRAVITY_H_
#define ENGINE_GRAPHICS_GRAPHICSGRAVITY_H_

#include "OgreBulletDynamicsRigidBody.h"				 // for OgreBullet
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h" // for static planes
#include "Shapes/OgreBulletCollisionsBoxShape.h"		 // for Boxes

namespace Engine {

/*
 *
 */
class GraphicsGravity {
public:
	GraphicsGravity(Ogre::SceneManager *sceneMgr,Ogre::Vector3 gravityVector,Ogre::AxisAlignedBox bounds);
	virtual ~GraphicsGravity();

	void update(float dt);

	OgreBulletDynamics::DynamicsWorld * getWorld();

private:
	Ogre::SceneManager* mSceneMgr;
	OgreBulletDynamics::DynamicsWorld *mWorld;	// OgreBullet World
	OgreBulletCollisions::DebugDrawer *debugDrawer;
};

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_GRAPHICSGRAVITY_H_ */
