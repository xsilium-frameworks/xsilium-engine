/*
 * \file Animation.h
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <Ogre.h>
#include <map>

/*
 *
 */

/*! \struct AnimationStructure
 * \brief Structure contenant toutes les information de l'animation
 *
 *  La classe gere la lecture d'une liste de morceaux
 */


struct AnimationStructure
{
	Ogre::AnimationState * mAnims ; /** Objet de l'animation */
	bool FadingIn; /** flag debut d'activation */
	bool FadingOut; /** flag fin d'activation */
};

/*! \class Animation
 * \brief class qui gere les animations
 *
 *  La classe gere les animations des differentes entités
 */

class Animation {
public:
	Animation(Ogre::Entity* mBodyEnt);
	virtual ~Animation();

	void loadAnimation();

	void updateAnimation(double timeSinceLastFrame);

	void setAnimationBas(Ogre::String nomAnimation,bool reset = false);
	void setAnimationHaut(Ogre::String nomAnimation,bool reset = false);

	void setAnimationSeul(Ogre::String nomAnimation);
	void unsetAnimationSeul(Ogre::String nomAnimation);

	Ogre::String getNomAnimationBasActuel();
	Ogre::String getNomAnimationHautActuel();

	double getTime();


private:

	std::map<Ogre::String,AnimationStructure> listOfAnimation;
	std::map<Ogre::String,AnimationStructure>::iterator animation;


	Ogre::Entity* mBodyEnt;

	Ogre::String nomAnimationBasActuel;
	Ogre::String nomAnimationHautActuel;

	double mTimer;

};

#endif /* ANIMATION_H_ */
