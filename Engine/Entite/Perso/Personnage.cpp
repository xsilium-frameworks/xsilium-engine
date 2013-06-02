/*
 * \file Personnage.cpp
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Personnage.h"

Personnage::Personnage(Ogre::Camera* cam) {


	sceneManager = cam->getSceneManager();

	setupBody(sceneManager);
	setupCamera(cam);

	animation = new Animation(mBodyEnt);
	animation->loadAnimation();

}

Personnage::~Personnage() {
	delete animation;

	mCameraPivot->removeAndDestroyChild("mCameraGoal");
	sceneManager->getRootSceneNode()->removeAndDestroyChild("mCameraPivot");
	sceneManager->getRootSceneNode()->removeAndDestroyChild("mCameraNode");
}

void Personnage::setupBody(Ogre::SceneManager* sceneMgr)
{
	// create main model
	mBodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3::UNIT_Y * CHAR_HEIGHT);
	mBodyEnt = sceneMgr->createEntity("Perso", "Sinbad.mesh");

	mBodyEnt->setCastShadows(true);

	mBodyNode->attachObject(mBodyEnt);

}

void Personnage::setupCamera(Ogre::Camera* cam)
{
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

	// our model is quite small, so reduce the clipping planes
	cam->setNearClipDistance(0.1);
	cam->setFarClipDistance(100);
	mCameraNode->attachObject(cam);
}
