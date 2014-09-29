/*
 * \file GraphicsWater.cpp
 *
 *  Created on: \date 25 sept. 2014
 *      Author: \author joda xelfe
 *  \brief : Fichier source de la classe GraphicsWater
 */
#include "GraphicsWater.h"

namespace Engine {

	GraphicsWater::GraphicsWater(Ogre::SceneManager *sm, Ogre::Root* m_pRoot, Ogre::RenderWindow* m_pRenderWnd) {
		m_pHydrax = 0;
		m_pSceneMgr = sm;
		this->m_pRoot = m_pRoot;
		this->m_pRenderWnd = m_pRenderWnd;
		m_pCamera = 0;

	}

	GraphicsWater::~GraphicsWater() {
		// TODO Auto-generated destructor stub
	}

	void GraphicsWater::initHydrax() {

		LogManager::getInstance()->setLogMessage("Initialisation de Hydrax", NORMAL);

		// Create Hydrax object
		m_pHydrax = new Hydrax::Hydrax(m_pSceneMgr, m_pCamera, m_pRenderWnd->getViewport(0));

		// Create our projected grid module  
		Hydrax::Module::ProjectedGrid *mModule
			= new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
			m_pHydrax,
			// Noise module
			new Hydrax::Noise::Perlin(/*Generic one*/),
			// Base plane
			Ogre::Plane(Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0)),
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

		Ogre::TerrainGroup::TerrainIterator ti = m_pTerrainGroup->getTerrainIterator();
		while (ti.hasMoreElements())
		{
			Ogre::Terrain* t = ti.getNext()->instance;
			Ogre::MaterialPtr ptr = t->getMaterial();
			m_pHydrax->getMaterialManager()->addDepthTechnique(ptr->createTechnique());
		}

		m_pHydrax->getRttManager()->addRttListener(new GraphicsHydraxRttListener(m_pHydrax));

	}

} /* namespace Engine */
