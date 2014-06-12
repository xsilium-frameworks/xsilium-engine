#include "XsiliumFramework.h"

using namespace Ogre;

XsiliumFramework::XsiliumFramework()
{
	m_pRoot				= 0;
	m_pRenderWnd		= 0;
	m_pLog				= 0;
	inputManager 		= 0;
	keyboardMap 		= 0;
	m_pRenderSystem		= 0;

	sauvegardeParam = false;


#ifdef __APPLE__
	mResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
	mResourcePath = "";
#endif


}

XsiliumFramework::~XsiliumFramework()
{
	m_pLog->logMessage("Extinction OGRE...");
	m_pRoot->removeFrameListener(this);
	if(m_pRoot)
		delete m_pRoot;
	if(inputManager)
		InputManager::DestroyInstance();
	if(keyboardMap)
		KeyboardMap::DestroyInstance();
	if(m_pLog)
		delete m_pLog;
}

void XsiliumFramework::setParamettreOgre(std::string key, std::string valeur)
{
	if(m_pRenderSystem)
	{
		m_pRenderSystem->setConfigOption(key,valeur);
	}
}

bool XsiliumFramework::initOgre(Ogre::String fenetreName,Ogre::String fileName,bool sauvegardeParam)
{
	this->fenetreName = fenetreName;
	this->sauvegardeParam = sauvegardeParam;

	// Creation du systeme de log
	Ogre::LogManager* logMgr = new Ogre::LogManager();

	m_pLog = logMgr->createLog(mResourcePath + "Log" + fileName + ".log", true, true, false);
	m_pLog->setDebugOutputEnabled(true);

	m_pRoot = new Ogre::Root(mResourcePath + "plugins.cfg",mResourcePath + fileName + ".cfg","");
	//m_pRenderSystem = m_pRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	m_pRenderSystem = m_pRoot->getAvailableRenderers().front();
	m_pRoot->setRenderSystem(m_pRenderSystem);
	if(!m_pRoot->restoreConfig())
	{
		// Set defaults per RenderSystem
		m_pRenderSystem->setConfigOption("Video Mode", "1024 x 768");
		m_pRenderSystem->setConfigOption("Colour Depth", "32");
		m_pRenderSystem->setConfigOption("FSAA", "0");
		m_pRenderSystem->setConfigOption("Full Screen", "No");
		m_pRenderSystem->setConfigOption("RTT Preferred Mode", "FBO");
		m_pRenderSystem->setConfigOption("sRGB Gamma Conversion", "No");
		m_pRenderSystem->setConfigOption("Content Scaling Factor", "1.0");
		m_pRenderSystem->setConfigOption("macAPI", "cocoa");
	}

	return true;
}

void XsiliumFramework::createWindow()
{
	m_pRenderWnd = m_pRoot->initialise(true,fenetreName);

	if(sauvegardeParam)
		m_pRoot->saveConfig();

	m_pRenderWnd->addViewport(0);

	m_pRenderWnd->setActive(true);

	m_pRoot->addFrameListener(this);

}

bool XsiliumFramework::initInput()
{
	// Initialisation des inputs
	inputManager = InputManager::getInstance();
	keyboardMap = KeyboardMap::getInstance();

	// Chargement des transposition clavier / action
	keyboardMap->load(mResourcePath + "configKey.xml");

	// initialisation des inputs
	inputManager->initialise(m_pRenderWnd);

	return true;
}

void XsiliumFramework::loadRessource()
{
	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
	cf.load(mResourcePath + "resources.cfg");

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

Ogre::Root* XsiliumFramework::getRoot()
{
	return this->m_pRoot;
}

Ogre::RenderWindow* XsiliumFramework::getRenderWindow()
{
	return this->m_pRenderWnd;
}

Ogre::Log* XsiliumFramework::getLog()
{
	return this->m_pLog;
}

bool XsiliumFramework::frameStarted (const Ogre::FrameEvent &evt)
{
	return true;
}

bool XsiliumFramework::frameRenderingQueued (const Ogre::FrameEvent &evt)
{
	if(inputManager)
		inputManager->capture(evt.timeSinceLastFrame);
	return true;
}

bool XsiliumFramework::frameEnded (const Ogre::FrameEvent &evt)
{
	return true;
}

void XsiliumFramework::shutdown()
{
	XsiliumFramework::getInstance()->getRoot()->queueEndRendering(true);

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
