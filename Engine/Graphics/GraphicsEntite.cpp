/*
 * \file GraphicsEntite.cpp
 *
 *  Created on: \date 4 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsEntite.h"

namespace Engine {

GraphicsEntite::GraphicsEntite() {
	id  = 0;
	charHeight = 0;
	runSpeed = 0;
	turnSpeed = 0;
	msceneMgr = 0;
	mMainNode = 0;
	mBodyEnt = 0;
	graphicsAnimation = 0;
	direction = Ogre::Vector3::ZERO;
	degainer = false;

	mMoving = false;

	physicsEntite = 0;


	animNames[ANIM_IDLE_BASE] = "IdleBase" ;
	animNames[ANIM_IDLE_TOP] =		"IdleTop" ;

	animNames[ANIM_RUN_BASE] =		"RunBase";
	animNames[ANIM_RUN_TOP] =		"RunTop";

	animNames[ANIM_HANDS_CLOSED] =		"HandsClosed";
	animNames[ANIM_HANDS_RELAXED] =		"HandsRelaxed";

	animNames[ANIM_DRAW_SWORDS] =		"DrawSwords";

	animNames[ANIM_SLICE_VERTICAL] =		"SliceVertical";
	animNames[ANIM_SLICE_HORIZONTAL] =		"SliceHorizontal";

	animNames[ANIM_JUMP_START] =		"JumpStart";
	animNames[ANIM_JUMP_LOOP] =		"JumpLoop";
	animNames[ANIM_JUMP_END] =		"JumpEnd";

}

GraphicsEntite::~GraphicsEntite() {
	delete physicsEntite;
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

	physicsEntite = new PhysicsEntite();

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
	graphicsAnimation->setAnimationHaut(animNames[ANIM_DRAW_SWORDS],true);
}

void GraphicsEntite::update(double timeSinceLastFrame)
{
	Ogre::Vector3 playerPos = mMainNode->getPosition();

	btVector3 pos = physicsEntite->getPosition();

	Ogre::Vector3 position(pos.x(), pos.y(), pos.z());

	if (position != playerPos)
	{
		mMainNode->translate((position - playerPos) * runSpeed * timeSinceLastFrame);

		if (!mIsFalling && !physicsEntite->onGround()) // last frame we were on ground and now we're in "air"
		{
			mIsFalling = true;

			graphicsAnimation->setAnimationBas(animNames[ANIM_JUMP_LOOP].c_str());
		}
		else if (physicsEntite->onGround() && mIsFalling) // last frame we were falling and now we're on the ground
		{
			mIsFalling = false;
			graphicsAnimation->setAnimationBas(animNames[ANIM_JUMP_END].c_str());
		}
	}
    
	updateAnimation(timeSinceLastFrame);

	if( direction != Ogre::Vector3::ZERO )
	{
		Ogre::Quaternion toGoal = mMainNode->getOrientation().zAxis().getRotationTo(direction);

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

		physicsEntite->setWalkDirection(direction.x * runSpeed * timeSinceLastFrame, direction.y * runSpeed * timeSinceLastFrame, direction.z * runSpeed * timeSinceLastFrame);

		if(!mMoving)
		{
			mMoving = true;
			graphicsAnimation->setAnimationBas(animNames[ANIM_RUN_BASE].c_str());
			graphicsAnimation->setAnimationHaut(animNames[ANIM_RUN_TOP].c_str());
		}
	}
	else
	{
		if(mMoving)
		{
			mMoving = false;
			physicsEntite->setWalkDirection(0, 0, 0);
			graphicsAnimation->setAnimationBas(animNames[ANIM_IDLE_BASE].c_str());
			graphicsAnimation->setAnimationHaut(animNames[ANIM_IDLE_TOP].c_str());
		}

	}

	graphicsAnimation->updateAnimation(timeSinceLastFrame) ;
}

void GraphicsEntite::updateAnimation(double timeSinceLastFrame)
{
	if (graphicsAnimation->getNomAnimationBasActuel().compare(animNames[ANIM_JUMP_START]) == 0 && graphicsAnimation->getTime() >= mBodyEnt->getAnimationState(graphicsAnimation->getNomAnimationBasActuel())->getLength())
	{
		// takeoff animation finished, so time to leave the ground!
		graphicsAnimation->setAnimationBas(animNames[ANIM_JUMP_LOOP].c_str(),1);
	}
	else if (graphicsAnimation->getNomAnimationBasActuel().compare(animNames[ANIM_JUMP_END]) == 0)
	{
		if (graphicsAnimation->getTime() >= mBodyEnt->getAnimationState(graphicsAnimation->getNomAnimationBasActuel())->getLength())
		{
			if (mMoving)
			{
				graphicsAnimation->setAnimationBas(animNames[ANIM_RUN_BASE].c_str());
				graphicsAnimation->setAnimationHaut(animNames[ANIM_RUN_TOP].c_str());
			}
			else
			{
				graphicsAnimation->setAnimationBas(animNames[ANIM_IDLE_BASE].c_str());
				graphicsAnimation->setAnimationHaut(animNames[ANIM_IDLE_TOP].c_str());
			}
		}
	}

	if(graphicsAnimation->getNomAnimationHautActuel().compare(animNames[ANIM_RUN_BASE]) == 0)
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
				graphicsAnimation->unsetAnimationSeul(animNames[ANIM_HANDS_RELAXED].c_str());
				graphicsAnimation->setAnimationSeul(animNames[ANIM_HANDS_CLOSED].c_str());
			}
			else
			{
				graphicsAnimation->unsetAnimationSeul(animNames[ANIM_HANDS_CLOSED].c_str());
				graphicsAnimation->setAnimationSeul(animNames[ANIM_HANDS_RELAXED].c_str());
			}

		}

		if (graphicsAnimation->getTime() > mBodyEnt->getAnimationState(graphicsAnimation->getNomAnimationHautActuel())->getLength() )
		{
			if(graphicsAnimation->getNomAnimationBasActuel().compare(animNames[ANIM_IDLE_BASE]) == 0 )
			{
				graphicsAnimation->setAnimationHaut(animNames[ANIM_IDLE_TOP].c_str());
			}
			else
			{
				graphicsAnimation->setAnimationBas(animNames[ANIM_RUN_BASE].c_str());
				graphicsAnimation->setAnimationHaut(animNames[ANIM_RUN_TOP].c_str());
				mBodyEnt->getAnimationState(animNames[ANIM_RUN_TOP].c_str())->setTimePosition(mBodyEnt->getAnimationState(graphicsAnimation->getNomAnimationBasActuel())->getTimePosition());
			}
		}
	}
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

void GraphicsEntite::deplaceEntite(Ogre::Vector3 direction)
{
	direction.normalise();
	this->direction = direction;
}

void GraphicsEntite::setOrientation(Ogre::Quaternion orientation)
{
	mMainNode->setOrientation(orientation);
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
	if(event->hasProperty("NewDirection"))
	{
		deplaceEntite( Ogre::Vector3(
				atoi(event->getProperty("NewPositionX").c_str()),
				atoi(event->getProperty("NewPositionY").c_str()),
				atoi(event->getProperty("NewPositionZ").c_str()))  );
	}

	if(event->hasProperty("NewOrientation"))
	{
		setOrientation( Ogre::Quaternion(
				atoi(event->getProperty("NewOrientationW").c_str()),
				atoi(event->getProperty("NewOrientationX").c_str()),
				atoi(event->getProperty("NewOrientationY").c_str()),
				atoi(event->getProperty("NewOrientationZ").c_str()))  );
	}
	if(event->hasProperty("Jump"))
	{
		if (physicsEntite->canJump())
		{
			physicsEntite->jump();
			graphicsAnimation->setAnimationBas(animNames[ANIM_JUMP_START].c_str(),1);

		}
	}
	if(event->hasProperty("Camera"))
	{
		GraphicsCamera::getInstance()->setTarget(mMainNode);
	}

}



} /* namespace Engine */
