/*
 * \file MouvementPersonnage.cpp
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "MouvementPersonnage.h"

MouvementPersonnage::MouvementPersonnage(Ogre::SceneNode* mBodyNode,Ogre::SceneNode* mCameraNode,Ogre::SceneNode* mCameraPivot,Ogre::SceneNode* mCameraGoal) {
	inputManager = InputManager::getSingletonPtr();
	keyboardMap = KeyboardMap::getInstance();
	this->mBodyNode = mBodyNode;
	this->mCameraNode = mCameraNode;
	this->mCameraPivot = mCameraPivot;
	this->mCameraGoal = mCameraGoal;
	mKeyDirection = Ogre::Vector3::ZERO;
	mPivotPitch = 0;



	inputManager->addKeyListener(this,"PersoKey");
	inputManager->addMouseListener(this,"PersoMouse");

}

MouvementPersonnage::~MouvementPersonnage() {
	inputManager->removeKeyListener(this);
	inputManager->removeMouseListener(this);
}

bool MouvementPersonnage::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	if( keyEventRef.key == keyboardMap->checkKey("GAUCHE"))
		mKeyDirection.x = -1;

	if( keyEventRef.key == keyboardMap->checkKey("DROITE"))
		mKeyDirection.x = 1;

	if( keyEventRef.key == keyboardMap->checkKey("AVANCER"))
		mKeyDirection.z = -1;

	if( keyEventRef.key == keyboardMap->checkKey("RECULER"))
		mKeyDirection.z = 1;

	return true;


}
bool MouvementPersonnage::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	if( keyEventRef.key == keyboardMap->checkKey("GAUCHE") && mKeyDirection.x == -1 )
		mKeyDirection.x = 0;

	if( keyEventRef.key == keyboardMap->checkKey("DROITE") && mKeyDirection.x == 1)
		mKeyDirection.x = 0;

	if( keyEventRef.key == keyboardMap->checkKey("AVANCER") && mKeyDirection.z == -1)
		mKeyDirection.z = 0;

	if( keyEventRef.key == keyboardMap->checkKey("RECULER")  && mKeyDirection.z == 1 )
		mKeyDirection.z = 0;

	return true;

}

bool MouvementPersonnage::mouseMoved( const OIS::MouseEvent &event )
{
	updateCameraGoal(-0.05f * event.state.X.rel, -0.05f * event.state.Y.rel, -0.0005f * event.state.Z.rel);
	return true;
}
bool MouvementPersonnage::mousePressed( const OIS::MouseEvent &event, OIS::MouseButtonID id )
{
	return true;
}
bool MouvementPersonnage::mouseReleased( const OIS::MouseEvent &event, OIS::MouseButtonID id )
{
	return true;
}

void MouvementPersonnage::update(double timeSinceLastFrame)
{
	updateBody(timeSinceLastFrame);
	updateCamera(timeSinceLastFrame);
}

void MouvementPersonnage::updateBody(double timeSinceLastFrame)
{
	mGoalDirection = Ogre::Vector3::ZERO;   // we will calculate this

	if (mKeyDirection != Ogre::Vector3::ZERO)
	{
		// calculate actually goal direction in world based on player's key directions
		mGoalDirection += mKeyDirection.z * mCameraNode->getOrientation().zAxis();
		mGoalDirection += mKeyDirection.x * mCameraNode->getOrientation().xAxis();
		mGoalDirection.y = 0;
		mGoalDirection.normalise();

		Ogre::Quaternion toGoal = mBodyNode->getOrientation().zAxis().getRotationTo(mGoalDirection);

		// calculate how much the character has to turn to face goal direction
		Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();
		// this is how much the character CAN turn this frame
		Ogre::Real yawAtSpeed = yawToGoal / Ogre::Math::Abs(yawToGoal) * timeSinceLastFrame * TURN_SPEED;

		// turn as much as we can, but not more than we need to
		if (yawToGoal < 0)
			yawToGoal = std::min<Ogre::Real>(0, std::max<Ogre::Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, yawAtSpeed, 0);
		else if (yawToGoal > 0)
			yawToGoal = std::max<Ogre::Real>(0, std::min<Ogre::Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, 0, yawAtSpeed);

		mBodyNode->yaw(Ogre::Degree(yawToGoal));

		// move in current body direction (not the goal direction)
		mBodyNode->translate(0, 0, timeSinceLastFrame * RUN_SPEED,Ogre::Node::TS_LOCAL);
	}
}

void MouvementPersonnage::updateCamera(double timeSinceLastFrame)
{
	// place the camera pivot roughly at the character's shoulder
	mCameraPivot->setPosition(mBodyNode->getPosition() + Ogre::Vector3::UNIT_Y * CAM_HEIGHT);

	// move the camera smoothly to the goal
	Ogre::Vector3 goalOffset = mCameraGoal->_getDerivedPosition() - mCameraNode->getPosition();
	mCameraNode->translate(goalOffset * timeSinceLastFrame * 9.0f);
	// always look at the pivot
	mCameraNode->lookAt(mCameraPivot->_getDerivedPosition(), Ogre::Node::TS_WORLD);
}

void MouvementPersonnage::updateCameraGoal(Ogre::Real deltaYaw, Ogre::Real deltaPitch, Ogre::Real deltaZoom)
{
	mCameraPivot->yaw(Ogre::Degree(deltaYaw), Ogre::Node::TS_WORLD);

	// bound the pitch
	if (!(mPivotPitch + deltaPitch > 25 && deltaPitch > 0) && !(mPivotPitch + deltaPitch < -60 && deltaPitch < 0))
	{
		mCameraPivot->pitch(Ogre::Degree(deltaPitch), Ogre::Node::TS_LOCAL);
		mPivotPitch += deltaPitch;
	}

	Ogre::Real dist = mCameraGoal->_getDerivedPosition().distance(mCameraPivot->_getDerivedPosition());
	Ogre::Real distChange = deltaZoom * dist;

	// bound the zoom
	if (!(dist + distChange < 8 && distChange < 0) && !(dist + distChange > 25 && distChange > 0))
	{
		mCameraGoal->translate(0, 0, distChange, Ogre::Node::TS_LOCAL);
	}
}
