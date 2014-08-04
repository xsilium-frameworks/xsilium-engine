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
	sauvegardeParam = false;


	m_pRoot = Engine::getInstance()->getRoot();

	Engine::getInstance()->addListenner(this);

}

GraphicsManager::~GraphicsManager() {

}


void GraphicsManager::setParamettreOgre(std::string key, std::string valeur)
{
	if(m_pRenderSystem)
	{
		m_pRenderSystem->setConfigOption(key,valeur);
	}
}

bool GraphicsManager::initOgre()
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
		}

		// Set defaults per RenderSystem
		m_pRenderSystem->setConfigOption("Full Screen", "No");
		m_pRenderSystem->setConfigOption("VSync", "No");
		m_pRenderSystem->setConfigOption("Video Mode", "800 x 600");
		m_pRenderSystem->setConfigOption("Colour Depth", "32");
		m_pRenderSystem->setConfigOption("FSAA", "0");
		m_pRenderSystem->setConfigOption("sRGB Gamma Conversion", "No");

		m_pRoot->setRenderSystem(m_pRenderSystem);
	}

	return true;
}

void GraphicsManager::createWindow()
{
	m_pRenderWnd = m_pRoot->initialise(true,fenetreName);

	if(sauvegardeParam)
		m_pRoot->saveConfig();

	m_pRenderWnd->addViewport(0);

	m_pRenderWnd->setActive(true);

}

void GraphicsManager::loadRessource()
{
	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
	cf.load( Engine::getInstance()->getResourcePath() + "resources.cfg");

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


Ogre::RenderWindow* GraphicsManager::getRenderWindow()
{
	return this->m_pRenderWnd;
}

void GraphicsManager::processEvent(Event * event)
{

}


} /* namespace Engine */
