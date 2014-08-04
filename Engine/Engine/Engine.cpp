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


void Engine::initEngine(Ogre::String configFile)
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

bool Engine::frameStarted (const Ogre::FrameEvent &evt)
{
	return true;
}

bool Engine::frameRenderingQueued (const Ogre::FrameEvent &evt)
{
	std::vector<EngineListenner*>::iterator it;

	Event * event = getEvent();

	for (it=listOfEngineListenner.begin(); it<listOfEngineListenner.end(); it++)
	{
		(*it)->processEvent(event);
	}
	removeEvent();

	return true;
}

bool Engine::frameEnded (const Ogre::FrameEvent &evt)
{
	return true;
}

void Engine::shutdown()
{
	m_pRoot->queueEndRendering(true);

#ifdef USE_RTSHADER_SYSTEM
	// Finalize the RT Shader System.
	finalizeRTShaderSystem();
#endif // USE_RTSHADER_SYSTEM


#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__

	[NSApp terminate:nil];

#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	[mGestureView release];
#endif
}

} /* namespace Engine */
