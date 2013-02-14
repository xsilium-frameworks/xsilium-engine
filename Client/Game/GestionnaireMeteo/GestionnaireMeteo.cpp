/*
 * \file GestionnaireMeteo.cpp
 *
 *  Created on: \date 14 fŽvr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireMeteo.h"

GestionnaireMeteo::GestionnaireMeteo(Ogre::SceneManager *sm, Ogre::Camera *c) {

	m_pSceneMgr = sm;
	m_pCamera = c;

    mSkyX = 0;
    mBasicController = 0;
    mHydrax = 0;

}

GestionnaireMeteo::~GestionnaireMeteo() {

	delete mSkyX;
	delete mHydrax ;
	XsiliumFramework::getInstance()->m_pRoot->removeFrameListener(this);
}

bool GestionnaireMeteo::frameStarted(const Ogre::FrameEvent& evt)
{
	mSkyX->update(evt.timeSinceLastFrame);
	mHydrax->update(evt.timeSinceLastFrame);
	return true;
}


void GestionnaireMeteo::create()
{
	mBasicController = new SkyX::BasicController();
	mSkyX = new SkyX::SkyX(m_pSceneMgr, mBasicController);
	mSkyX->create();

	XsiliumFramework::getInstance()->m_pRenderWnd->addListener(mSkyX);

	mHydrax = new Hydrax::Hydrax(m_pSceneMgr, m_pCamera, XsiliumFramework::getInstance()->m_pRenderWnd->getViewport(0));






	Hydrax::Module::ProjectedGrid *mModule
				= new Hydrax::Module::ProjectedGrid(mHydrax,new Hydrax::Noise::Perlin(/*Generic one*/),
				                                    Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
													// Normal mode
													Hydrax::MaterialManager::NM_VERTEX,
													// Projected grid options
											        Hydrax::Module::ProjectedGrid::Options());

			// Set our module
			mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));

			// Load all parameters from config file
			// Remarks: The config file must be in Hydrax resource group.
			// All parameters can be set/updated directly by code(Like previous versions),
			// but due to the high number of customizable parameters, since 0.4 version, Hydrax allows save/load config files.
			mHydrax->loadCfg("HydraxDemo.hdx");


			if (XsiliumFramework::getInstance()->m_pRoot->getRenderSystem()->getName() == "OpenGL Rendering Subsystem")
				mHydrax->setShaderMode( Hydrax::MaterialManager::SM_GLSL);
			else
				mHydrax->setShaderMode( Hydrax::MaterialManager::SM_HLSL);



	        // Create water
	        mHydrax->create();



	XsiliumFramework::getInstance()->m_pRoot->addFrameListener(this);
}
