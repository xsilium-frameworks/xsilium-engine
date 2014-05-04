/*
 * \file Personnage.cpp
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Personnage.h"

Personnage::Personnage(Ogre::SceneManager* sceneMgr,const char * nom,const char * fileMesh) {

	this->sceneMgr = sceneMgr;
	charHeight = 1;
	turnSpeed = 500.0f;
	runSpeed = 3 ;
	setNom(nom);
	mBodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(nom,Ogre::Vector3::UNIT_Y * charHeight);
	mBodyNode->setPosition(Ogre::Vector3(0,0.7,0));
	mBodyEnt = sceneMgr->createEntity(fileMesh);

	mBodyEnt->setCastShadows(true);

	mBodyNode->attachObject(mBodyEnt);
	mBodyNode->setScale(0.15,0.15,0.15);


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

void Personnage::processAnimation(Event * event)
{
    if(event->hasProperty("AnimationBas"))
    {
    	if(event->hasProperty("AnimationBasReset"))
    	{
    		animation->setAnimationBas(event->getProperty("AnimationBas").c_str(),atoi(event->getProperty("AnimationBasReset").c_str()));
    	}
    	else
    	{
    		animation->setAnimationBas(event->getProperty("AnimationBas").c_str());
    	}
    }
    if(event->hasProperty("AnimationHaut"))
    {
    	if(event->hasProperty("AnimationHautReset"))
    	{
    		animation->setAnimationHaut(event->getProperty("AnimationHaut").c_str(),atoi(event->getProperty("AnimationHautReset").c_str()));
    	}
    	else
    	{
    		animation->setAnimationHaut(event->getProperty("AnimationHaut").c_str());
    	}
    }
}
