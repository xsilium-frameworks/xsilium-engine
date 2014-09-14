/*
 * \file GraphicsObjet.cpp
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsObjet.h"

namespace Engine {

GraphicsObjet::GraphicsObjet() {
	objetEnt = 0;
	objetNode = 0;
	isIndependant = true;

}

GraphicsObjet::~GraphicsObjet() {
	// TODO Auto-generated destructor stub
}

void GraphicsObjet::initObjet(Ogre::SceneManager* sceneMgr,Ogre::String nom,Ogre::String fileMesh)
{
	this->nom = nom;
	objetEnt = sceneMgr->createEntity(nom, fileMesh);
	objetNode = sceneMgr->getRootSceneNode()->createChildSceneNode(nom);
}

Ogre::Entity* GraphicsObjet::getObjet()
{
	return this->objetEnt;
}

Ogre::String * GraphicsObjet::getNom()
{
	return &this->nom;
}

void GraphicsObjet::update(double timeSinceLastFrame)
{

}

void GraphicsObjet::setPosition(Ogre::Vector3 position)
{
	objetNode->setPosition(position);
}

void GraphicsObjet::setIndependant(bool seul)
{
	if ( seul != isIndependant)
	{
		isIndependant = seul;
		if (seul)
			objetNode->detachObject(objetEnt);
		else
			objetNode->attachObject(objetEnt);
	}
}

} /* namespace Engine */
