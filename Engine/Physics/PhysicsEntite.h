/*
 * \file PhysicsEntite.h
 *
 *  Created on: \date 16 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_PHYSICS_PHYSICSENTITE_H_
#define ENGINE_PHYSICS_PHYSICSENTITE_H_

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/CollisionShapes/btMultiSphereShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/BroadphaseCollision/btOverlappingPairCache.h>
#include <BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <LinearMath/btDefaultMotionState.h>
#include <BulletDynamics/Character/btCharacterControllerInterface.h>
#include "Physics/PhysicsManager.h"

namespace Engine {

/*
 *
 */
class PhysicsEntite : public btCharacterControllerInterface {
public:
	PhysicsEntite();
	virtual ~PhysicsEntite();

	void updateAction(btCollisionWorld * collisionWorld, btScalar dt);

	void debugDraw(btIDebugDraw * debugDrawer);

	void setWalkDirection(const btVector3 & walkDirection);
	void setWalkDirection(const btScalar x, const btScalar y, const btScalar z);

	void setVelocityForTimeInterval(const btVector3 & velocity, btScalar timeInterval);

	void reset(btCollisionWorld* collisionWorld);
	void warp(const btVector3 & origin);
	void preStep(btCollisionWorld * collisionWorld);
	void playerStep(btCollisionWorld * collisionWorld, btScalar dt);
	bool canJump() const;
	void jump();
	bool onGround() const;
    void setUpInterpolate (bool value);

    bool recoverFromPenetration(btCollisionWorld * collisionWorld);
    void setRBForceImpulseBasedOnCollision();

    void stepUp(btCollisionWorld * collisionWorld);

    btPairCachingGhostObject * getGhostObject();

    void stepForwardAndStrafe(btCollisionWorld * collisionWorld, const btVector3 & walkMove);

    void updateTargetPositionBasedOnCollision(const btVector3 & hitNormal, btScalar tangentMag = 0, btScalar normalMag = 1);

    void stepDown(btCollisionWorld * collisionWorld, btScalar dt);

    void stand();

    bool canStand();

    btVector3 getPosition() const;


private:
	btScalar mHalfHeight;

	btPairCachingGhostObject * mGhostObject;
	btConvexShape * mConvexShape;
	btConvexShape * mStandingConvexShape;
	btConvexShape * mDuckingConvexShape;

	btCollisionWorld * mCollisionWorld;

	btScalar mVerticalVelocity;
	btScalar mVerticalOffset;
	btScalar mFallSpeed;
	btScalar mJumpSpeed;
	btScalar mMaxJumpHeight;
	btScalar mMaxSlopeRadians;
	btScalar mMaxSlopeCosine;
	btScalar mGravity;

	btScalar mTurnAngle;

	btScalar mStepHeight;

	btScalar mAddedMargin;

	btVector3 mWalkDirection;
	btVector3 mNormalizedDirection;

	btVector3 mCurrentPosition;
	btScalar mCurrentStepOffset;
	btVector3 mTargetPosition;

	btManifoldArray mManifoldArray;

	bool mTouchingContact;
	btVector3 mTouchingNormal;

	bool mWasOnGround;
	bool mWasJumping;
	bool mUseGhostObjectSweepTest;
	bool mUseWalkDirection;
	btScalar mVelocityTimeInterval;
	int mUpAxis;

	btVector3 mLinearVelocity;
	btScalar mMass;
	bool mCanStand;


	class ClosestNotMeRayResultCallback : public btCollisionWorld::ClosestRayResultCallback
	{
	private:
		btCollisionObject * mMe;

	public:
		ClosestNotMeRayResultCallback(btCollisionObject * me) :
			btCollisionWorld::ClosestRayResultCallback(btVector3(0, 0, 0), btVector3(0, 0, 0)),
			mMe(me)
		{}

		btScalar addSingleResult(btCollisionWorld::LocalRayResult & rayResult, bool normalInWorldSpace)
		{
			if (rayResult.m_collisionObject == mMe)
				return 1.0;

			return btCollisionWorld::ClosestRayResultCallback::addSingleResult(rayResult, normalInWorldSpace);
		}
	};

	class ClosestNotMeConvexResultCallback : public btCollisionWorld::ClosestConvexResultCallback
	{
	private:
		btCollisionObject * mMe;
		const btVector3 mUp;
		btScalar mMinSlopeDot;

	public:
		ClosestNotMeConvexResultCallback(btCollisionObject * me, const btVector3 & up, btScalar minSlopeDot) :
			btCollisionWorld::ClosestConvexResultCallback(btVector3(0, 0, 0), btVector3(0, 0, 0)),
			mMe(me),
			mUp(up),
			mMinSlopeDot(minSlopeDot)
		{}

		btScalar addSingleResult(btCollisionWorld::LocalConvexResult & convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == mMe)
				return 1.0;

			btVector3 hitNormalWorld;

			if (normalInWorldSpace)
				hitNormalWorld = convexResult.m_hitNormalLocal;
			else
				hitNormalWorld = convexResult.m_hitCollisionObject->getWorldTransform().getBasis() * convexResult.m_hitNormalLocal;

			btScalar dotUp = mUp.dot(hitNormalWorld);

			if (dotUp < mMinSlopeDot)
				return 1.0;

			return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
		}
	};


	static btVector3 * getUpAxisDirections()
	{
		static btVector3 sUpAxisDirection[3] = {
				btVector3(1, 0, 0),
				btVector3(0, 1, 0),
				btVector3(0, 0, 1)
		};

		return sUpAxisDirection;
	}

	static btVector3 getNormalizedVector(const btVector3 & v)
	{
		btVector3 n = v.normalized();

		if (n.length() < SIMD_EPSILON)
			n.setValue(0, 0, 0);

		return n;
	}

	btVector3 computeReflectionDirection(const btVector3 & direction, const btVector3 & normal);
	btVector3 parallelComponent(const btVector3 & direction, const btVector3 & normal);
	btVector3 perpindicularComponent(const btVector3 & direction, const btVector3 & normal);
	void setPlayerMode();
};

} /* namespace Engine */

#endif /* ENGINE_PHYSICS_PHYSICSENTITE_H_ */
