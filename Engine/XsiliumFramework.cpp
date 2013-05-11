#include "XsiliumFramework.h"

using namespace Ogre;

XsiliumFramework::XsiliumFramework()
{
	m_pRoot				= 0;
	m_pRenderWnd		= 0;
	m_pLog				= 0;
	m_pTimer			= 0;
	inputManager 		= 0;
	keyboardMap 		= 0;
}

XsiliumFramework::~XsiliumFramework()
{
	m_pLog->logMessage("Extinction OGRE...");
	if(m_pRoot)			delete m_pRoot;
	if(inputManager) delete inputManager;
	if(keyboardMap) delete keyboardMap;
	if(m_pLog) delete m_pLog;
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

	m_pLog = Ogre::LogManager::getSingleton().createLog(mResourcePath + "OgreLogfile.log", true, true, false);
	m_pLog->setDebugOutputEnabled(true);

	m_pRoot = new Ogre::Root(mResourcePath + "plugins.cfg",mResourcePath + "ogre.cfg",logName + ".log");


	if (!m_pRoot->restoreConfig())
	{
		if(!m_pRoot->showConfigDialog())
			return false;
	}
	m_pRenderWnd = m_pRoot->initialise(true, wndTitle);

	inputManager->initialise(m_pRenderWnd);
	m_pRenderWnd->addViewport(0);

	m_pTimer = new Ogre::Timer();
	m_pTimer->reset();

	m_pRenderWnd->setActive(true);

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

Ogre::Timer* XsiliumFramework::getTimer()
{
	return this->m_pTimer;
}
