/*
 * \file GestionnaireMouvement.cpp
 *
 *  Created on: \date 29 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireMouvement.h"

GestionnaireMouvement::GestionnaireMouvement() {

	keyboardMap = KeyboardMap::getInstance();
	inputManager = InputManager::getInstance();
	mKeyDirection = 0;
	mGoalDirection = 0;
	mPivotPitch = 0;
	entite = 0;
	mCameraGoal = 0;
	mCameraPivot = 0;
	mCameraNode = 0;
	sceneMgr = 0;
	clickgauche = false;
	deplacement = false;


	inputManager->addKeyListener(this,"GestionMouvementKey");
	inputManager->addMouseListener(this,"GestionMouvementMouse");
	XsiliumFramework::getInstance()->getRoot()->addFrameListener(this);

}

GestionnaireMouvement::~GestionnaireMouvement() {
	XsiliumFramework::getInstance()->getRoot()->removeFrameListener(this);
	inputManager->removeKeyListener(this);
	inputManager->removeMouseListener(this);

	mCameraPivot->removeAndDestroyChild("mCameraGoal");
	sceneMgr->getRootSceneNode()->removeAndDestroyChild("mCameraPivot");
	sceneMgr->getRootSceneNode()->removeAndDestroyChild("mCameraNode");
}

void GestionnaireMouvement::setCamera(Ogre::Camera* cam)
{
	sceneMgr = cam->getSceneManager() ;
	// create a pivot at roughly the character's shoulder
	mCameraPivot = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode("mCameraPivot");
	// this is where the camera should be soon, and it spins around the pivot
	mCameraGoal = mCameraPivot->createChildSceneNode("mCameraGoal",Ogre::Vector3(0, 0, 3));
	// this is where the camera actually is
	mCameraNode = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode("mCameraNode");
	mCameraNode->setPosition(mCameraPivot->getPosition() + mCameraGoal->getPosition());

	mCameraPivot->setFixedYawAxis(true);
	mCameraGoal->setFixedYawAxis(true);
	mCameraNode->setFixedYawAxis(true);

	mCameraNode->attachObject(cam);
}

bool GestionnaireMouvement::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	if(deplacement)
	{
		if( keyEventRef.key == keyboardMap->checkKey("GAUCHE"))
			mKeyDirection.x = -1;

		if( keyEventRef.key == keyboardMap->checkKey("DROITE"))
			mKeyDirection.x = 1;

		if( keyEventRef.key == keyboardMap->checkKey("AVANCER"))
			mKeyDirection.z = -1;

		if( keyEventRef.key == keyboardMap->checkKey("RECULER"))
			mKeyDirection.z = 1;
	}

	if (!mKeyDirection.isZeroLength())
	{
		// start running if not already moving and the player wants to move
		entite->runAnimation();
	}

	if( keyEventRef.key == keyboardMap->checkKey("DEGAINER"))
	{
		entite->degainerArme();
	}


	return true;


}

void GestionnaireMouvement::activeDeplacement()
{
	deplacement = true;
}
void GestionnaireMouvement::desactiveDeplacement()
{
	deplacement = false;
}

bool GestionnaireMouvement::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	if(deplacement)
	{
		if( keyEventRef.key == keyboardMap->checkKey("GAUCHE") && mKeyDirection.x == -1 )
			mKeyDirection.x = 0;

		if( keyEventRef.key == keyboardMap->checkKey("DROITE") && mKeyDirection.x == 1)
			mKeyDirection.x = 0;

		if( keyEventRef.key == keyboardMap->checkKey("AVANCER") && mKeyDirection.z == -1)
			mKeyDirection.z = 0;

		if( keyEventRef.key == keyboardMap->checkKey("RECULER")  && mKeyDirection.z == 1 )
			mKeyDirection.z = 0;
	}

	if (mKeyDirection.isZeroLength() && keyEventRef.key != keyboardMap->checkKey("DEGAINER") )
	{
		entite->idleAnimation();
	}

	return true;

}

bool GestionnaireMouvement::mouseMoved( const OIS::MouseEvent &event )
{
	if(clickgauche)
	{
		updateCameraGoal(-0.05f * event.state.X.rel, -0.05f * event.state.Y.rel, -0.0005f * event.state.Z.rel);
	}
	return true;
}
bool GestionnaireMouvement::mousePressed( const OIS::MouseEvent &event, OIS::MouseButtonID id )
{
	if(id == OIS::MB_Left)
	{
		clickgauche = true;
	}
	return true;
}
bool GestionnaireMouvement::mouseReleased( const OIS::MouseEvent &event, OIS::MouseButtonID id )
{
	if(id == OIS::MB_Left)
	{
		clickgauche = false;
	}
	return true;
}

void GestionnaireMouvement::setEntities(Entite * entite)
{
	this->entite = entite;
}

bool GestionnaireMouvement::frameStarted(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
bool GestionnaireMouvement::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
	updateBody(m_FrameEvent.timeSinceLastFrame);
	updateCamera(m_FrameEvent.timeSinceLastFrame);
	return true;
}
bool GestionnaireMouvement::frameEnded(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
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
		Ogre::Real yawAtSpeed = yawToGoal / Ogre::Math::Abs(yawToGoal) * timeSinceLastFrame * entite->getTurnSpeed();

		// turn as much as we can, but not more than we need to
		if (yawToGoal < 0)
			yawToGoal = std::min<Ogre::Real>(0, std::max<Ogre::Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, yawAtSpeed, 0);
		else if (yawToGoal > 0)
			yawToGoal = std::max<Ogre::Real>(0, std::min<Ogre::Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, 0, yawAtSpeed);

		entite->getBody()->yaw(Ogre::Degree(yawToGoal));

		// move in current body direction (not the goal direction)
		entite->getBody()->translate(0, 0, timeSinceLastFrame * entite->getRunSpeed(),Ogre::Node::TS_LOCAL);
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
	if (!(dist + distChange < 1 && distChange < 0) && !(dist + distChange > 8 && distChange > 0))
	{
		mCameraGoal->translate(0, 0, distChange, Ogre::Node::TS_LOCAL);
	}
}

