/*
 * \file Entite.cpp
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Entite.h"

Entite::Entite() {
	vieEntite = 0;
	nom = 0;
	//charHeight = 0;
	//turnSpeed = 0;
	mBodyNode = 0;
	mBodyEnt = 0;

	sceneMgr = 0;

	eventManager = new EventManager();

}

Entite::~Entite() {
	delete nom;
	delete eventManager;
}

void Entite::setVieEntite(int Vie)
{
	this->vieEntite = Vie;
}
int Entite::getVieEntite()
{
	return this->vieEntite;
}

void Entite::setNom(const char * nom)
{
	this->nom = new std::string(nom);
}

std::string * Entite::getNom()
{
	return this->nom ;
}

Ogre::SceneNode* Entite::getBody()
{
	return this->mBodyNode;
}

double Entite::getTurnSpeed()
{
	return this->turnSpeed;
}

int Entite::getRunSpeed()
{
	return this->runSpeed ;
}

void Entite::update(double timeSinceLastFrame)
{
	Event * event = eventManager->getEvent();

	if(event != NULL)
	{
		if(event->getProperty("Evenement").compare("Animation") == 0 )
		{
			animation->setAnimationBas(event->getProperty("AnimationBas").c_str());
			animation->setAnimationHaut(event->getProperty("AnimationHaut").c_str());
		}
		eventManager->removeEvent();
	}

	animation->updateAnimation(timeSinceLastFrame) ;
}

void Entite::setEvent(Event event)
{
	eventManager->addEvent(event);
}
