/*
 * \file GestionnaireMeteo.cpp
 *
 *  Created on: \date 14 fŽvr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireMeteo.h"

ShadowConfig mShadowConfigList[] = {ShadowConfig(false, 0), ShadowConfig(true, 2048) };

GestionnaireMeteo::GestionnaireMeteo(Ogre::SceneManager *sm, Ogre::Camera *c, SkyX::SkyX* mSkyX) {

	m_pSceneMgr = sm;
	m_pCamera = c;
	this->mSkyX = mSkyX;
    
    mForceDisableShadows = false;
    mShadowMode = static_cast<int>(SM_HIGH);

    
	mBasicController = 0;
	mHydrax = 0;
	mLastPositionLength = (Ogre::Vector3(1500, 100, 1500) - m_pCamera->getDerivedPosition()).length() ;

	// Color gradients
	// Water
	mWaterGradient = SkyX::ColorGradient();
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.058209,0.535822,0.779105)*0.4, 1));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.058209,0.535822,0.729105)*0.3, 0.8));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.058209,0.535822,0.679105)*0.25, 0.6));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.058209,0.535822,0.679105)*0.2, 0.5));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.058209,0.535822,0.679105)*0.1, 0.45));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.058209,0.535822,0.679105)*0.025, 0));
	// Sun
	mSunGradient = SkyX::ColorGradient();
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.8,0.75,0.55)*1.5, 1.0f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.8,0.75,0.55)*1.4, 0.75f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.8,0.75,0.55)*1.3, 0.5625f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.6,0.5,0.2)*1.5, 0.5f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.5,0.5,0.5)*0.25, 0.45f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.5,0.5,0.5)*0.01, 0.0f));
	// Ambient
	mAmbientGradient = SkyX::ColorGradient();
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1,1,1)*1, 1.0f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1,1,1)*1, 0.6f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1,1,1)*0.6, 0.5f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1,1,1)*0.3, 0.45f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1,1,1)*0.1, 0.35f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1,1,1)*0.05, 0.0f));


}

GestionnaireMeteo::~GestionnaireMeteo() {

	XsiliumFramework::getInstance()->getRoot()->removeFrameListener(this);
	XsiliumFramework::getInstance()->getRenderWindow()->removeListener(mSkyX);
    if(mSkyX)
        delete mSkyX;
	if(mHydrax)
        delete mHydrax ;
}

void GestionnaireMeteo::setShadowMode(Ogre::SceneManager *sm, const ShadowMode& smode)
{
	//Ogre::MaterialPtr IslandMat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("Island"));
    
	if (mShadowConfigList[smode].Enable && !mForceDisableShadows)
	{
		sm->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
		sm->setShadowTextureConfig(0, mShadowConfigList[smode].Size, mShadowConfigList[smode].Size, Ogre::PF_X8R8G8B8);
	//	IslandMat->getTechnique(0)->setSchemeName("Default");
	//	IslandMat->getTechnique(1)->setSchemeName("NoDefault");
	}
	else
	{
		sm->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
	//	IslandMat->getTechnique(0)->setSchemeName("NoDefault");
	//	IslandMat->getTechnique(1)->setSchemeName("Default");
	}
}

bool GestionnaireMeteo::frameStarted(const Ogre::FrameEvent& evt)
{
	// Update environment lighting
	updateEnvironmentLighting();

	// Update shadow far distance
	updateShadowFarDistance();

	mSkyX->update(evt.timeSinceLastFrame);
	mHydrax->update(evt.timeSinceLastFrame);
	return true;
}


void GestionnaireMeteo::create()
{
	Ogre::Light *mLight0 = m_pSceneMgr->getLight("Light#0");
	mLight0->setDiffuseColour(1, 1, 1);
	mLight0->setCastShadows(false);
    
    // Shadow caster
    Ogre::Light *mLight1 = m_pSceneMgr->createLight("Light#1");
    mLight1->setType(Ogre::Light::LT_DIRECTIONAL);

	mBasicController = (SkyX::BasicController *) mSkyX->getController();
	mBasicController->setTime(Ogre::Vector3(18.75f, 7.5f, 20.5f));
    
    mSkyX->setTimeMultiplier(0.1f);

	mSkyX->create();

	XsiliumFramework::getInstance()->getRenderWindow()->addListener(mSkyX);
    
    
    // Shadows
    m_pSceneMgr->setShadowCameraSetup(Ogre::ShadowCameraSetupPtr(new Ogre::FocusedShadowCameraSetup()));
   // m_pSceneMgr->setShadowTextureCasterMaterial("ShadowCaster");
    m_pSceneMgr->getLight("Light#1")->setShadowFarDistance(1750);
    
    setShadowMode(m_pSceneMgr, static_cast<ShadowMode>(mShadowMode));

	mHydrax = new Hydrax::Hydrax(m_pSceneMgr, m_pCamera, XsiliumFramework::getInstance()->getRenderWindow()->getViewport(0));






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
	mHydrax->loadCfg("Hydrax.hdx");

	// Create water
	mHydrax->create();

	// Add the Hydrax Rtt listener
	mHydrax->getRttManager()->addRttListener(new HydraxRttListener(mSkyX,mHydrax));


    
    

	XsiliumFramework::getInstance()->getRoot()->addFrameListener(this);

}

void GestionnaireMeteo::updateEnvironmentLighting()
{
	float point;

	Ogre::Vector3 time = mBasicController->getTime();

	bool day = time.x > time.y && time.x < time.z ;
	Ogre::Vector3 lightDir = (day) ? mBasicController->getSunDirection() : mBasicController->getMoonDirection() ;
    
    
    bool preForceDisableShadows = mForceDisableShadows;
    mForceDisableShadows = (lightDir.y > 0.15f) ? true : false;
    
    if (preForceDisableShadows != mForceDisableShadows)
    {
        setShadowMode(m_pSceneMgr, static_cast<ShadowMode>(mShadowMode));
    }
    
	point = (-lightDir.y + 1.0f) / 2.0f;

	// Calculate current color gradients point
	mHydrax->setWaterColor(mWaterGradient.getColor(point));

	Ogre::Vector3 sunPos = m_pCamera->getDerivedPosition() - lightDir * mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera) * 0.1;
	mHydrax->setSunPosition(sunPos);

	Ogre::Light *Light0 = m_pSceneMgr->getLight("Light#0"),
                *Light1 = m_pSceneMgr->getLight("Light#1");

	Light0->setPosition(m_pCamera->getDerivedPosition() - lightDir * mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera) * 0.02);
    Light1->setDirection(-lightDir);

	Ogre::Vector3 sunCol = mSunGradient.getColor(point);
	Light0->setSpecularColour(sunCol.x, sunCol.y, sunCol.z);
	Ogre::Vector3 ambientCol = mAmbientGradient.getColor(point);
	Light0->setDiffuseColour(ambientCol.x, ambientCol.y, ambientCol.z);
	mHydrax->setSunColor(sunCol);


}


/** Update shadow far distance
 */
void GestionnaireMeteo::updateShadowFarDistance()
{
    Ogre::Light * Light1 = m_pSceneMgr->getLight("Light#1");
	float currentLength = (Ogre::Vector3(1500, 100, 1500) - m_pCamera->getDerivedPosition()).length();

	if (currentLength < 1000)
	{
		mLastPositionLength = currentLength;
		return;
	}

	if (currentLength - mLastPositionLength > 100)
	{
		mLastPositionLength += 100;
        Light1->setShadowFarDistance(Light1->getShadowFarDistance() + 100);
	}
	else if (currentLength - mLastPositionLength < -100)
	{
		mLastPositionLength -= 100;
        Light1->setShadowFarDistance(Light1->getShadowFarDistance() - 100);
	}
}
