#ifndef OGRE_FRAMEWORK_H
#define OGRE_FRAMEWORK_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>

#include "InputManager/InputManager.h"

#ifdef __APPLE__
#include "OSX/macUtils.h"
#endif

#include <OgreParticleSystem.h>


#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include "Interface/Interface.h"

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "DotSceneLoader/DotSceneLoader.h"


class XsiliumFramework : public Singleton<XsiliumFramework> {

	friend class Singleton<XsiliumFramework>;

public:
	XsiliumFramework();
	~XsiliumFramework();

	bool initOgre(Ogre::String wndTitle);
	void updateOgre(double timeSinceLastFrame);

	Ogre::Root*					m_pRoot;
	Ogre::RenderWindow*			m_pRenderWnd;
	Ogre::Viewport*				m_pViewport;
	Ogre::Log*					m_pLog;
	Ogre::Timer*				m_pTimer;
	InputManager*				inputManager;

private:
	XsiliumFramework(const XsiliumFramework&);
	XsiliumFramework& operator= (const XsiliumFramework&);
    Ogre::String m_SceneFile;
};

#endif
