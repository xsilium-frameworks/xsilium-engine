/*
 * \file PhysicsMotionState.h
 *
 *  Created on: \date 9 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_PHYSICS_PHYSICSMOTIONSTATE_H_
#define ENGINE_PHYSICS_PHYSICSMOTIONSTATE_H_

#include "LinearMath/btDefaultMotionState.h"
#include "Ogre.h"

namespace Engine {

/*
 *
 */
class PhysicsMotionState : public btDefaultMotionState {
public:
	PhysicsMotionState(const btTransform & initialPos, Ogre::SceneNode * node);
	PhysicsMotionState(const btTransform & initialPos);
	virtual ~PhysicsMotionState();

	void setNode(Ogre::SceneNode * node);

	btTransform getWorldTransform() const;

	void getWorldTransform(btTransform & worldTrans) const;

	void setWorldTransform(const btTransform & worldTrans);

protected:
	Ogre::SceneNode * mVisibleObj;
	btTransform mTransform;
	btTransform mCOM;
};

} /* namespace Engine */

#endif /* ENGINE_PHYSICS_PHYSICSMOTIONSTATE_H_ */
