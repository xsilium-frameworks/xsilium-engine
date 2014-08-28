/*
 * \file GraphicsObjetManager.cpp
 *
 *  Created on: \date 27 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsObjetManager.h"

namespace Engine {

GraphicsObjetManager::GraphicsObjetManager() {
	msceneMgr = 0;

}

GraphicsObjetManager::~GraphicsObjetManager() {
	for (objet=listOfObjet.begin() ; objet!=listOfObjet.end() ; ++objet)
	{
		delete (*objet);
	}
}

void GraphicsObjetManager::createObjet(Event * event)
{
	GraphicsObjet * graphicsObjet = new GraphicsObjet();
	graphicsObjet->initObjet(msceneMgr,event->getProperty("NomObjet"), event->getProperty("fileMesh"));

	//if(event->hasProperty("IndependantObjet"))
	//	graphicsObjet->setIndependant(event->getProperty("IndependantObjet"));


	listOfObjet.push_back(graphicsObjet);

}
GraphicsObjet * GraphicsObjetManager::trouverObjet(Ogre::String nom)
{
	for (objet=listOfObjet.begin() ; objet!=listOfObjet.end() ; ++objet)
	{
		if ( nom.compare(0,(*objet)->getNom()->length(),*(*objet)->getNom()) ==0 )
		{
			return (*objet);
		}
	}
	return NULL;
}
void GraphicsObjetManager::deleteObjet(Ogre::String nom)
{
	for (objet=listOfObjet.begin() ; objet!=listOfObjet.end() ; ++objet)
	{
		if ( nom.compare(0,(*objet)->getNom()->length(),*(*objet)->getNom()) ==0 )
		{
			delete (*objet);
		}
	}
}

void GraphicsObjetManager::setSceneManager(Ogre::SceneManager* msceneMgr)
{
	this->msceneMgr = msceneMgr ;
}

void GraphicsObjetManager::update(float time)
{
	for (objet=listOfObjet.begin() ; objet!=listOfObjet.end() ; ++objet)
	{
			(*objet)->update(time);
	}
}

void GraphicsObjetManager::processEvent(Event * event)
{
	if(event->hasProperty("CreateObjet"))
	{
		createObjet(event);
	}
}

} /* namespace Engine */
