/*
 * \file PhysicsManager.cpp
 *
 *  Created on: \date 7 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "PhysicsManager.h"

namespace Engine {

PhysicsManager::PhysicsManager() {
	mWorld = 0;
	debugDrawer = 0;
}

PhysicsManager::~PhysicsManager() {
	// OgreBullet physic delete - RigidBodies
	std::deque<OgreBulletDynamics::RigidBody *>::iterator itBody = mBodies.begin();
	while (mBodies.end() != itBody)
	{
		delete *itBody;
		++itBody;
	}
	// OgreBullet physic delete - Shapes
	std::deque<OgreBulletCollisions::CollisionShape *>::iterator itShape = mShapes.begin();
	while (mShapes.end() != itShape)
	{
		delete *itShape;
		++itShape;
	}
	mBodies.clear();
	mShapes.clear();
	delete mWorld->getDebugDrawer();
	mWorld->setDebugDrawer(0);
	delete mWorld;
}

void PhysicsManager::initPhysics(Ogre::SceneManager *sceneMgr,Ogre::Vector3 gravityVector,Ogre::AxisAlignedBox bounds)
{
	// Start Bullet
	mWorld = new OgreBulletDynamics::DynamicsWorld(sceneMgr, bounds, gravityVector);

	// add Debug info display tool
	debugDrawer = new OgreBulletCollisions::DebugDrawer();
	debugDrawer->setDrawWireframe(true);	// we want to see the Bullet containers

	mWorld->setDebugDrawer(debugDrawer);
	mWorld->setShowDebugShapes(true);		// enable it if you want to see the Bullet containers
	Ogre::SceneNode *node = sceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
	node->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));

}


void PhysicsManager::update(float dt)
{
	mWorld->stepSimulation(dt);	// update Bullet Physics animation
}

OgreBulletDynamics::DynamicsWorld * PhysicsManager::getWorld()
{
	return mWorld;
}


void PhysicsManager::addShape(OgreBulletCollisions::CollisionShape * shape)
{
	mShapes.push_back(shape);
}
void PhysicsManager::removeShape(OgreBulletCollisions::CollisionShape * shape)
{
	std::deque<OgreBulletCollisions::CollisionShape *>::iterator itShape = mShapes.begin();


	while(itShape != mShapes.end())
	{
		if(*itShape == shape)
			mShapes.erase(itShape);
		++itShape;
	}
}

void PhysicsManager::addBody(OgreBulletDynamics::RigidBody * body)
{
	mBodies.push_back(body);
}
void PhysicsManager::removeBody(OgreBulletDynamics::RigidBody * body)
{
	std::deque<OgreBulletDynamics::RigidBody *>::iterator itBody = mBodies.begin();
	while (mBodies.end() != itBody)
	{
		if(*itBody == body)
			mBodies.erase(itBody);
		++itBody;
	}
}

} /* namespace Engine */
