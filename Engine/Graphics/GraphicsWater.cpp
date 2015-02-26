/*
 * \file GraphicsWater.cpp
 *
 *  Created on: \date 25 sept. 2014
 *      Author: \author joda xelfe
 *  \brief : Fichier source de la classe GraphicsWater
 */
#include "GraphicsWater.h"

namespace Engine {

GraphicsWater::GraphicsWater() {
	m_pHydrax = 0;
	m_pTerrainGroup = 0;
	m_pSceneMgr = 0;
	m_pRoot = 0;
	m_pRenderWnd = 0;
	m_pCamera = 0;

}

GraphicsWater::~GraphicsWater() {
	delete m_pHydrax;
}

void GraphicsWater::init(Ogre::SceneManager *sm, Ogre::Root* m_pRoot, Ogre::RenderWindow* m_pRenderWnd,Ogre::Camera* m_pCamera) {

	m_pSceneMgr = sm;
	this->m_pRoot = m_pRoot;
	this->m_pRenderWnd = m_pRenderWnd;
	this->m_pCamera = m_pCamera;

	LogManager::getInstance()->setLogMessage("Initialisation de Hydrax", NORMAL);

	// Create Hydrax object
	m_pHydrax = new Hydrax::Hydrax(m_pSceneMgr, m_pCamera, m_pRenderWnd->getViewport(0));

	// Create our projected grid module
	Hydrax::Module::ProjectedGrid *mModule
	= new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
			m_pHydrax,
			// Noise module
			new Hydrax::Noise::Perlin (/*Generic one*/),
			// Base plane
			Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
			// Normal mode
			Hydrax::MaterialManager::NM_VERTEX,
			// Projected grid options
			Hydrax::Module::ProjectedGrid::Options(/*264 /*Generic one*/));

	// Set our module
	m_pHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));

	// Load all parameters from config file
	// Remarks: The config file must be in Hydrax resource group.
	m_pHydrax->loadCfg("Hydrax.hdx");

	// Create water
	m_pHydrax->create();


}

void GraphicsWater::addRttListener(GraphicsHydraxRttListener * graphicsHydraxRttListener)
{
        m_pHydrax->getRttManager()->addRttListener(graphicsHydraxRttListener);
}


void GraphicsWater::update(float dt)
{
	if(m_pHydrax)
		m_pHydrax->update(dt);
}

Hydrax::Hydrax* GraphicsWater::getHydraX()
{
	return this->m_pHydrax;
}

} /* namespace Engine */
