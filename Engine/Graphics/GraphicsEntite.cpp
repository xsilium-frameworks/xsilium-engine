/*
 * \file GraphicsEntite.cpp
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsEntite.h"

namespace Engine {

GraphicsEntite::GraphicsEntite() {
	charHeight = 0;
	runSpeed = 0;
	turnSpeed = 0;
	msceneMgr = 0;
	mMainNode = 0;
	mBodyEnt = 0;
	graphicsAnimation = 0;

	degainer = false;

}

GraphicsEntite::~GraphicsEntite() {
	delete graphicsAnimation;
}

void GraphicsEntite::initEntite(Ogre::SceneManager* sceneMgr,Ogre::String nom,Ogre::String fileMesh)
{
	this->msceneMgr = sceneMgr;
	this->nom = nom;

	mMainNode = msceneMgr->getRootSceneNode ()->createChildSceneNode (nom);

	mBodyEnt = sceneMgr->createEntity(fileMesh);

	mBodyEnt->setCastShadows(true);

	mMainNode->attachObject(mBodyEnt);


	graphicsAnimation = new GraphicsAnimation(mBodyEnt);
	graphicsAnimation->loadAnimation();
}

void GraphicsEntite::setCharHeight(int charHeight)
{
	this->charHeight = charHeight;
}

void GraphicsEntite::setRunSpeed(int runSpeed)
{
	this->runSpeed = runSpeed;
}

void GraphicsEntite::setTurnSpeed(double turnSpeed)
{
	this->turnSpeed = turnSpeed;
}

Ogre::Vector3 GraphicsEntite::getWorldPosition () {
	return mMainNode->_getDerivedPosition ();
}

Ogre::String * GraphicsEntite::getNom()
{
	return &this->nom ;
}

void GraphicsEntite::degainerArme()
{
	graphicsAnimation->setAnimationHaut("DrawSwords",true);
}

void GraphicsEntite::update(double timeSinceLastFrame)
{
	if(graphicsAnimation->getNomAnimationHautActuel().compare("DrawSwords") == 0)
	{
		if (graphicsAnimation->getTime() >= mBodyEnt->getAnimationState(graphicsAnimation->getNomAnimationHautActuel())->getLength() / 2 && graphicsAnimation->getTime() - timeSinceLastFrame < mBodyEnt->getAnimationState(graphicsAnimation->getNomAnimationHautActuel())->getLength() / 2 )
		{
			std::map<Ogre::String,Ogre::Entity*>::iterator it;
			degainer = !degainer;
			it=listOfObject.find(degainer ? "Handle.L" : "Sheath.L");
			if (it != listOfObject.end() )
			{
				mBodyEnt->detachObjectFromBone(it->second);
				mBodyEnt->attachObjectToBone(degainer ? "Handle.L" : "Sheath.L", it->second);
			}
			it=listOfObject.find(degainer ? "Handle.R" : "Sheath.R");
			if (it != listOfObject.end() )
			{
				mBodyEnt->detachObjectFromBone(it->second);
				mBodyEnt->attachObjectToBone(degainer ? "Handle.R" : "Sheath.R", it->second);
			}

			if(degainer)
			{
				graphicsAnimation->unsetAnimationSeul("HandsRelaxed");
				graphicsAnimation->setAnimationSeul("HandsClosed");
			}
			else
			{
				graphicsAnimation->unsetAnimationSeul("HandsClosed");
				graphicsAnimation->setAnimationSeul("HandsRelaxed");
			}

		}

		if (graphicsAnimation->getTime() > mBodyEnt->getAnimationState(graphicsAnimation->getNomAnimationHautActuel())->getLength() )
		{
			if(graphicsAnimation->getNomAnimationBasActuel().compare("IdleBase") == 0 )
			{
				idleAnimation();
			}
			else
			{
				runAnimation();
				mBodyEnt->getAnimationState("RunTop")->setTimePosition(mBodyEnt->getAnimationState(graphicsAnimation->getNomAnimationBasActuel())->getTimePosition());
			}
		}
	}

	graphicsAnimation->updateAnimation(timeSinceLastFrame) ;
}

void GraphicsEntite::runAnimation()
{
	graphicsAnimation->setAnimationBas("RunBase");
	graphicsAnimation->setAnimationHaut("RunTop");
}
void GraphicsEntite::idleAnimation()
{
	graphicsAnimation->setAnimationBas("IdleBase");
	graphicsAnimation->setAnimationHaut("IdleTop");
}

void GraphicsEntite::setPosition(Ogre::Vector3 position)
{
	mMainNode->setPosition(position);
}

void GraphicsEntite::addEquipement(Ogre::Entity * objet,Ogre::String emplacement)
{
	listOfObject[emplacement] = objet;
	mBodyEnt->attachObjectToBone(emplacement, objet);
}

void GraphicsEntite::deleteEquipement(Ogre::String emplacement)
{
	std::map<Ogre::String,Ogre::Entity*>::iterator it = listOfObject.find(emplacement);
	if (it != listOfObject.end())
	{
		listOfObject.erase(it);
	}

}

} /* namespace Engine */
