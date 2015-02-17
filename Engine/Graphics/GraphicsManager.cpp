/*
 * \file GraphicsManager.cpp
 *
 *  Created on: \date 4 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsManager.h"

namespace Engine {

GraphicsManager::GraphicsManager() {
	m_pRenderWnd		= 0;
	m_pRenderSystem		= 0;
	m_pSceneMgr         = 0;
	m_pCamera			= 0;
	graphicsSky = 0;
	graphicsWater = 0;
	graphicsCamera = GraphicsCamera::getInstance();
	inputManager = InputManager::getInstance();
	sauvegardeParam = false;


	m_pRoot = Engine::getInstance()->getRoot();

	Engine::getInstance()->addListenner(this);

	Engine::getInstance()->getRoot()->addFrameListener(this);

	graphicsEntiteManager = new GraphicsEntiteManager();
	graphicsSceneLoader = new GraphicsSceneLoader();
	PhysicsManager::getInstance();
	graphicsMouvementManager = 0;



}

GraphicsManager::~GraphicsManager() {

	Engine::getInstance()->getRoot()->removeFrameListener(this);
	PhysicsManager::DestroyInstance();
	if(graphicsWater)
		delete graphicsWater;
	if(graphicsSky)
		delete graphicsSky;
	GraphicsObjetManager::DestroyInstance();
	if(graphicsEntiteManager)
		delete graphicsEntiteManager;
	if(graphicsSceneLoader)
		delete graphicsSceneLoader;
	if(graphicsMouvementManager)
		delete graphicsMouvementManager ;
	GraphicsCamera::DestroyInstance();
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
	// D�fini le mode par default OpenGL Rendering
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
		m_pRenderSystem->setConfigOption("Video Mode", "1024 x 768");
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

	m_pRenderWnd->getViewport(0)->setBackgroundColour(Ogre::ColourValue(0,0,0));

	inputManager->initialise(m_pRenderWnd);

	m_pSceneMgr = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
	m_pCamera = m_pSceneMgr->createCamera("CamPrincipal");
	graphicsCamera->setCamera(m_pCamera);
	m_pRenderWnd->getViewport(0)->setCamera(m_pCamera);
	graphicsEntiteManager->setSceneManager(m_pSceneMgr);
	GraphicsObjetManager::getInstance()->setSceneManager(m_pSceneMgr);
	graphicsWater = new GraphicsWater(m_pSceneMgr, m_pRoot, m_pRenderWnd);
	PhysicsManager::getInstance()->setRootSceneNode(m_pSceneMgr->getRootSceneNode());

	graphicsSky = new GraphicsSky(m_pSceneMgr, m_pRoot, m_pRenderWnd);

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
	m_pCamera->setNearClipDistance(5);
    graphicsMouvementManager = new GraphicsMouvementManager();
	graphicsMouvementManager->setGraphicsCamera(graphicsCamera);


	graphicsSceneLoader->parseDotScene( event->getProperty("NameScene"),event->getProperty("NameGroup"),m_pSceneMgr);

	for(unsigned int ij = 0;ij < graphicsSceneLoader->mPGHandles.size();ij++)
	{
		graphicsSceneLoader->mPGHandles[ij]->setCamera(m_pCamera);
	}


	Ogre::TerrainGroup::TerrainIterator it = graphicsSceneLoader->getTerrainGroup()->getTerrainIterator();
	while(it.hasMoreElements())
	{
		Ogre::Terrain* terrain = it.getNext()->instance;

		float* terrainHeightData = terrain->getHeightData();
		float * pDataConvert= new float[terrain->getSize() *terrain->getSize()];
		for(int i=0;i<terrain->getSize();i++)
			memcpy(
					pDataConvert+terrain->getSize() * i, // source
					terrainHeightData + terrain->getSize() * (terrain->getSize()-i-1), // target
					sizeof(float)*(terrain->getSize()) // size
			);


		float metersBetweenVertices = terrain->getWorldSize()/(terrain->getSize()-1);

		PhysicsManager::getInstance()->addDynamicTerrain(
				metersBetweenVertices,
				terrain->getSize(),
				terrain->getSize(),
				pDataConvert,
				terrain->getMinHeight(),
				terrain->getMaxHeight(),
				terrain->getPosition(),
				terrain->getWorldSize()/(terrain->getSize()-1) );

	}


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
	if(event->hasProperty("Objet"))
	{
		GraphicsObjetManager::getInstance()->processEvent(event);
	}
	if(event->hasProperty("LoadScene"))
	{
		loadScene(event);
	}
	if(event->hasProperty("Water"))
	{
		if(event->hasProperty("InitWater"))
		{
			graphicsWater->initHydrax();
			graphicsWater->addDepthTechnique(graphicsSceneLoader->getMaterialNames());
			if(graphicsSky->getSkyX())
				graphicsWater->addRttListener(new GraphicsHydraxRttListener(graphicsSky->getSkyX(),graphicsWater->getHydraX()));
		}
	}
	if(event->hasProperty("Sky"))
	{
		if(event->hasProperty("InitSky"))
		{
			graphicsSky->initSkyX();
			if(graphicsWater->getHydraX())
				graphicsWater->addRttListener(new GraphicsHydraxRttListener(graphicsSky->getSkyX(),graphicsWater->getHydraX()));
		}
	}
    if(graphicsMouvementManager)
        graphicsMouvementManager->processEvent(event);

}

bool GraphicsManager::frameStarted(const Ogre::FrameEvent& m_FrameEvent)
{
	inputManager->capture(m_FrameEvent.timeSinceLastFrame);
	PhysicsManager::getInstance()->update(m_FrameEvent.timeSinceLastFrame);
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


	graphicsCamera->frameRenderingQueued(m_FrameEvent);
	graphicsEntiteManager->update(m_FrameEvent.timeSinceLastFrame);
	GraphicsObjetManager::getInstance()->update(m_FrameEvent.timeSinceLastFrame);
	graphicsWater->update(m_FrameEvent.timeSinceLastFrame);
	graphicsSky->update(m_FrameEvent.timeSinceLastFrame);


	for(unsigned int ij = 0;ij < graphicsSceneLoader->mPGHandles.size();ij++)
	{
		graphicsSceneLoader->mPGHandles[ij]->update();
	}

	printf("FPS %f \n",m_pRenderWnd->getStatistics().lastFPS);

	return true;
}
bool GraphicsManager::frameEnded(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}

void GraphicsManager::exit()
{
#ifdef USE_RTSHADER_SYSTEM
	// Finalize the RT Shader System.
	finalizeRTShaderSystem();
#endif // USE_RTSHADER_SYSTEM
}



} /* namespace Engine */
