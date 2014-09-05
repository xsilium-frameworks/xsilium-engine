/*
 * \file GraphicsEntiteManager.cpp
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsEntiteManager.h"

namespace Engine {

GraphicsEntiteManager::GraphicsEntiteManager() {
	msceneMgr = 0;
	graphicsObjetManager = 0;

}

GraphicsEntiteManager::~GraphicsEntiteManager() {

	for (entite=listOfEntite.begin() ; entite!=listOfEntite.end() ; ++entite)
	{
		delete (*entite);
	}
}

void GraphicsEntiteManager::setSceneManager(Ogre::SceneManager* msceneMgr)
{
	this->msceneMgr = msceneMgr ;
}

void GraphicsEntiteManager::setObjetManager(GraphicsObjetManager * graphicsObjetManager)
{
	this->graphicsObjetManager = graphicsObjetManager;
}

void GraphicsEntiteManager::createEntite(Event * event)
{
	GraphicsEntite * graphicsEntite = new GraphicsEntite();

	if(event->hasProperty("CharHeight"))
	{
		graphicsEntite->setCharHeight( atoi(event->getProperty("CharHeight").c_str() ) );
	}

	if(event->hasProperty("RunSpeed"))
	{
		graphicsEntite->setRunSpeed( atoi(event->getProperty("RunSpeed").c_str() ) );
	}

	if(event->hasProperty("TurnSpeed"))
	{
		graphicsEntite->setTurnSpeed( atof(event->getProperty("TurnSpeed").c_str()) );
	}

	graphicsEntite->initEntite(msceneMgr , event->getProperty("NomEntite"), event->getProperty("fileMesh") );
/**
	if(event->hasProperty("PositionX"))
	{
		graphicsEntite->setPosition(Ogre::Vector3( atoi(event->getProperty("PositionX").c_str()),atoi(event->getProperty("PositionY").c_str()),atoi(event->getProperty("PositionZ").c_str()))) ;
	}
*/

	listOfEntite.push_back(graphicsEntite);
}



GraphicsEntite * GraphicsEntiteManager::trouverEntite(Ogre::String nom)
{
	for (entite=listOfEntite.begin() ; entite!=listOfEntite.end() ; ++entite)
	{
		if ( nom.compare(0,(*entite)->getNom()->length(),*(*entite)->getNom()) ==0 )
		{
			return (*entite);
		}
	}
	return NULL;
}

void GraphicsEntiteManager::deleteEntite(Ogre::String nom)
{
	for (entite=listOfEntite.begin() ; entite!=listOfEntite.end() ; ++entite)
	{
		if ( nom.compare(0,(*entite)->getNom()->length(),*(*entite)->getNom()) ==0 )
		{
			delete (*entite);
		}
	}
}

void GraphicsEntiteManager::assigneObjet(Event * event)
{
	trouverEntite(event->getProperty("NomEntite"))->addEquipement( graphicsObjetManager->trouverObjet( event->getProperty("NomObjet"))->getObjet(), event->getProperty("Emplacement") );
}

void GraphicsEntiteManager::processEvent(Event * event)
{
	if(event->hasProperty("CreateEntite"))
	{
		createEntite(event);
	}
	if(event->hasProperty("AssigneObjet"))
	{
		assigneObjet(event);
	}
}

void GraphicsEntiteManager::update(float time)
{
	for (entite=listOfEntite.begin() ; entite!=listOfEntite.end() ; ++entite)
	{
		(*entite)->update(time);
	}
}

} /* namespace Engine */
