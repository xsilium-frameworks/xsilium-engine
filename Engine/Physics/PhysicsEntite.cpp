/*
 * \file PhysicsEntite.cpp
 *
 *  Created on: \date 16 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "PhysicsEntite.h"

namespace Engine {

PhysicsEntite::PhysicsEntite() {

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(4, 4, 4));

	btPairCachingGhostObject * characterGhostObject =
			new btPairCachingGhostObject();
	characterGhostObject->setWorldTransform(startTransform);

	btScalar characterHeight = 4.f;
	btScalar characterWidth = 3.f;

	btConvexShape * capsule = new btCapsuleShape(characterWidth,
			characterHeight);

	PhysicsManager::getInstance()->addCollisionShape(capsule);

	characterGhostObject->setCollisionShape(capsule);
	characterGhostObject->setCollisionFlags(
			btCollisionObject::CF_CHARACTER_OBJECT);

	// duck setup
	btConvexShape * mDuckingConvexShape = new btCapsuleShape(characterWidth,
			characterHeight / 3);
	PhysicsManager::getInstance()->addCollisionShape(mDuckingConvexShape);

	PhysicsManager::getInstance()->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(
			new btGhostPairCallback());

	PhysicsManager::getInstance()->getDynamicsWorld()->addCollisionObject(
			characterGhostObject, btBroadphaseProxy::CharacterFilter,
			btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
	PhysicsManager::getInstance()->getDynamicsWorld()->addAction(this);
    
    mUpAxis = 1;
    mAddedMargin = 0.02;
    mWalkDirection.setValue(0, 0, 0);
    mUseGhostObjectSweepTest = true;
    mGhostObject = characterGhostObject;
    mStepHeight = 0.35f;
    mTurnAngle = 0;
    mConvexShape = mStandingConvexShape = capsule;
    mUseWalkDirection = true;
    mVelocityTimeInterval = 0;
    mVerticalOffset = 0;
    mVerticalVelocity = 0;
    mGravity = 9.8 * 3;
    mFallSpeed = 55;
    mJumpSpeed = 10;
    mWasOnGround = false;
    mWasJumping = false;
    mCanStand = true;
    mCurrentPosition.setValue(4, 4, 4);
    mMass = 20;

}

PhysicsEntite::~PhysicsEntite() {
	// TODO Auto-generated destructor stub
}

void PhysicsEntite::updateAction(btCollisionWorld * collisionWorld,
		btScalar dt) {
	preStep(collisionWorld);
	playerStep(collisionWorld, dt);
}

void PhysicsEntite::debugDraw(btIDebugDraw * debugDrawer) {

}

void PhysicsEntite::setWalkDirection(const btVector3 & walkDirection) {
	mUseWalkDirection = true;
	mWalkDirection = walkDirection;
	mNormalizedDirection = getNormalizedVector(mWalkDirection);
}
void PhysicsEntite::setWalkDirection(const btScalar x, const btScalar y,
		const btScalar z) {
	mUseWalkDirection = true;
	mWalkDirection.setValue(x, y, z);
	mNormalizedDirection = getNormalizedVector(mWalkDirection);

}

void PhysicsEntite::setVelocityForTimeInterval(const btVector3 & velocity,
		btScalar timeInterval) {
	mUseWalkDirection = false;
	mWalkDirection = velocity;
	mNormalizedDirection = getNormalizedVector(mWalkDirection);
	mVelocityTimeInterval = timeInterval;
}

void PhysicsEntite::reset(btCollisionWorld* collisionWorld) {

}

void PhysicsEntite::warp(const btVector3 & origin) {
	btTransform xform;
	xform.setIdentity();
	xform.setOrigin(origin);
	mGhostObject->setWorldTransform(xform);
}

void PhysicsEntite::preStep(btCollisionWorld * collisionWorld) {
	int numPenetrationLoops = 0;
	mTouchingContact = false;

	while (recoverFromPenetration(collisionWorld)) {
		numPenetrationLoops++;
		mTouchingContact = true;

		if (numPenetrationLoops > 4)
			break;
	}

	mCurrentPosition = mGhostObject->getWorldTransform().getOrigin();
	mTargetPosition = mCurrentPosition;

}
void PhysicsEntite::playerStep(btCollisionWorld * collisionWorld, btScalar dt) {
	if (!mUseWalkDirection && mVelocityTimeInterval <= 0)
		return;

	mWasOnGround = onGround();

	setRBForceImpulseBasedOnCollision();

	mVerticalVelocity -= mGravity * dt;

	if (mVerticalVelocity > 0 && mVerticalVelocity > mJumpSpeed)
		mVerticalVelocity = mJumpSpeed;

	if (mVerticalVelocity < 0 && btFabs(mVerticalVelocity) > btFabs(mFallSpeed))
		mVerticalVelocity = -btFabs(mFallSpeed);

	mVerticalOffset = mVerticalVelocity * dt;

	btTransform xform;
	xform = mGhostObject->getWorldTransform();

	stepUp(collisionWorld);

	if (mUseWalkDirection)
		stepForwardAndStrafe(collisionWorld, mWalkDirection);
	else {
		// still have some time left for moving!
		btScalar dtMoving =
				(dt < mVelocityTimeInterval) ? dt : mVelocityTimeInterval;
		mVelocityTimeInterval -= dt;

		// how far will we move while we are moving?
		btVector3 move = mWalkDirection * dtMoving;

		// okay, step
		stepForwardAndStrafe(collisionWorld, move);
	}

	stepDown(collisionWorld, dt);

	xform.setOrigin(mCurrentPosition);
	mGhostObject->setWorldTransform(xform);

	if (!mCanStand)
		stand(); // check if we can stand
}
bool PhysicsEntite::canJump() const {
	return onGround();
}
void PhysicsEntite::jump() {
	if (!canJump())
		return;

	mVerticalVelocity = mJumpSpeed;
	mWasJumping = true;
}
bool PhysicsEntite::onGround() const {
	return mVerticalVelocity == 0 && mVerticalOffset == 0;
}
void PhysicsEntite::setUpInterpolate(bool value) {

}

bool PhysicsEntite::recoverFromPenetration(btCollisionWorld * collisionWorld)
{
	bool penetration = false;

	collisionWorld->getDispatcher()->dispatchAllCollisionPairs(mGhostObject->getOverlappingPairCache(), collisionWorld->getDispatchInfo(), collisionWorld->getDispatcher());

	mCurrentPosition = mGhostObject->getWorldTransform().getOrigin();

	btScalar maxPen = 0;

	for (int i = 0; i < mGhostObject->getOverlappingPairCache()->getNumOverlappingPairs(); i++)
	{
		mManifoldArray.resize(0);

		btBroadphasePair * collisionPair = &mGhostObject->getOverlappingPairCache()->getOverlappingPairArray()[i];

		if (collisionPair->m_algorithm)
			collisionPair->m_algorithm->getAllContactManifolds(mManifoldArray);

		for (int j = 0; j < mManifoldArray.size(); j++)
		{
			btPersistentManifold * manifold = mManifoldArray[j];
			btScalar directionSign = manifold->getBody0() == mGhostObject ? btScalar(-1) : btScalar(1);

			for (int p = 0; p < manifold->getNumContacts(); p++)
			{
				const btManifoldPoint & pt = manifold->getContactPoint(p);

				btScalar dist = pt.getDistance();

				if (dist < 0)
				{
					maxPen = dist;
					mTouchingNormal = pt.m_normalWorldOnB * directionSign;
					penetration = true;
				}

				mCurrentPosition += pt.m_normalWorldOnB * directionSign * dist * btScalar(0.2);


			}
		}
	}

	btTransform newTrans = mGhostObject->getWorldTransform();
	newTrans.setOrigin(mCurrentPosition);
	mGhostObject->setWorldTransform(newTrans);

	return penetration;
}

void PhysicsEntite::setRBForceImpulseBasedOnCollision()
{
	if (!mWalkDirection.isZero())
	{

		for (int i = 0; i < mGhostObject->getOverlappingPairCache()->getNumOverlappingPairs(); i++)
		{
			btBroadphasePair * collisionPair = &mGhostObject->getOverlappingPairCache()->getOverlappingPairArray()[i];

			btRigidBody * rb = (btRigidBody*)collisionPair->m_pProxy1->m_clientObject;

			if (mMass > rb->getInvMass())
			{
				btScalar resultMass = mMass - rb->getInvMass();
				btVector3 reflection = computeReflectionDirection(mWalkDirection * resultMass, getNormalizedVector(mWalkDirection));
				rb->applyCentralImpulse(reflection * -1);
			}
		}

	}
}

void PhysicsEntite::stepUp(btCollisionWorld * collisionWorld)
{
	btTransform start, end;
	mTargetPosition = mCurrentPosition + getUpAxisDirections()[mUpAxis] * (mStepHeight + (mVerticalOffset > 0 ? mVerticalOffset : 0));

	start.setIdentity();
	end.setIdentity();

	start.setOrigin(mCurrentPosition);
	end.setOrigin(mTargetPosition);

	ClosestNotMeConvexResultCallback callback(mGhostObject, getUpAxisDirections()[mUpAxis], btScalar(0.7071));
	callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
	callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

	if (mUseGhostObjectSweepTest)
		mGhostObject->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
	else
		collisionWorld->convexSweepTest(mConvexShape, start, end, callback);

	if (callback.hasHit())
	{
		if (callback.m_hitNormalWorld.dot(getUpAxisDirections()[mUpAxis]) > 0)
		{
			mCurrentStepOffset = mStepHeight * callback.m_closestHitFraction;
			mCurrentPosition.setInterpolate3(mCurrentPosition, mTargetPosition, callback.m_closestHitFraction);
		}

		mVerticalOffset = mVerticalVelocity = 0;
	}
	else
	{
		mCurrentStepOffset = mStepHeight;
		mCurrentPosition = mTargetPosition;
	}
}

btPairCachingGhostObject * PhysicsEntite::getGhostObject()
{
	return mGhostObject;
}

void PhysicsEntite::stepForwardAndStrafe(btCollisionWorld * collisionWorld, const btVector3 & walkMove)
{
	btTransform start, end;
	mTargetPosition = mCurrentPosition + walkMove;

	start.setIdentity();
	end.setIdentity();

	btScalar fraction = 1.0;
	btScalar distance2 = (mCurrentPosition - mTargetPosition).length2();

	if (mTouchingContact)
	{
		if (mNormalizedDirection.dot(mTouchingNormal) > 0)
			updateTargetPositionBasedOnCollision(mTouchingNormal);
	}

	int maxIter = 10;

	while (fraction > 0.01 && maxIter-- > 0)
	{
		start.setOrigin(mCurrentPosition);
		end.setOrigin(mTargetPosition);

		btVector3 sweepDirNegative(mCurrentPosition - mTargetPosition);

		ClosestNotMeConvexResultCallback callback(mGhostObject, sweepDirNegative, 0);
		callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
		callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

		btScalar margin = mConvexShape->getMargin();
		mConvexShape->setMargin(margin + mAddedMargin);

		if (mUseGhostObjectSweepTest)
			mGhostObject->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
		else
			collisionWorld->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);

		mConvexShape->setMargin(margin);

		fraction -= callback.m_closestHitFraction;

		if (callback.hasHit())
		{
			btScalar hitDistance = (callback.m_hitPointWorld - mCurrentPosition).length();

			updateTargetPositionBasedOnCollision(callback.m_hitNormalWorld);
			btVector3 currentDir = mTargetPosition - mCurrentPosition;
			distance2 = currentDir.length2();

			if (distance2 > SIMD_EPSILON)
			{
				currentDir.normalize();

				if (currentDir.dot(mNormalizedDirection) <= 0)
					break;
			}
			else
				break;
		}
		else
			mCurrentPosition = mTargetPosition;
	}
}

void PhysicsEntite::updateTargetPositionBasedOnCollision(const btVector3 & hitNormal, btScalar tangentMag, btScalar normalMag)
{
	btVector3 movementDirection = mTargetPosition - mCurrentPosition;
	btScalar movementLenght = movementDirection.length();

	if (movementLenght > SIMD_EPSILON)
	{
		movementDirection.normalize();

		btVector3 reflectDir = computeReflectionDirection(movementDirection, hitNormal);

		btVector3 parallelDir, perpindicularDir;

		parallelDir = parallelComponent(reflectDir, hitNormal);
		perpindicularDir = perpindicularComponent(reflectDir, hitNormal);

		mTargetPosition = mCurrentPosition;

		if (normalMag != 0)
		{
			btVector3 perpComponent = perpindicularDir * btScalar(normalMag * movementLenght);
			mTargetPosition += perpComponent;
		}
	}
}

void PhysicsEntite::stepDown(btCollisionWorld * collisionWorld, btScalar dt)
{
	btTransform start, end;

	btScalar downVelocity = (mVerticalVelocity < 0 ? -mVerticalVelocity : 0) * dt;

	if (downVelocity > 0 && downVelocity < mStepHeight && (mWasOnGround || !mWasJumping))
		downVelocity = mStepHeight;

	btVector3 stepDrop = getUpAxisDirections()[mUpAxis] * (mCurrentStepOffset + downVelocity);
	mTargetPosition -= stepDrop;

	start.setIdentity();
	end.setIdentity();

	start.setOrigin(mCurrentPosition);
	end.setOrigin(mTargetPosition);

	ClosestNotMeConvexResultCallback callback(mGhostObject, getUpAxisDirections()[mUpAxis], mMaxSlopeCosine);
	callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
	callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

	if (mUseGhostObjectSweepTest)
		mGhostObject->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
	else
		collisionWorld->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);

	if (callback.hasHit())
	{
		mCurrentPosition.setInterpolate3(mCurrentPosition, mTargetPosition, callback.m_closestHitFraction);
		mVerticalOffset = mVerticalVelocity = 0;
		mWasJumping = false;
	}
	else
		mCurrentPosition = mTargetPosition;
}

void PhysicsEntite::stand()
{
	if (!canStand())
		return;

	mConvexShape = mStandingConvexShape;
	mGhostObject->setCollisionShape(mStandingConvexShape);
}

bool PhysicsEntite::canStand()
{
	btTransform start, end;

	start.setIdentity();
	end.setIdentity();

	start.setOrigin(mCurrentPosition);
	end.setOrigin(mCurrentPosition + btVector3(0,
												static_cast<btCapsuleShape*>(mStandingConvexShape)->getHalfHeight() * 2 - static_cast<btCapsuleShape*>(mDuckingConvexShape)->getHalfHeight() * 2,
												0));

	ClosestNotMeConvexResultCallback callback(mGhostObject, -getUpAxisDirections()[mUpAxis], 0);
	callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
	callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

	if (mUseGhostObjectSweepTest)
		mGhostObject->convexSweepTest(mConvexShape, start, end, callback, PhysicsManager::getInstance()->getCollisionWorld()->getDispatchInfo().m_allowedCcdPenetration);
	else
		PhysicsManager::getInstance()->getCollisionWorld()->convexSweepTest(mConvexShape, start, end, callback);

	if (callback.hasHit())
	{
		mCanStand = false;
		return false;
	}
	else
	{
		mCanStand = true;
		return true;
	}
}

btVector3 PhysicsEntite::computeReflectionDirection(const btVector3 & direction, const btVector3 & normal)
{
	return direction - (btScalar(2) * direction.dot(normal)) * normal;
}

btVector3 PhysicsEntite::parallelComponent(const btVector3 & direction, const btVector3 & normal)
{
	btScalar magnitude = direction.dot(normal);
	return normal * magnitude;
}

btVector3 PhysicsEntite::perpindicularComponent(const btVector3 & direction, const btVector3 & normal)
{
	return direction - parallelComponent(direction, normal);
}

btVector3 PhysicsEntite::getPosition() const
{
	return mCurrentPosition;
}




} /* namespace Engine */
