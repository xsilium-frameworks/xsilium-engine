/*
 * \file GraphicsAnimation.h
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSANIMATION_H_
#define GRAPHICSANIMATION_H_

#include <Ogre.h>
#include <map>

namespace Engine {

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

/*
 *
 */
class GraphicsAnimation {
public:
	GraphicsAnimation(Ogre::Entity* mBodyEnt);
	virtual ~GraphicsAnimation();

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

} /* namespace Engine */

#endif /* GRAPHICSANIMATION_H_ */
