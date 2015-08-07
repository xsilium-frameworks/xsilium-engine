/*
 * \file PhysicsManager.h
 *
 *  Created on: \date 7 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_PHYSICS_PHYSICSMANAGER_H_
#define ENGINE_PHYSICS_PHYSICSMANAGER_H_



#include "Singleton/Singleton.h"
#include "PhysicsMotionState.h"
#include "PhysicsDebugDrawer.h"

#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"



#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"




namespace Engine {
/*
 *
 */
class PhysicsManager : public Singleton<PhysicsManager> {

	friend class Singleton<PhysicsManager>;

public:
	PhysicsManager();
	virtual ~PhysicsManager();

	void addDynamicTerrain(float metersBetweenVertices,float w,float h,float* data,float minH,float maxH,const Ogre::Vector3& pos,float scale);

	btRigidBody * addDynamicBox(Ogre::SceneNode * node, float m = 1.0f);

	btRigidBody * addRigidBody(btTransform  * transform, btCollisionShape * shape, btScalar * mass, Ogre::SceneNode * node = NULL);

	void addCollisionShape(btCollisionShape * colShape);

	btDiscreteDynamicsWorld * getDynamicsWorld();

	btCollisionWorld * getCollisionWorld();

	btBroadphaseInterface * getBroadphase();

	void setRootSceneNode(Ogre::SceneNode * node);

	void shootBox(const Ogre::Vector3 & camPosition);

	static void debugBtVector3(const btVector3 & vec, const char * str = 0);

	void update(float dt);

private:
	btAlignedObjectArray<btCollisionShape*> mCollisionShapes;
	btBroadphaseInterface * mBroadphase;
	btCollisionDispatcher * mDispatcher;
	btConstraintSolver * mSolver;
	btDefaultCollisionConfiguration * mColConfig;
	btDiscreteDynamicsWorld * mWorld;
	Ogre::SceneNode * mRootSceneNode;

	PhysicsDebugDrawer * physicsDebugDrawer;

};

} /* namespace Engine */

#endif /* ENGINE_PHYSICS_PHYSICSMANAGER_H_ */
