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
    m_pRenderWnd = 0;
    m_pRenderSystem = 0;
    m_pSceneMgr = 0;
    graphicsMeteoManager = 0;
    graphicsCamera = GraphicsCamera::getInstance();
    inputManager = InputManager::getInstance();
    sauvegardeParam = false;

    m_pRoot = 0;

    graphicsEntiteManager = new GraphicsEntiteManager();
    graphicsSceneLoader = new GraphicsSceneLoader();
    PhysicsManager::getInstance();
    graphicsMouvementManager = new GraphicsMouvementManager();

    EventManager::getInstance()->addListenneur(this);

}

GraphicsManager::~GraphicsManager() {

    m_pRoot->removeFrameListener(this);
    PhysicsManager::DestroyInstance();
    GraphicsObjetManager::DestroyInstance();
    if (graphicsEntiteManager)
        delete graphicsEntiteManager;
    if (graphicsMeteoManager)
        delete graphicsMeteoManager;
    if (graphicsSceneLoader)
        delete graphicsSceneLoader;
    if (graphicsMouvementManager)
        delete graphicsMouvementManager;
    GraphicsCamera::DestroyInstance();
    InputManager::DestroyInstance();

#ifdef USE_RTSHADER_SYSTEM
    // Finalize the RT Shader System.
    finalizeRTShaderSystem();
#endif // USE_RTSHADER_SYSTEM

    if (m_pRoot)
        delete m_pRoot;
}

void GraphicsManager::setParamettreOgre(Ogre::String key, Ogre::String valeur) {
    if (m_pRenderSystem) {
        m_pRenderSystem->setConfigOption(key, valeur);
    }
}

void GraphicsManager::init(std::string mResourcePath, std::string configFile) {
//Debug name convention
#ifdef _DEBUG
    m_pRoot = new Ogre::Root(mResourcePath + "plugins_d.cfg", mResourcePath + configFile + ".cfg", "");
#else
    m_pRoot = new Ogre::Root(mResourcePath + "plugins.cfg", mResourcePath + configFile + ".cfg",
            "");
#endif
    m_pRoot->addFrameListener(this);

    // D�fini le mode par default OpenGL Rendering
    m_pRenderSystem = m_pRoot->getRenderSystemByName("OpenGL Rendering Subsystem");

    if (!m_pRoot->restoreConfig()) {

        if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) {
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

void GraphicsManager::createWindow() {
	m_pRenderWnd = m_pRoot->initialise(true, "Xsilium");

	if (sauvegardeParam)
		m_pRoot->saveConfig();

	m_pRenderWnd->setActive(true);

	inputManager->initialise(m_pRenderWnd);

	m_pSceneMgr = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");

	graphicsCamera->initCamera(m_pSceneMgr, m_pRenderWnd);
	graphicsMouvementManager->setGraphicsCamera(graphicsCamera);
}

void GraphicsManager::loadRessource(std::string mResourcePath, std::string ressourceFile) {
    Ogre::String secName, typeName, archName;
    Ogre::ConfigFile cf;
    cf.load(mResourcePath + ressourceFile);

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;

#ifdef __APPLE__
            if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative dirs
            archName = Ogre::String(mResourcePath + "/" + archName);
#endif

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName,
                    secName);
        }
    }

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

void GraphicsManager::loadScene(Event* event) {
    graphicsMeteoManager = new GraphicsMeteoManager(m_pSceneMgr, m_pRoot, m_pRenderWnd,
            graphicsCamera->getCamera());
    graphicsMeteoManager->init();

    graphicsSceneLoader->parseDotScene(event->getProperty("NameScene"),
            event->getProperty("NameGroup"), m_pSceneMgr);
    for (unsigned int ij = 0; ij < graphicsSceneLoader->mPGHandles.size(); ij++) {
        graphicsSceneLoader->mPGHandles[ij]->setCamera(graphicsCamera->getCamera());
    }

    graphicsEntiteManager->setSceneManager(m_pSceneMgr);
    GraphicsObjetManager::getInstance()->setSceneManager(m_pSceneMgr);
    PhysicsManager::getInstance()->setRootSceneNode(m_pSceneMgr->getRootSceneNode());

    Ogre::TerrainGroup::TerrainIterator it =
            graphicsSceneLoader->getTerrainGroup()->getTerrainIterator();
    while (it.hasMoreElements()) {
        Ogre::Terrain* terrain = it.getNext()->instance;

        float* terrainHeightData = terrain->getHeightData();
        float * pDataConvert = new float[terrain->getSize() * terrain->getSize()];
        for (int i = 0; i < terrain->getSize(); i++)
            memcpy(pDataConvert + terrain->getSize() * i, // source
            terrainHeightData + terrain->getSize() * (terrain->getSize() - i - 1), // target
            sizeof(float) * (terrain->getSize()) // size
                    );

        float metersBetweenVertices = terrain->getWorldSize() / (terrain->getSize() - 1);

        PhysicsManager::getInstance()->addDynamicTerrain(metersBetweenVertices, terrain->getSize(),
                terrain->getSize(), pDataConvert, terrain->getMinHeight(), terrain->getMaxHeight(),
                terrain->getPosition(), terrain->getWorldSize() / (terrain->getSize() - 1));

    }
    graphicsMouvementManager->activeMouvement();
}

Ogre::RenderWindow* GraphicsManager::getRenderWindow() {
    return this->m_pRenderWnd;
}

void GraphicsManager::processEvent(Event* event) {
    if (event->hasProperty("LoadScene")) {
        loadScene(event);
    }

    graphicsMouvementManager->processEvent(event);
    graphicsCamera->processEvent(event);
    graphicsMeteoManager->processEvent(event);
    graphicsEntiteManager->processEvent(event);
    GraphicsObjetManager::getInstance()->processEvent(event);

}

bool GraphicsManager::frameStarted(const Ogre::FrameEvent& m_FrameEvent) {
    inputManager->capture(m_FrameEvent.timeSinceLastFrame);
    PhysicsManager::getInstance()->update(m_FrameEvent.timeSinceLastFrame);
    return true;
}
bool GraphicsManager::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent) {
    graphicsCamera->frameRenderingQueued(m_FrameEvent);
    if (graphicsEntiteManager)
        graphicsEntiteManager->update(m_FrameEvent.timeSinceLastFrame);
    if (graphicsEntiteManager)
        GraphicsObjetManager::getInstance()->update(m_FrameEvent.timeSinceLastFrame);
    if (graphicsMeteoManager)
        graphicsMeteoManager->update(m_FrameEvent.timeSinceLastFrame);
    graphicsMouvementManager->update(m_FrameEvent.timeSinceLastFrame);

    for (unsigned int ij = 0; ij < graphicsSceneLoader->mPGHandles.size(); ij++) {
        graphicsSceneLoader->mPGHandles[ij]->update();
    }

    return true;
}
bool GraphicsManager::frameEnded(const Ogre::FrameEvent& m_FrameEvent) {
    return true;
}

Ogre::Root* GraphicsManager::getRoot() {
    return this->m_pRoot;
}

} /* namespace Engine */
