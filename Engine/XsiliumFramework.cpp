#include "XsiliumFramework.h"

using namespace Ogre;

XsiliumFramework::XsiliumFramework()
{
	m_pRoot				= 0;
	m_pRenderWnd		= 0;
	m_pLog				= 0;
	inputManager 		= 0;
	keyboardMap 		= 0;
}

XsiliumFramework::~XsiliumFramework()
{
	m_pLog->logMessage("Extinction OGRE...");
	m_pRoot->removeFrameListener(this);
	if(m_pRoot)
		delete m_pRoot;
	if(inputManager)
		delete inputManager;
	if(keyboardMap)
		delete keyboardMap;
	if(m_pLog)
		delete m_pLog;
}

bool XsiliumFramework::initOgre(Ogre::String wndTitle,Ogre::String logName)
{

	inputManager = InputManager::getSingletonPtr();
	keyboardMap = KeyboardMap::getInstance();


#ifdef __APPLE__
	mResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
	mResourcePath = "";
#endif

	keyboardMap->load(mResourcePath + "configKey.xml");
	keyboardMap->saveKeyboardMap();


	Ogre::LogManager* logMgr = new Ogre::LogManager();

	m_pLog = logMgr->createLog(mResourcePath + "OgreLogfile.log", true, true, false);
	m_pLog->setDebugOutputEnabled(true);

	m_pRoot = new Ogre::Root(mResourcePath + "plugins.cfg",mResourcePath + "ogre.cfg",mResourcePath + logName + ".log");


	if (!m_pRoot->restoreConfig())
	{
		if(!m_pRoot->showConfigDialog())
			return false;
	}
	m_pRenderWnd = m_pRoot->initialise(true,wndTitle);

	inputManager->initialise(m_pRenderWnd);
	m_pRenderWnd->addViewport(0);

	m_pRenderWnd->setActive(true);

	m_pRoot->addFrameListener(this);

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
	inputManager->capture();
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
	// Set the shutting down flag and sleep a bit so the displaylink thread can shut itself down
	// Note: It is essential that you yield to the CVDisplayLink thread. Otherwise it will
	// continue to run which will result in either a crash or kernel panic.
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 1000;
	nanosleep(&ts, NULL);

	[NSApp terminate:nil];

#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	[mGestureView release];
#endif
}
