/*
 * \file Animation.cpp
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Animation.h"

Animation::Animation(Ogre::Entity* mBodyEnt) {
	this->mBodyEnt = mBodyEnt;

	this->mBodyEnt->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);
	nomAnimationBasActuel = "IdleBase";
	nomAnimationHautActuel = "IdleTop";


}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

void Animation::loadAnimation()
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


void Animation::updateAnimation(double timeSinceLastFrame)
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

void Animation::setAnimationBas(Ogre::String nomAnimation,bool reset)
{
	if(!Ogre::StringUtil::match(nomAnimation,nomAnimationBasActuel,true))
	{
		animation = listOfAnimation.find(nomAnimationBasActuel);
		animation->second.FadingIn = false;
		animation->second.FadingOut = true;

		animation = listOfAnimation.find(nomAnimation);
		if(listOfAnimation.end() != animation)
		{
			animation->second.mAnims->setEnabled(true);
			animation->second.FadingIn = true;
			animation->second.FadingOut = false;
			nomAnimationBasActuel = nomAnimation;
			mTimer = 0;
		}
	}
	if(reset)
	{
		mBodyEnt->getAnimationState(nomAnimationBasActuel)->setTimePosition(0);
	}
}

void Animation::setAnimationHaut(Ogre::String nomAnimation,bool reset)
{
	if(!Ogre::StringUtil::match(nomAnimation,nomAnimationHautActuel,true))
	{
		animation = listOfAnimation.find(nomAnimationHautActuel);
		animation->second.FadingIn = false;
		animation->second.FadingOut = true;

		animation = listOfAnimation.find(nomAnimation);
		if(listOfAnimation.end() != animation)
		{
			animation->second.mAnims->setEnabled(true);
			animation->second.FadingIn = true;
			animation->second.FadingOut = false;
			nomAnimationHautActuel = nomAnimation;
			mTimer = 0;
		}
	}
	if(reset)
	{
		mBodyEnt->getAnimationState(nomAnimationHautActuel)->setTimePosition(0);
	}
}

void Animation::setAnimationSeul(Ogre::String nomAnimation)
{
	animation = listOfAnimation.find(nomAnimation);
	animation->second.mAnims->setEnabled(true);
}

void Animation::unsetAnimationSeul(Ogre::String nomAnimation)
{
	animation = listOfAnimation.find(nomAnimation);
	animation->second.mAnims->setEnabled(false);
}

Ogre::String Animation::getNomAnimationBasActuel()
{
	return this->nomAnimationBasActuel;
}
Ogre::String Animation::getNomAnimationHautActuel()
{
	return this->nomAnimationHautActuel;
}

double Animation::getTime()
{
	return mTimer;
}
