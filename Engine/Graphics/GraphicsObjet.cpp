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

}

GraphicsObjet::~GraphicsObjet() {
	// TODO Auto-generated destructor stub
}

void GraphicsObjet::initObjet(Ogre::SceneManager* sceneMgr,Ogre::String nom,Ogre::String fileMesh)
{
	this->nom = nom;
	objetEnt = sceneMgr->createEntity(nom, fileMesh);
}

Ogre::Entity* GraphicsObjet::getObjet()
{
	return this->objetEnt;
}

void GraphicsObjet::update(double timeSinceLastFrame)
{

}

} /* namespace Engine */
