/*
 * \file Engine.h
 *
 *  Created on: \date 2 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_H_
#define ENGINE_H_

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__
#import <Cocoa/Cocoa.h>
#endif



#include "Singleton/Singleton.h"
#include "Event/Event.h"
#include "EngineListenner.h"
#include <vector>


#include <Ogre.h>
#include <OgreRoot.h>

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE)
#include <OSX/macUtils.h>
#endif


namespace Engine {



/*
 *
 */
class Engine : public Singleton<Engine>
{
	friend class Singleton<Engine>;

public:
	Engine();
	virtual ~Engine();

	void initEngine(Ogre::String configFile, int nbThread);

	void initOgre(Ogre::String configFile);

	void addListenner(EngineListenner* engineListenner);

	void shutdown();

	Ogre::Root* getRoot();
	Ogre::String * getResourcePath();

	void addEvent(Event event);

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

private:

	Ogre::String mResourcePath ;
	Ogre::Root*	m_pRoot;

	std::vector<EngineListenner*> listOfEngineListenner;

};

} /* namespace Engine */

#endif /* ENGINE_H_ */
