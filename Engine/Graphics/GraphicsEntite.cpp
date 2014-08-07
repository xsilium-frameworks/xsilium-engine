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
	countObjet = 0;
	msceneMgr = 0;
	mMainNode = 0;
    mSightNode = 0;
    mCameraNode = 0;
	mBodyEnt = 0;
	graphicsAnimation = 0;

	degainer = false;

}

GraphicsEntite::~GraphicsEntite() {
	// TODO Auto-generated destructor stub
}

void GraphicsEntite::initEntite(Ogre::SceneManager* sceneMgr,Ogre::String nom,Ogre::String fileMesh)
{
	this->msceneMgr = sceneMgr;
	this->nom = nom;

	mMainNode = msceneMgr->getRootSceneNode ()->createChildSceneNode (nom);
	mSightNode = mMainNode->createChildSceneNode (nom + "_sight", Ogre::Vector3 (0, 0, 100));
	mCameraNode = mMainNode->createChildSceneNode (nom + "_camera", Ogre::Vector3 (0, 50, -100));

	mBodyEnt = sceneMgr->createEntity(fileMesh);

	mBodyEnt->setCastShadows(true);

	mMainNode->attachObject(mBodyEnt);
	mMainNode->setScale(0.15,0.15,0.15);


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

Ogre::SceneNode * GraphicsEntite::getSightNode () {
	return mSightNode;
}
Ogre::SceneNode * GraphicsEntite::getCameraNode () {
	return mCameraNode;
}
Ogre::Vector3 GraphicsEntite::getWorldPosition () {
	return mMainNode->_getDerivedPosition ();
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
			std::map<int,GraphicsObjet*>::iterator it;
			degainer = !degainer;
			it=listOfObject.find(1);
			mBodyEnt->detachObjectFromBone(it->second->getObjet());
			mBodyEnt->attachObjectToBone(degainer ? "Handle.L" : "Sheath.L", it->second->getObjet());
			it=listOfObject.find(2);
			mBodyEnt->detachObjectFromBone(it->second->getObjet());
			mBodyEnt->attachObjectToBone(degainer ? "Handle.R" : "Sheath.R", it->second->getObjet());

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

void GraphicsEntite::addEquipement(Ogre::String nomObjet,Ogre::String fileMesh,Ogre::String emplacement)
{
	GraphicsObjet * graphicsObjetTemp = new GraphicsObjet();
	graphicsObjetTemp->initObjet(msceneMgr,nomObjet,fileMesh);
	countObjet += 1;
	mBodyEnt->attachObjectToBone(emplacement, graphicsObjetTemp->getObjet());
	listOfObject.insert ( std::pair<int,GraphicsObjet*>(countObjet,graphicsObjetTemp) );


}

} /* namespace Engine */
