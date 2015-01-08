/*
 * \file GraphicsMouvementManager.cpp
 *
 *  Created on: \date 8 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsMouvementManager.h"

namespace Engine {

GraphicsMouvementManager::GraphicsMouvementManager() {
	graphicsCamera = 0;
	direction = Ogre::Vector3::ZERO ;
}

GraphicsMouvementManager::~GraphicsMouvementManager() {
	InputManager::getInstance()->removeMouseListener(this);
}



void GraphicsMouvementManager::setGraphicsCamera(GraphicsCamera * graphicsCamera)
{
	this->graphicsCamera = graphicsCamera;
	InputManager::getInstance()->addMouseListener(this,"MouvementManager");
}

void GraphicsMouvementManager::processEvent(Event * event)
{
	if(event->hasProperty("Keyboard"))
	{
		if( (event->getProperty("Fonction").compare("AVANCER")) == 0 )
		{
			if( atoi(event->getProperty("Action").c_str()) == 1 )
			{
				direction.x = 1;
			}
			else
			{
				direction.x = 0;
			}
		}

		if( (event->getProperty("Fonction").compare("DROITE")) == 0 )
		{
			if( atoi(event->getProperty("Action").c_str()) == 1 )
			{
				direction.z = 1;
			}
			else
			{
				direction.z = 0;
			}
		}


		if( (event->getProperty("Fonction").compare("GAUCHE")) == 0 )
		{
			if( atoi(event->getProperty("Action").c_str()) == 1 )
			{
				direction.z = -1;
			}
			else
			{
				direction.z = 0;
			}
		}

		if( (event->getProperty("Fonction").compare("RECULER")) == 0 )
		{
			if( atoi(event->getProperty("Action").c_str()) == 1 )
			{
				direction.x = -1;
			}
			else
			{
				direction.x = 0;
			}
		}

		graphicsCamera->setDirection(direction);

	}

}

bool GraphicsMouvementManager::mouseMoved(const OIS::MouseEvent &e)
{
	if(graphicsCamera)
		graphicsCamera->injectMouseMove(e);

	return true;
}
bool GraphicsMouvementManager::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{

}
bool GraphicsMouvementManager::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{

}


} /* namespace Engine */
