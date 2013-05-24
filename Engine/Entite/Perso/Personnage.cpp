/*
 * \file Personnage.cpp
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Personnage.h"

Personnage::Personnage(Ogre::Camera* cam) {

	setupBody(cam->getSceneManager());
	setupCamera(cam);

	mouvementPersonnage = new MouvementPersonnage(mBodyNode,mCameraNode,mCameraPivot,mCameraGoal);

	XsiliumFramework::getInstance()->getRoot()->addFrameListener(this);

}

Personnage::~Personnage() {
	XsiliumFramework::getInstance()->getRoot()->removeFrameListener(this);
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
	mCameraPivot = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	// this is where the camera should be soon, and it spins around the pivot
	mCameraGoal = mCameraPivot->createChildSceneNode(Ogre::Vector3(0, 0, 15));
	// this is where the camera actually is
	mCameraNode = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mCameraNode->setPosition(mCameraPivot->getPosition() + mCameraGoal->getPosition());

	mCameraPivot->setFixedYawAxis(true);
	mCameraGoal->setFixedYawAxis(true);
	mCameraNode->setFixedYawAxis(true);

	// our model is quite small, so reduce the clipping planes
	cam->setNearClipDistance(0.1);
	cam->setFarClipDistance(100);
	mCameraNode->attachObject(cam);
}

bool Personnage::frameStarted (const Ogre::FrameEvent &evt)
{
	return true;
}

bool Personnage::frameRenderingQueued (const Ogre::FrameEvent &evt)
{
	mouvementPersonnage->update(evt.timeSinceLastEvent);
	return true;
}

bool Personnage::frameEnded (const Ogre::FrameEvent &evt)
{
	return true;
}
