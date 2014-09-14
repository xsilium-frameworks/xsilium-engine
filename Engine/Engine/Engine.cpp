/*
 * \file Engine.cpp
 *
 *  Created on: \date 2 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "Engine.h"

namespace Engine {

Engine::Engine() {
	m_pRoot = 0;

}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

void Engine::initOgre(Ogre::String configFile)
{
	m_pRoot = new Ogre::Root(mResourcePath + "plugins.cfg",mResourcePath + configFile + ".cfg","");
}


void Engine::initEngine(Ogre::String configFile, int nbThread)
{

#ifdef __APPLE__
	mResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
	mResourcePath = "";
#endif

	initOgre(configFile);

}

Ogre::Root* Engine::getRoot()
{
	return this->m_pRoot;
}

Ogre::String * Engine::getResourcePath()
{
	return &this->mResourcePath;
}

void Engine::addListenner(EngineListenner * engineListenner)
{
	listOfEngineListenner.push_back(engineListenner);
}

void Engine::addEvent(Event event)
{
	std::vector<EngineListenner*>::iterator it;
	for (it=listOfEngineListenner.begin(); it<listOfEngineListenner.end(); ++it)
	{
		(*it)->addEvent(event);
	}
}

void Engine::stopEngine()
{
	m_pRoot->queueEndRendering(true);

	std::vector<EngineListenner*>::iterator it;
	for (it=listOfEngineListenner.begin(); it<listOfEngineListenner.end(); ++it)
	{
		(*it)->exit();
	}


#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__

	[NSApp terminate:nil];

#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	[mGestureView release];
#endif
}

} /* namespace Engine */
