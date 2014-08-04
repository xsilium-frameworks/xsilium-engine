/*
 * \file GraphicsAnimation.cpp
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsAnimation.h"

namespace Engine {

GraphicsAnimation::GraphicsAnimation(Ogre::Entity* mBodyEnt) {
	this->mBodyEnt = mBodyEnt;

	this->mBodyEnt->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);
	nomAnimationBasActuel = "IdleBase";
	nomAnimationHautActuel = "IdleTop";

	mTimer = 0;

}

GraphicsAnimation::~GraphicsAnimation() {
	// TODO Auto-generated destructor stub
}

void GraphicsAnimation::loadAnimation()
{
	//{"IdleBase", "IdleTop", "RunBase", "RunTop", "HandsClosed", "HandsRelaxed", "DrawSwords",
	//		"SliceVertical", "SliceHorizontal", "Dance", "JumpStart", "JumpLoop", "JumpEnd"};

	// populate our animation list
	Ogre::AnimationStateIterator iter = mBodyEnt->getAllAnimationStates()->getAnimationStateIterator();
	while (iter.hasMoreElements()) {
		AnimationStructure animationTemp;
		animationTemp.mAnims = iter.peekNextValue();
		animationTemp.mAnims->setLoop(true);
		animationTemp.mAnims->setEnabled(false);
		animationTemp.FadingIn = false;
		animationTemp.FadingOut = false;
		listOfAnimation[iter.peekNextKey()] = animationTemp ;
		iter.moveNext();
	}

	animation = listOfAnimation.find("IdleBase");
	animation->second.mAnims->setEnabled(true);
	animation->second.FadingIn = true;
	animation->second.FadingOut = false;

	animation = listOfAnimation.find("IdleTop");
	animation->second.mAnims->setEnabled(true);
	animation->second.FadingIn = true;
	animation->second.FadingOut = false;

}


void GraphicsAnimation::updateAnimation(double timeSinceLastFrame)
{
	mTimer += timeSinceLastFrame;
	mBodyEnt->getAnimationState(nomAnimationBasActuel)->addTime(timeSinceLastFrame);
	mBodyEnt->getAnimationState(nomAnimationHautActuel)->addTime(timeSinceLastFrame);


	for (animation=listOfAnimation.begin(); animation!=listOfAnimation.end(); ++animation)
	{
		if (animation->second.FadingIn)
		{
			// slowly fade this animation in until it has full weight
			Ogre::Real newWeight = animation->second.mAnims->getWeight() + timeSinceLastFrame * 7.5f;
			animation->second.mAnims->setWeight(Ogre::Math::Clamp<Ogre::Real>(newWeight, 0, 1));
			if (newWeight >= 1)
				animation->second.FadingIn = false;
		}
		else if (animation->second.FadingOut)
		{
			// slowly fade this animation out until it has no weight, and then disable it
			Ogre::Real newWeight = animation->second.mAnims->getWeight() - timeSinceLastFrame * 7.5f;
			animation->second.mAnims->setWeight(Ogre::Math::Clamp<Ogre::Real>(newWeight, 0, 1));
			if (newWeight <= 0)
			{
				animation->second.mAnims->setEnabled(false);
				animation->second.FadingOut = false;
			}
		}
	}
}

void GraphicsAnimation::setAnimationBas(Ogre::String nomAnimation,bool reset)
{
	if(!Ogre::StringUtil::match(nomAnimation,nomAnimationBasActuel,true))
	{
		animation = listOfAnimation.find(nomAnimation);

		if(listOfAnimation.end() != animation)
		{
			animation->second.mAnims->setEnabled(true);
			animation->second.FadingIn = true;
			animation->second.FadingOut = false;

			animation = listOfAnimation.find(nomAnimationBasActuel);
			animation->second.FadingIn = false;
			animation->second.FadingOut = true;
			nomAnimationBasActuel = nomAnimation;
			mTimer = 0;
		}
	}
	if(reset)
	{
		mBodyEnt->getAnimationState(nomAnimationBasActuel)->setTimePosition(0);
	}
}

void GraphicsAnimation::setAnimationHaut(Ogre::String nomAnimation,bool reset)
{
	if(!Ogre::StringUtil::match(nomAnimation,nomAnimationHautActuel,true))
	{
		animation = listOfAnimation.find(nomAnimation);
		if(listOfAnimation.end() != animation)
		{
			animation->second.mAnims->setEnabled(true);
			animation->second.FadingIn = true;
			animation->second.FadingOut = false;

			animation = listOfAnimation.find(nomAnimationHautActuel);
			animation->second.FadingIn = false;
			animation->second.FadingOut = true;

			nomAnimationHautActuel = nomAnimation;
			mTimer = 0;
		}
	}
	if(reset)
	{
		mBodyEnt->getAnimationState(nomAnimationHautActuel)->setTimePosition(0);
	}
}

void GraphicsAnimation::setAnimationSeul(Ogre::String nomAnimation)
{
	animation = listOfAnimation.find(nomAnimation);
	animation->second.mAnims->setEnabled(true);
}

void GraphicsAnimation::unsetAnimationSeul(Ogre::String nomAnimation)
{
	animation = listOfAnimation.find(nomAnimation);
	animation->second.mAnims->setEnabled(false);
}

Ogre::String GraphicsAnimation::getNomAnimationBasActuel()
{
	return this->nomAnimationBasActuel;
}
Ogre::String GraphicsAnimation::getNomAnimationHautActuel()
{
	return this->nomAnimationHautActuel;
}

double GraphicsAnimation::getTime()
{
	return mTimer;
}

} /* namespace Engine */
