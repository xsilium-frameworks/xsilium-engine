/*
 * \file GraphicsWater.cpp
 *
 *  Created on: \date 25 sept. 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsWater.h"

namespace Engine {

	GraphicsWater::GraphicsWater(Ogre::SceneManager *sm, Ogre::Root* m_pRoot, Ogre::RenderWindow* m_pRenderWnd) {
	mHydrax = 0;
	m_pSceneMgr = sm;

}

GraphicsWater::~GraphicsWater() {
	// TODO Auto-generated destructor stub
}

void GraphicsWater::initHydrax() {

	// Create Hydrax object
	mHydrax = new Hydrax::Hydrax(m_pSceneMgr, m_pCamera, m_pRenderWnd->getViewport(0));

	// Create our projected grid module  
	Hydrax::Module::ProjectedGrid *mModule
		= new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
		mHydrax,
		// Noise module
		new Hydrax::Noise::Perlin(/*Generic one*/),
		// Base plane
		Ogre::Plane(Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0)),
		// Normal mode
		Hydrax::MaterialManager::NM_VERTEX,
		// Projected grid options
		Hydrax::Module::ProjectedGrid::Options(/*264 /*Generic one*/));

	// Set our module
	mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));

	// Load all parameters from config file
	// Remarks: The config file must be in Hydrax resource group.
	mHydrax->loadCfg("HydraxDemo.hdx");

	// Create water
	mHydrax->create();

}

} /* namespace Engine */
