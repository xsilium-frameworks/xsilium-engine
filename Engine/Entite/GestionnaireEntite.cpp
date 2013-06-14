/*
 * \file GestionnaireEntite.cpp
 *
 *  Created on: \date 13 juin 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireEntite.h"

GestionnaireEntite::GestionnaireEntite() {
	XsiliumFramework::getInstance()->getRoot()->addFrameListener(this);
}

GestionnaireEntite::~GestionnaireEntite() {
	XsiliumFramework::getInstance()->getRoot()->removeFrameListener(this);
}

Entite * GestionnaireEntite::trouverEntite(std::string nom)
{
	for (entite=listOfEntite.begin() ; entite!=listOfEntite.end() ; ++entite)
	{
		if((*entite)->getNom()->compare(nom))
		{
				return (*entite);
		}

	}
	return NULL;
}


void GestionnaireEntite::ajouterEntite(Entite * entite)
{
	listOfEntite.push_back(entite);
}

bool GestionnaireEntite::frameStarted(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
bool GestionnaireEntite::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
	for (entite=listOfEntite.begin() ; entite!=listOfEntite.end() ; ++entite)
	{
		(*entite)->update(m_FrameEvent.timeSinceLastFrame);
	}
	return true;
}
bool GestionnaireEntite::frameEnded(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
