/*
 * \file GraphicsGravity.cpp
 *
 *  Created on: \date 6 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsGravity.h"

namespace Engine {

GraphicsGravity::GraphicsGravity(Ogre::SceneManager *sceneMgr,Ogre::Vector3 gravityVector,Ogre::AxisAlignedBox bounds) {
	this->mSceneMgr = sceneMgr;
	// Start Bullet
	mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, bounds, gravityVector);

	// add Debug info display tool
	debugDrawer = new OgreBulletCollisions::DebugDrawer();
	debugDrawer->setDrawWireframe(true);	// we want to see the Bullet containers

	mWorld->setDebugDrawer(debugDrawer);
	mWorld->setShowDebugShapes(true);		// enable it if you want to see the Bullet containers
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
	node->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));

	OgreBulletCollisions::CollisionShape *Shape;
	Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,0,0), 0); // (normal vector, distance)
	// a body is needed for the shape
	OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody("BasePlane",mWorld);
	defaultPlaneBody->setStaticShape(Shape, 0.1, 0.8);// (shape, restitution, friction)

}

GraphicsGravity::~GraphicsGravity() {
	delete mWorld->getDebugDrawer();
	mWorld->setDebugDrawer(0);
	delete mWorld;
}

void GraphicsGravity::update(float dt)
{
	mWorld->stepSimulation(dt);	// update Bullet Physics animation
}

OgreBulletDynamics::DynamicsWorld * GraphicsGravity::getWorld()
{
	return mWorld;
}

} /* namespace Engine */
