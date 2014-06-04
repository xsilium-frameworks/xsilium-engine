#ifndef OGRE_FRAMEWORK_H
#define OGRE_FRAMEWORK_H

#include <OgreLogManager.h>

#include "InputManager/InputManager.h"
#include "KeyboardMap/KeyboardMap.h"

#ifdef __APPLE__
#include "OSX/macUtils.h"
#endif

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__
#import <Cocoa/Cocoa.h>
#endif

#include <Ogre.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreOverlaySystem.h>



class XsiliumFramework : public xsilium::Singleton<XsiliumFramework> , public Ogre::FrameListener {

	friend class xsilium::Singleton<XsiliumFramework>;

public:
	XsiliumFramework();
	~XsiliumFramework();

	bool initOgre(Ogre::String programme);
	bool initInput();

	void setParamettreOgre(std::string key, std::string valeur);
	void loadParametre();
	void setSauvegardeParam(bool sauvegardeParam);


	void loadRessource();

	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);

	void shutdown();

	Ogre::Root* getRoot();
	Ogre::RenderWindow* getRenderWindow();
	Ogre::Log* getLog();
	Ogre::RenderTarget* getRenderTarget();

private:
	XsiliumFramework(const XsiliumFramework&);
	XsiliumFramework& operator= (const XsiliumFramework&);
	Ogre::String m_SceneFile;

	std::string mResourcePath ;

	Ogre::Root*					m_pRoot;
	Ogre::RenderWindow*			m_pRenderWnd;
	Ogre::RenderTarget* 		m_pRenderTarget;
	Ogre::Log*					m_pLog;
	InputManager*				inputManager;
	KeyboardMap * keyboardMap;

	Ogre::NameValuePairList misc;
	bool sauvegardeParam;
	int width;
	int height;

};

#endif
