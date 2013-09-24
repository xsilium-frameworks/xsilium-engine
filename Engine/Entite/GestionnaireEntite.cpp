/*
 * \file GestionnaireEntite.cpp
 *
 *  Created on: \date 13 juin 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireEntite.h"

GestionnaireEntite::GestionnaireEntite() {
	networkManager = NetworkManager::getInstance();
	XsiliumFramework::getInstance()->getRoot()->addFrameListener(this);
//	networkManager->addNetworkListener(this,"GestionnaireEntite");
}

GestionnaireEntite::~GestionnaireEntite() {
	XsiliumFramework::getInstance()->getRoot()->removeFrameListener(this);
//	networkManager->removeNetworkListener("GestionnaireEntite");
	for (entite=listOfEntite.begin() ; entite!=listOfEntite.end() ; ++entite)
	{
				delete (*entite);
	}
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


void GestionnaireEntite::updateNetwork(int event ,ENetEvent * packet)
{
	switch(event)
		{
		case ENET_EVENT_TYPE_RECEIVE:
		{
		}
			break;
		default:
			break;
		}
}
