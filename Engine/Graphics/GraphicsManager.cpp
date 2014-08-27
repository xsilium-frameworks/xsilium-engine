/*
 * \file GraphicsManager.cpp
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsManager.h"

namespace Engine {

GraphicsManager::GraphicsManager() {
	m_pRenderWnd		= 0;
	m_pRenderSystem		= 0;
	m_pSceneMgr         = 0;
	graphicsMeteoManager = 0;
	graphicsCamera = new GraphicsCamera();
	inputManager = InputManager::getInstance();
	sauvegardeParam = false;


	m_pRoot = Engine::getInstance()->getRoot();

	Engine::getInstance()->addListenner(this);

	Engine::getInstance()->getRoot()->addFrameListener(this);

	graphicsEntiteManager = new GraphicsEntiteManager();
	graphicsSceneLoader = new GraphicsSceneLoader();


}

GraphicsManager::~GraphicsManager() {

	Engine::getInstance()->getRoot()->removeFrameListener(this);
	delete graphicsMeteoManager;
	delete graphicsEntiteManager;
	delete graphicsSceneLoader;
	delete graphicsCamera;
	InputManager::DestroyInstance();

}


void GraphicsManager::setParamettreOgre(Ogre::String key, Ogre::String valeur)
{
	if(m_pRenderSystem)
	{
		m_pRenderSystem->setConfigOption(key,valeur);
	}
}

void GraphicsManager::initOgre()
{
	// DŽfini le mode par default OpenGL Rendering
	m_pRenderSystem = m_pRoot->getRenderSystemByName("OpenGL Rendering Subsystem");

	if(!m_pRoot->restoreConfig())
	{

		if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE )
		{
			m_pRenderSystem->setConfigOption("RTT Preferred Mode", "FBO");
			m_pRenderSystem->setConfigOption("Content Scaling Factor", "1.0");
			m_pRenderSystem->setConfigOption("macAPI", "cocoa");
			m_pRenderSystem->setConfigOption("Colour Depth", "32");
		}

		// Set defaults per RenderSystem
		m_pRenderSystem->setConfigOption("Full Screen", "No");
		m_pRenderSystem->setConfigOption("VSync", "No");
		m_pRenderSystem->setConfigOption("Video Mode", "800 x 600");
		m_pRenderSystem->setConfigOption("FSAA", "0");
		m_pRenderSystem->setConfigOption("sRGB Gamma Conversion", "No");

		m_pRoot->setRenderSystem(m_pRenderSystem);
	}
}

void GraphicsManager::createWindow()
{
	m_pRenderWnd = m_pRoot->initialise(true,"Xsilium");

	if(sauvegardeParam)
		m_pRoot->saveConfig();

	m_pRenderWnd->addViewport(0);

	m_pRenderWnd->setActive(true);

	inputManager->initialise(m_pRenderWnd);

	inputManager->addKeyListener(this,"GraphicsKey");
	inputManager->addMouseListener(this,"GraphicsMouse");

	m_pSceneMgr = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
	graphicsEntiteManager->setSceneManager(m_pSceneMgr);
	graphicsMeteoManager = new GraphicsMeteoManager(m_pSceneMgr,m_pRoot,m_pRenderWnd);

}

void GraphicsManager::loadRessource()
{
	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
	cf.load( *(Engine::getInstance()->getResourcePath()) + "resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;

#ifdef __APPLE__
			if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative dirs
				archName = Ogre::String(Ogre::macBundlePath() + "/" + archName);
#endif

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

void GraphicsManager::loadScene(Event* event)
{

	Ogre::Camera* m_pCamera = m_pSceneMgr->createCamera("CamPricipal");
	m_pCamera->setNearClipDistance(0.1);
	m_pRenderWnd->getViewport(0)->setCamera(m_pCamera);
	graphicsCamera->setCamera(m_pCamera);
	graphicsCamera->setStyle(CS_FREELOOK);



	graphicsSceneLoader->parseDotScene( event->getProperty("NameScene"),event->getProperty("NameGroup"),m_pSceneMgr);

	for(unsigned int ij = 0;ij < graphicsSceneLoader->mPGHandles.size();ij++)
	{
		graphicsSceneLoader->mPGHandles[ij]->setCamera(m_pCamera);
	}

	graphicsMeteoManager->createMeteo();
    graphicsMeteoManager->beafourt(0);
    graphicsMeteoManager->addDepthTechnique(graphicsSceneLoader->getMaterialNames());

}


Ogre::RenderWindow* GraphicsManager::getRenderWindow()
{
	return this->m_pRenderWnd;
}

void GraphicsManager::processEvent(Event* event)
{
	if(event->hasProperty("Entite"))
	{
		graphicsEntiteManager->processEvent(event);
	}
	if(event->hasProperty("LoadScene"))
	{
		loadScene(event);
	}

}

bool GraphicsManager::frameStarted(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
bool GraphicsManager::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{


	if(!isEmpty())
	{
		Event* event = getEvent();
		processEvent(event);
		deleteEvent();
	}

	for(unsigned int ij = 0;ij < graphicsSceneLoader->mPGHandles.size();ij++)
	{
		graphicsSceneLoader->mPGHandles[ij]->update();
	}

	inputManager->capture(m_FrameEvent.timeSinceLastFrame);
	graphicsCamera->frameRenderingQueued(m_FrameEvent);
	graphicsEntiteManager->update(m_FrameEvent.timeSinceLastFrame);
	graphicsMeteoManager->update(m_FrameEvent.timeSinceLastFrame);


	return true;
}
bool GraphicsManager::frameEnded(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}

bool GraphicsManager::keyPressed( const OIS::KeyEvent &e )
{
	graphicsCamera->injectKeyDown(e);
	return true;
}
bool GraphicsManager::keyReleased( const OIS::KeyEvent &e )
{
	graphicsCamera->injectKeyUp(e);
	return true;
}

bool GraphicsManager::mouseMoved( const OIS::MouseEvent &e )
{
	graphicsCamera->injectMouseMove(e);
	return true;
}
bool GraphicsManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	graphicsCamera->injectMouseDown(e,id);
	return true;
}
bool GraphicsManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	graphicsCamera->injectMouseUp(e,id);
	return true;
}

void GraphicsManager::shutdown()
{
#ifdef USE_RTSHADER_SYSTEM
	// Finalize the RT Shader System.
	finalizeRTShaderSystem();
#endif // USE_RTSHADER_SYSTEM
}



} /* namespace Engine */
