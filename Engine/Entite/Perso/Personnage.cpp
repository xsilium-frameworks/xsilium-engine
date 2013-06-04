/*
 * \file Personnage.cpp
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Personnage.h"

Personnage::Personnage(Ogre::SceneManager* sceneMgr) {

	this->sceneMgr = sceneMgr;
	charHeight = 5;
	turnSpeed = 500.0f;
	runSpeed = 17 ;
	mBodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode("bodyNode",Ogre::Vector3::UNIT_Y * charHeight);
	mBodyEnt = sceneMgr->createEntity("Perso", "Sinbad.mesh");

	mBodyEnt->setCastShadows(true);

	mBodyNode->attachObject(mBodyEnt);


	animation = new Animation(mBodyEnt);
	animation->loadAnimation();

}

Personnage::~Personnage() {
	delete animation;
	sceneMgr->destroyEntity(mBodyEnt);
	sceneMgr->getRootSceneNode()->removeAndDestroyChild("bodyNode");

}
