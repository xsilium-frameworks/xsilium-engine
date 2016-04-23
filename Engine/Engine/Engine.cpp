/*
 * \file Engine.cpp
 *
 *  Created on: \date 2 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#include "Engine.h"

namespace Engine {

Engine::Engine() {
	graphicsManager = GraphicsManager::getInstance();
	guiManager = GuiManager::getInstance();
	logManager = LogManager::getInstance();
	eventManager = EventManager::getInstance();

	eventManager->addListenneur(this);

}

Engine::~Engine() {
	EventManager::DestroyInstance();
	KeyboardManager::DestroyInstance();
	GuiManager::DestroyInstance()  ;
	GraphicsManager::DestroyInstance();
	LogManager::DestroyInstance();
}


void Engine::initEngine(std::string configFile)
{

#ifdef __APPLE__
	mResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
	mResourcePath = "";
#endif

	logManager->initLog(getResourcePath(), "client");

	logManager->setLogMessage("Initialisation de l\'engine", NOTIFICATION);

	graphicsManager->init(getResourcePath(),configFile);
	graphicsManager->createWindow();

// Debug name convention
#ifdef _DEBUG
	graphicsManager->loadRessource(getResourcePath(), "resources_d.cfg");
#else
	graphicsManager->loadRessource(getResourcePath(),"resources.cfg");
#endif

	guiManager->init(graphicsManager->getRoot());

	eventManager->init(graphicsManager->getRoot());

	KeyboardManager::getInstance()->load(getResourcePath(), "configKey.xml");

	GameStateManager::getInstance()->setRoot(graphicsManager->getRoot());
	GameStateManager::getInstance()->setRenderWindow(graphicsManager->getRenderWindow());

}

Ogre::Root* Engine::getRoot()
{
	return this->graphicsManager->getRoot();
}

std::string Engine::getResourcePath()
{
	return this->mResourcePath;
}

Ogre::RenderWindow* Engine::getRenderWindow()
{
	return this->graphicsManager->getRenderWindow();
}

void Engine::processEvent(Event* event)
{
	if(event->hasProperty("ENGINE"))
	{
		if( (event->getProperty("Fonction").compare("QUIT")) == 0 )
		{
			getRoot()->queueEndRendering(true);
		}
	}
}

} /* namespace Engine */
