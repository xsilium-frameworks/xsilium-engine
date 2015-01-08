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
	mColConfig = new btDefaultCollisionConfiguration;
	mDispatcher = new btCollisionDispatcher(mColConfig);
	mBroadphase = new btDbvtBroadphase;
	mSolver = new btSequentialImpulseConstraintSolver;
	mWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mColConfig);

	mWorld->setGravity(btVector3(0, -9.81, 0));
	mRootSceneNode = 0;

	physicsDebugDrawer = 0;

}

PhysicsManager::~PhysicsManager() {
	for (int i = mWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject * obj = mWorld->getCollisionObjectArray()[i];
		btRigidBody * body = btRigidBody::upcast(obj);

		if (body && body->getMotionState())
			delete body->getMotionState();

		mWorld->removeCollisionObject(obj);

		delete obj;
	}

	delete mWorld;
	delete mSolver;
	delete mBroadphase;
	delete mDispatcher;
	delete mColConfig;
	delete physicsDebugDrawer;
}

void PhysicsManager::addDynamicTerrain(float metersBetweenVertices,float w,float h,float* data,float minH,float maxH,const Ogre::Vector3& pos,float scale)
{
    btVector3 localScaling(metersBetweenVertices, 1, metersBetweenVertices);

     btHeightfieldTerrainShape* groundShape = new btHeightfieldTerrainShape(
                 w,
                 h,
				 data,
                 1/*ignore*/,
				 minH,
				 maxH,
                 1,
                 PHY_FLOAT,
                 true);

     groundShape->setUseDiamondSubdivision(true);
     groundShape->setLocalScaling(localScaling);

     mCollisionShapes.push_back(groundShape);

     btRigidBody * mGroundBody = new btRigidBody(0, new btDefaultMotionState(), groundShape);

     mGroundBody->getWorldTransform().setOrigin(
                 btVector3(
                		 pos.x,
						 pos.y + (maxH - minH)/2,
						 pos.z));

     mGroundBody->getWorldTransform().setRotation(
                 btQuaternion(
                     Ogre::Quaternion::IDENTITY.x,
                     Ogre::Quaternion::IDENTITY.y,
                     Ogre::Quaternion::IDENTITY.z,
                     Ogre::Quaternion::IDENTITY.w));

     mWorld->addRigidBody(mGroundBody);
}

btRigidBody * PhysicsManager::addDynamicBox(Ogre::SceneNode * node, float m)
{
	btCollisionShape * colShape = new btBoxShape(btVector3(1, 1, 1));
	mCollisionShapes.push_back(colShape);
	btTransform boxTransform;
	boxTransform.setIdentity();

	btScalar mass(m);
	btVector3 localInertia(0, 0, 0);

	colShape->calculateLocalInertia(mass, localInertia);

	boxTransform.setOrigin(btVector3(node->getPosition().x, node->getPosition().y, node->getPosition().z));

	PhysicsMotionState * motionState = new PhysicsMotionState(boxTransform, node);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);
	btRigidBody * body = new btRigidBody(rbInfo);

	mWorld->addRigidBody(body);

	return body;
}

btRigidBody * PhysicsManager::addRigidBody(btTransform transform, btCollisionShape * shape, btScalar mass, Ogre::SceneNode * node )
{
	mCollisionShapes.push_back(shape);
	btVector3 localInertia(0, 0, 0);

	shape->calculateLocalInertia(mass, localInertia);
	PhysicsMotionState * motionState = new PhysicsMotionState(transform, node);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
	btRigidBody * body = new btRigidBody(rbInfo);

	mWorld->addRigidBody(body);

	return body;
}

void PhysicsManager::addCollisionShape(btCollisionShape * colShape)
{
	mCollisionShapes.push_back(colShape);
}

btDiscreteDynamicsWorld * PhysicsManager::getDynamicsWorld()
{
	return mWorld;
}

btCollisionWorld * PhysicsManager::getCollisionWorld()
{
	return mWorld->getCollisionWorld();
}

btBroadphaseInterface * PhysicsManager::getBroadphase()
{
	return mBroadphase;
}

void PhysicsManager::setRootSceneNode(Ogre::SceneNode * node)
{
	mRootSceneNode = node;
	physicsDebugDrawer = new PhysicsDebugDrawer(node,this->getDynamicsWorld());
	getDynamicsWorld()->setDebugDrawer(physicsDebugDrawer);
}

void PhysicsManager::shootBox(const Ogre::Vector3 & camPosition)
{
	if (mRootSceneNode)
	{
		Ogre::SceneNode * node = mRootSceneNode->createChildSceneNode(camPosition);
		btRigidBody * box = addDynamicBox(node);
		box->applyCentralImpulse(btVector3(50, 0, 0));
	}
}

void PhysicsManager::debugBtVector3(const btVector3 & vec, const char * str)
{
	std::cout << str << " x: " << vec.x() << "; y: " << vec.y() << "; z: " << vec.z() << std::endl;
}

void PhysicsManager::update(float dt)
{
	getDynamicsWorld()->stepSimulation(1 / 100.f, 10);
	if(physicsDebugDrawer)
	{
		physicsDebugDrawer->setDebugMode(true);
		physicsDebugDrawer->step();
	}
}


} /* namespace Engine */
