/*
 * \file PhysicsMotionState.cpp
 *
 *  Created on: \date 9 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "PhysicsMotionState.h"

namespace Engine {

PhysicsMotionState::PhysicsMotionState(const btTransform & initialPos, Ogre::SceneNode * node) {
	mVisibleObj = node;
	mTransform = initialPos;
	mCOM = btTransform::getIdentity();

}

PhysicsMotionState::PhysicsMotionState(const btTransform & initialPos) {
	mVisibleObj = NULL;
	mTransform = initialPos;

}

PhysicsMotionState::~PhysicsMotionState() {
	// TODO Auto-generated destructor stub
}

void PhysicsMotionState::setNode(Ogre::SceneNode * node)
{
	mVisibleObj = node;
}

btTransform PhysicsMotionState::getWorldTransform() const
{
	return mCOM.inverse() * mTransform;
}

void PhysicsMotionState::getWorldTransform(btTransform & worldTrans) const
{
	worldTrans = mCOM.inverse() * mTransform;
}

void PhysicsMotionState::setWorldTransform(const btTransform & worldTrans)
{
	if (mVisibleObj == NULL)
		return;

	mTransform = worldTrans;
	btTransform transform = mTransform * mCOM;
	btQuaternion rot = transform.getRotation();
	btVector3 pos = transform.getOrigin();
	mVisibleObj->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
	mVisibleObj->setPosition(pos.x(), pos.y(), pos.z());
}

} /* namespace Engine */
