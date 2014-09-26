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
	orientation = Ogre::Vector3::UNIT_X;
	positionFinal = Ogre::Vector3::ZERO;

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

	if( positionFinal != Ogre::Vector3::ZERO )
	{
		Ogre::Vector3 mGoalDirection = Ogre::Vector3::ZERO;
		// calculate actually goal direction in world based on player's key directions
		mGoalDirection += positionFinal.z * orientation.z;
		mGoalDirection += positionFinal.x * orientation.x;
		mGoalDirection.y += positionFinal.y * orientation.y;
		mGoalDirection.normalise();

		Ogre::Quaternion toGoal = mMainNode->getOrientation().zAxis().getRotationTo(mGoalDirection);

		// calculate how much the character has to turn to face goal direction
		Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();
		// this is how much the character CAN turn this frame
		Ogre::Real yawAtSpeed = yawToGoal / Ogre::Math::Abs(yawToGoal) * timeSinceLastFrame * turnSpeed;

		// turn as much as we can, but not more than we need to
		if (yawToGoal < 0)
			yawToGoal = std::min<Ogre::Real>(0, std::max<Ogre::Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, yawAtSpeed, 0);
		else if (yawToGoal > 0)
			yawToGoal = std::max<Ogre::Real>(0, std::min<Ogre::Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, 0, yawAtSpeed);

		mMainNode->yaw(Ogre::Degree(yawToGoal));

		// move in current body direction (not the goal direction)
		mMainNode->translate(0, 0, timeSinceLastFrame * runSpeed,Ogre::Node::TS_LOCAL);
		runAnimation();

	}
	else
	{
		if(graphicsAnimation->getNomAnimationBasActuel().compare("RunBase") == 0 )
		{
			idleAnimation();
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

void GraphicsEntite::deplaceEntite(Ogre::Vector3 positionFinal)
{
    positionFinal.normalise();
	this->positionFinal = positionFinal;
}

void GraphicsEntite::setOrientation(Ogre::Vector3 orientation)
{
	this->orientation = orientation;
}

void GraphicsEntite::setID(int id)
{
	this->id = id;
}
int GraphicsEntite::getID()
{
	return id;
}

void GraphicsEntite::processEvent(Event * event)
{
	if(event->hasProperty("NewPositionX"))
	{
		deplaceEntite( Ogre::Vector3(atoi(event->getProperty("NewPositionX").c_str()),
				atoi(event->getProperty("NewPositionY").c_str()),
				atoi(event->getProperty("NewPositionZ").c_str()))  );
	}

	if(event->hasProperty("NewOrientationX"))
	{
		deplaceEntite( Ogre::Vector3(
				atoi(event->getProperty("NewOrientationX").c_str()),
				atoi(event->getProperty("NewOrientationY").c_str()),
				atoi(event->getProperty("NewOrientationZ").c_str()))  );
	}

}



} /* namespace Engine */
