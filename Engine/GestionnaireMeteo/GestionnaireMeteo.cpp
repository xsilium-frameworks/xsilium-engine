/*
 * \file GestionnaireMeteo.cpp
 *
 *  Created on: \date 14 fŽvr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireMeteo.h"

GestionnaireMeteo::GestionnaireMeteo(Ogre::SceneManager *sm) {

	m_pSceneMgr = sm;
	m_pCamera = XsiliumFramework::getInstance()->getRenderWindow()->getViewport(0)->getCamera();
	mSkyX = 0;
	mBasicController = 0;
	mHydrax = 0;
	mBeafourt = 0;

	updateCouleur();

	XsiliumFramework::getInstance()->getRoot()->addFrameListener(this);

}

GestionnaireMeteo::~GestionnaireMeteo() {

	XsiliumFramework::getInstance()->getRoot()->removeFrameListener(this);
	if(mSkyX)
	{
		XsiliumFramework::getInstance()->getRenderWindow()->removeListener(mSkyX);
		delete mSkyX;
	}
	if(mHydrax)
		delete mHydrax;
}

void GestionnaireMeteo::updateCouleur()
{
	// Beafourt associated darkness factor
	float f = (1.f - 0.7f*(mBeafourt/12.f) );
	// Water colour
	mWaterGradient = SkyX::ColorGradient();
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.0895f,0.1421f,0.2244f)*1.0f*f, 1.f));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.0895f,0.1421f,0.2244f)*0.8f*f, 0.8f));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.0895f,0.1421f,0.2244f)*0.6f*f, 0.6f));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.0895f,0.1421f,0.2244f)*0.4f*f, 0.5f));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.0895f,0.1421f,0.2244f)*0.2f*f, 0.45f));
	mWaterGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.0895f,0.1421f,0.2244f)*0.05f*f, 0.f));
	// Sun
	mSunGradient = SkyX::ColorGradient();
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.8f,0.75f,0.55f)*1.5f*f, 1.0f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.8f,0.75f,0.55f)*1.4f*f, 0.75f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.8f,0.75f,0.55f)*1.3f*f, 0.5625f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.6f,0.5f,0.2f)*1.5f*f, 0.5f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.5f,0.5f,0.5f)*0.25f*f, 0.45f));
	mSunGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(0.5f,0.5f,0.5f)*0.01f*f, 0.0f));
	// Ambient & Diffuse ilumination
	mDiffuseGradient = SkyX::ColorGradient();
	mDiffuseGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*1.f*f, 1.0f));
	mDiffuseGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*1.f*f, 0.6f));
	mDiffuseGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.6f*f, 0.5f));
	mDiffuseGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.3f*f, 0.45f));
	mDiffuseGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.1f*f, 0.35f));
	mDiffuseGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.05f*f, 0.0f));
	mAmbientGradient = SkyX::ColorGradient();
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.1f*f, 1.0f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.1f*f, 0.6f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.06f*f, 0.5f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.03f*f, 0.45f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.01f*f, 0.35f));
	mAmbientGradient.addCFrame(SkyX::ColorGradient::ColorFrame(Ogre::Vector3(1.f,1.f,1.f)*0.005f*f, 0.0f));
}

bool GestionnaireMeteo::frameStarted(const Ogre::FrameEvent& evt)
{
	if(mSkyX)
	{
		if(mHydrax)
		{
			updateEnvironmentLighting();
			mHydrax->update(evt.timeSinceLastFrame);
		}

		// SkyX use hours
		mSkyX->update(evt.timeSinceLastFrame);
	}


	return true;
}


void GestionnaireMeteo::createCiel(SkyX::SkyX* mSkyX)
{
	this->mSkyX = mSkyX;

	mBasicController = (SkyX::BasicController *) mSkyX->getController();
	mSkyX->create();

	mSkyX->getVCloudsManager()->getVClouds()->setDistanceFallingParams(Ogre::Vector2(2.f,-1.f));

	// Clouds generation
	if (!mSkyX->getCloudsManager()->getCloudLayers().empty()) {
		mSkyX->getCloudsManager()->removeAll();
	}
	if (!mSkyX->getVCloudsManager()->isCreated()) {
		mSkyX->getVCloudsManager()->create(mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera));
	}

	XsiliumFramework::getInstance()->getRenderWindow()->addListener(mSkyX);
}

void GestionnaireMeteo::createEau(const Ogre::String File)
{

	mHydrax = new Hydrax::Hydrax(m_pSceneMgr, m_pCamera, m_pCamera->getViewport());

	Hydrax::Module::ProjectedGrid *mModule
	      = new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
	      mHydrax,
	      // Noise module
	      new Hydrax::Noise::Perlin(/*Generic one*/),
	      // Base plane
	      Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
	      // Normal mode
	      Hydrax::MaterialManager::NM_VERTEX,
	      // Projected grid options
	      Hydrax::Module::ProjectedGrid::Options(/*264 /*Generic one*/));

	// Set our module
	mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));
    mHydrax->getRttManager()->setReflectionDisplacementError(1.8);
    mHydrax->setUnderwaterCameraSwitchDelta(-.2);

	mHydrax->loadCfg("Hydrax.hdx");

	// Create water
	mHydrax->create();

	if(mSkyX)
		mHydrax->getRttManager()->addRttListener(new HydraxRttListener(mSkyX,mHydrax));
}

void GestionnaireMeteo::updateEnvironmentLighting()
{
	Ogre::Vector3 lightDir = mBasicController->getSunDirection();

	Ogre::Vector3 time = mBasicController->getTime();

	bool day = time.x > time.y && time.x < time.z ;

	// Calculate current color gradients point
	float point = (lightDir.y + 1.0f) / 2.0f;
	mHydrax->setWaterColor(mWaterGradient.getColor(point));

	Ogre::Vector3 sunPos = m_pCamera->getDerivedPosition() - lightDir * mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera) * 0.1;
	mHydrax->setSunPosition(sunPos);

	Ogre::Light *Light0 = m_pSceneMgr->getLight("Sun");

	Light0->setPosition(m_pCamera->getDerivedPosition() - lightDir * mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera) * 0.02);
	Light0->setDirection(-lightDir);

	Ogre::Vector3 sunCol = mSunGradient.getColor(point);
	Light0->setSpecularColour(sunCol.x, sunCol.y, sunCol.z);
	Ogre::Vector3 diffuseCol = mDiffuseGradient.getColor(point);
	Light0->setDiffuseColour(diffuseCol.x, diffuseCol.y, diffuseCol.z);
	Ogre::Vector3 ambientCol = mAmbientGradient.getColor(point);
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(ambientCol.x, ambientCol.y, ambientCol.z, 1.f));
	mHydrax->setSunColor(sunCol);

}

void GestionnaireMeteo::addDepthTechnique(Ogre::MaterialPtr mat)
{
		mHydrax->getMaterialManager()->addDepthTechnique(mat->createTechnique());
}
