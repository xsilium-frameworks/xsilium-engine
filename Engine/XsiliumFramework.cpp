#include "XsiliumFramework.h"

using namespace Ogre;

XsiliumFramework::XsiliumFramework()
{
    m_pRoot				= 0;
    m_pRenderWnd		= 0;
    m_pViewport			= 0;
    m_pLog				= 0;
    m_pTimer			= 0;
    inputManager 		= 0;
}

XsiliumFramework::~XsiliumFramework()
{
    XsiliumFramework::getInstance()->m_pLog->logMessage("Extinction OGRE...");
    if(m_pRoot)			delete m_pRoot;
    if(inputManager) delete inputManager;
}

bool XsiliumFramework::initOgre(Ogre::String wndTitle)
{
    std::string mResourcePath ;

    inputManager = InputManager::getSingletonPtr();

#ifdef __APPLE__
    mResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
    mResourcePath = "";
#endif
    
    
    Ogre::LogManager* logMgr = new Ogre::LogManager();
    
    m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
    m_pLog->setDebugOutputEnabled(true);
    
    m_pRoot = new Ogre::Root(mResourcePath + "plugins.cfg",mResourcePath + "ogre.cfg","ogre.log");
    
    
    if (!m_pRoot->restoreConfig())
    {
    	if(!m_pRoot->showConfigDialog())
    		return false;
    }
    m_pRenderWnd = m_pRoot->initialise(true, wndTitle);
    
    inputManager->initialise(m_pRenderWnd);


    m_pViewport = m_pRenderWnd->addViewport(0);
    m_pViewport->setBackgroundColour(ColourValue(0.5f, 0.5f, 0.5f, 1.0f));
    
    m_pViewport->setCamera(0);
    
    size_t hWnd = 0;
    m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);
    
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

    // Calling methods from Interface class into the engine
    Interface cegui;
    cegui.initialiseDefaultResourceGroups();
    cegui.setupCEGUI();
    
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    m_pTimer = new Ogre::Timer();
    m_pTimer->reset();
    m_pRenderWnd->setActive(true);

    return true;
}

void XsiliumFramework::updateOgre(double timeSinceLastFrame)
{
}
