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

	XsiliumFramework::getInstance()->m_pRoot->removeFrameListener(this);
	XsiliumFramework::getInstance()->m_pRenderWnd->removeListener(mSkyX);
	delete mSkyX;
	delete mHydrax ;
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
	Ogre::Light *mLight1 = m_pSceneMgr->createLight("Light1");
	mLight1->setType(Ogre::Light::LT_DIRECTIONAL);


	mBasicController = new SkyX::BasicController();
	mSkyX = new SkyX::SkyX(m_pSceneMgr, mBasicController);

	// A little change to default atmosphere settings :)
	SkyX::AtmosphereManager::Options atOpt = mSkyX->getAtmosphereManager()->getOptions();
	atOpt.RayleighMultiplier = 0.003075f;
	atOpt.MieMultiplier = 0.00125f;
	atOpt.InnerRadius = 9.92f;
	atOpt.OuterRadius = 10.3311f;
	mSkyX->getAtmosphereManager()->setOptions(atOpt);


	// Add a basic cloud layer
	mSkyX->getCloudsManager()->add(SkyX::CloudLayer::Options(/* Default options */));



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

	        // Create water
	        mHydrax->create();

	        // Add the Hydrax Rtt listener
	        mHydrax->getRttManager()->addRttListener(new HydraxRttListener(mSkyX,mHydrax));





	XsiliumFramework::getInstance()->m_pRoot->addFrameListener(this);

}

void GestionnaireMeteo::updateEnvironmentLighting()
{
	Ogre::Vector3 lightDir = mBasicController->getSunDirection();

	// Calculate current color gradients point
	float point = (-lightDir.y + 1.0f) / 2.0f;
	mHydrax->setWaterColor(mWaterGradient.getColor(point));

	Ogre::Vector3 sunPos = m_pCamera->getDerivedPosition() - lightDir * mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera) * 0.1;
	mHydrax->setSunPosition(sunPos);

	Ogre::Light *Light0 = m_pSceneMgr->getLight("Light#0"),
				*Light1 = m_pSceneMgr->getLight("Light1");

	Light0->setPosition(m_pCamera->getDerivedPosition() - lightDir * mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera) * 0.02);
	Light1->setDirection(lightDir);

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
	Ogre::Light* Light1 = m_pSceneMgr->getLight("Light1");
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
