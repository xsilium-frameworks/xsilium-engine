/*
 * \file Personnage.cpp
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Personnage.h"

Personnage::Personnage(Ogre::SceneManager* sceneMgr,const char * nom) {

	this->sceneMgr = sceneMgr;
	charHeight = 5;
	turnSpeed = 500.0f;
	runSpeed = 17 ;
	setNom(nom);
	mBodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(nom,Ogre::Vector3::UNIT_Y * charHeight);
	mBodyEnt = sceneMgr->createEntity("Sinbad.mesh");

	mBodyEnt->setCastShadows(true);

	mBodyNode->attachObject(mBodyEnt);


	animation = new Animation(mBodyEnt);
	animation->loadAnimation();

}

Personnage::~Personnage() {
	delete animation;
	sceneMgr->destroyEntity(mBodyEnt);
	sceneMgr->getRootSceneNode()->removeAndDestroyChild(getNom()->c_str());

}

void Personnage::update(double timeSinceLastFrame)
{
	Entite::update(timeSinceLastFrame);
}
