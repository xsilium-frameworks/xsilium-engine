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
	charHeight = 0;
	turnSpeed = 0;
	mBodyNode = 0;
	mBodyEnt = 0;

	sceneMgr = 0;

	animation = 0;

	runSpeed = 0;
	countObjet = 0;
	degainer = false;

	eventManager = new EventManager();

}

Entite::~Entite() {
	std::map<int,Objet*>::iterator it;
	for (it=listOfObject.begin(); it!=listOfObject.end(); ++it)
	{
		delete it->second ;
	}
	listOfObject.clear();

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
			processAnimation(event);
		}
		eventManager->removeEvent();
	}


	if(animation->getNomAnimationHautActuel().compare("DrawSwords") == 0)
	{
		if (animation->getTime() >= mBodyEnt->getAnimationState(animation->getNomAnimationHautActuel())->getLength() / 2 && animation->getTime() - timeSinceLastFrame < mBodyEnt->getAnimationState(animation->getNomAnimationHautActuel())->getLength() / 2 )
		{
			std::map<int,Objet*>::iterator it;
			degainer = !degainer;
			it=listOfObject.find(1);
			mBodyEnt->detachObjectFromBone(it->second->getObjet());
			mBodyEnt->attachObjectToBone(degainer ? "Handle.L" : "Sheath.L", it->second->getObjet());
			it=listOfObject.find(2);
			mBodyEnt->detachObjectFromBone(it->second->getObjet());
			mBodyEnt->attachObjectToBone(degainer ? "Handle.R" : "Sheath.R", it->second->getObjet());

			if(degainer)
			{
				animation->unsetAnimationSeul("HandsRelaxed");
				animation->setAnimationSeul("HandsClosed");
			}
			else
			{
				animation->unsetAnimationSeul("HandsClosed");
				animation->setAnimationSeul("HandsRelaxed");
			}

		}

		if (animation->getTime() > mBodyEnt->getAnimationState(animation->getNomAnimationHautActuel())->getLength() )
		{
			if(animation->getNomAnimationBasActuel().compare("IdleBase") == 0 )
			{
				idleAnimation();
			}
			else
			{
				runAnimation();
				mBodyEnt->getAnimationState("RunTop")->setTimePosition(mBodyEnt->getAnimationState(animation->getNomAnimationBasActuel())->getTimePosition());
			}
		}
	}

	animation->updateAnimation(timeSinceLastFrame) ;
}

void Entite::setEvent(Event event)
{
	eventManager->addEvent(event);
}

void Entite::addObjet(const char * nomObjet,const char * fileMesh,const char * emplacement)
{
	Objet * objet = new Objet(sceneMgr,nomObjet,fileMesh);
	countObjet += 1;
	mBodyEnt->attachObjectToBone(emplacement, objet->getObjet());
	listOfObject.insert ( std::pair<int,Objet*>(countObjet,objet) );
}

void Entite::degainerArme()
{

	Event event;
	event.setProperty("Evenement",std::string("Animation"));
	event.setProperty("AnimationHaut",std::string("DrawSwords"));
	event.setProperty("AnimationHautReset",std::string("1"));
	setEvent(event);
}

bool Entite::isDegainerArme()
{
	return this->degainer;
}

void Entite::runAnimation()
{
	Event event;
	event.setProperty("Evenement",std::string("Animation"));
	event.setProperty("AnimationBas",std::string("RunBase"));
	event.setProperty("AnimationHaut",std::string("RunTop"));
	setEvent(event);
}
void Entite::idleAnimation()
{
	Event event;
	event.setProperty("Evenement",std::string("Animation"));
	event.setProperty("AnimationBas",std::string("IdleBase"));
	event.setProperty("AnimationHaut",std::string("IdleTop"));
	setEvent(event);
}


