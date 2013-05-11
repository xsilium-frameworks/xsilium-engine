#ifndef OGRE_FRAMEWORK_H
#define OGRE_FRAMEWORK_H

#include <OgreLogManager.h>

#include "InputManager/InputManager.h"
#include "KeyboardMap/KeyboardMap.h"

#ifdef __APPLE__
#include "OSX/macUtils.h"
#endif


#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <SdkTrays.h>

#include "DotSceneLoader/DotSceneLoader.h"


class XsiliumFramework : public xsilium::Singleton<XsiliumFramework> {

	friend class xsilium::Singleton<XsiliumFramework>;

public:
	XsiliumFramework();
	~XsiliumFramework();

	bool initOgre(Ogre::String wndTitle,Ogre::String logName);

	void loadRessource();

	Ogre::Root* getRoot();
	Ogre::RenderWindow* getRenderWindow();
	Ogre::Log* getLog();
	Ogre::Timer* getTimer();

private:
	XsiliumFramework(const XsiliumFramework&);
	XsiliumFramework& operator= (const XsiliumFramework&);
	Ogre::String m_SceneFile;

	std::string mResourcePath ;

	Ogre::Root*					m_pRoot;
	Ogre::RenderWindow*			m_pRenderWnd;
	Ogre::Log*					m_pLog;
	Ogre::Timer*				m_pTimer;
	InputManager*				inputManager;
	KeyboardMap * keyboardMap;

};

#endif
