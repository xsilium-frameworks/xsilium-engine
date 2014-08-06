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


	listOfEntite.push_back(graphicsEntite);
}

void GraphicsEntiteManager::processEvent(Event * event)
{

}

void GraphicsEntiteManager::update(float time)
{
	for (entite=listOfEntite.begin() ; entite!=listOfEntite.end() ; ++entite)
		{
					(*entite)->update(time);
		}
}

} /* namespace Engine */
