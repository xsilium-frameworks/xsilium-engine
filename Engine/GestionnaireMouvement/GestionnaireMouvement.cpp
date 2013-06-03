/*
 * \file GestionnaireMouvement.cpp
 *
 *  Created on: \date 29 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireMouvement.h"

GestionnaireMouvement::GestionnaireMouvement(Ogre::Camera* cam) {

	keyboardMap = KeyboardMap::getInstance();
	inputManager = InputManager::getSingletonPtr();
	mKeyDirection = 0;
	mGoalDirection = 0;
	// create a pivot at roughly the character's shoulder
	mCameraPivot = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode("mCameraPivot");
	// this is where the camera should be soon, and it spins around the pivot
	mCameraGoal = mCameraPivot->createChildSceneNode("mCameraGoal",Ogre::Vector3(0, 0, 15));
	// this is where the camera actually is
	mCameraNode = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode("mCameraNode");
	mCameraNode->setPosition(mCameraPivot->getPosition() + mCameraGoal->getPosition());

	mCameraPivot->setFixedYawAxis(true);
	mCameraGoal->setFixedYawAxis(true);
	mCameraNode->setFixedYawAxis(true);

	mCameraNode->attachObject(cam);
	mPivotPitch = 0;
	entite = 0;


	inputManager->addKeyListener(this,"GestionMouvementKey");
	inputManager->addMouseListener(this,"GestionMouvementMouse");

}

GestionnaireMouvement::~GestionnaireMouvement() {
	inputManager->removeKeyListener(this);
	inputManager->removeMouseListener(this);

    mCameraPivot->removeAndDestroyChild("mCameraGoal");
    sceneManager->getRootSceneNode()->removeAndDestroyChild("mCameraPivot");
    sceneManager->getRootSceneNode()->removeAndDestroyChild("mCameraNode");
}

bool GestionnaireMouvement::keyPressed(const OIS::KeyEvent &keyEventRef)
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
bool GestionnaireMouvement::keyReleased(const OIS::KeyEvent &keyEventRef)
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

bool GestionnaireMouvement::mouseMoved( const OIS::MouseEvent &event )
{
	updateCameraGoal(-0.05f * event.state.X.rel, -0.05f * event.state.Y.rel, -0.0005f * event.state.Z.rel);
	return true;
}
bool GestionnaireMouvement::mousePressed( const OIS::MouseEvent &event, OIS::MouseButtonID id )
{
	return true;
}
bool GestionnaireMouvement::mouseReleased( const OIS::MouseEvent &event, OIS::MouseButtonID id )
{
	return true;
}

void GestionnaireMouvement::setEntities(Entite * entite)
{
	this->entite = entite;
}



void GestionnaireMouvement::update(double timeSinceLastFrame)
{
	updateBody(timeSinceLastFrame);
	updateCamera(timeSinceLastFrame);
}

void GestionnaireMouvement::updateBody(double timeSinceLastFrame)
{
	mGoalDirection = Ogre::Vector3::ZERO;   // we will calculate this

	if (mKeyDirection != Ogre::Vector3::ZERO)
	{
		// calculate actually goal direction in world based on player's key directions
		mGoalDirection += mKeyDirection.z * mCameraNode->getOrientation().zAxis();
		mGoalDirection += mKeyDirection.x * mCameraNode->getOrientation().xAxis();
		mGoalDirection.y = 0;
		mGoalDirection.normalise();

		Ogre::Quaternion toGoal = entite->getBody()->getOrientation().zAxis().getRotationTo(mGoalDirection);

		// calculate how much the character has to turn to face goal direction
		Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();
		// this is how much the character CAN turn this frame
		Ogre::Real yawAtSpeed = yawToGoal / Ogre::Math::Abs(yawToGoal) * timeSinceLastFrame * TURN_SPEED;

		// turn as much as we can, but not more than we need to
		if (yawToGoal < 0)
			yawToGoal = std::min<Ogre::Real>(0, std::max<Ogre::Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, yawAtSpeed, 0);
		else if (yawToGoal > 0)
			yawToGoal = std::max<Ogre::Real>(0, std::min<Ogre::Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, 0, yawAtSpeed);

		entite->getBody()->yaw(Ogre::Degree(yawToGoal));

		// move in current body direction (not the goal direction)
		entite->getBody()->translate(0, 0, timeSinceLastFrame * RUN_SPEED,Ogre::Node::TS_LOCAL);

	}
	else
	{

	}
}

void GestionnaireMouvement::updateCamera(double timeSinceLastFrame)
{
	// place the camera pivot roughly at the character's shoulder
	mCameraPivot->setPosition(entite->getBody()->getPosition() + Ogre::Vector3::UNIT_Y * CAM_HEIGHT);

	// move the camera smoothly to the goal
	Ogre::Vector3 goalOffset = mCameraGoal->_getDerivedPosition() - mCameraNode->getPosition();
	mCameraNode->translate(goalOffset * timeSinceLastFrame * 9.0f);
	// always look at the pivot
	mCameraNode->lookAt(mCameraPivot->_getDerivedPosition(), Ogre::Node::TS_WORLD);
}

void GestionnaireMouvement::updateCameraGoal(Ogre::Real deltaYaw, Ogre::Real deltaPitch, Ogre::Real deltaZoom)
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

