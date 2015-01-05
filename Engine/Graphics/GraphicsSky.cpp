/*
 * \file GraphicsSky.cpp
 *
 *  Created on: \date 25 sept. 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsSky.h"

namespace Engine {

GraphicsSky::GraphicsSky(Ogre::SceneManager *sm, Ogre::Root* m_pRoot, Ogre::RenderWindow* m_pRenderWnd) {
	m_pSceneMgr = sm;
	this->m_pRoot = m_pRoot ;
	this->m_pRenderWnd = m_pRenderWnd;
	mSkyXController = 0;
	mSkyX = 0;


}

GraphicsSky::~GraphicsSky() {
	// TODO Auto-generated destructor stub
}

void GraphicsSky::initSkyX()
{
	LogManager::getInstance()->setLogMessage("Initialisation de SkyX", NORMAL);

	m_pSceneMgr->getLight("Sun")->setType(Ogre::Light::LT_DIRECTIONAL);
	m_pSceneMgr->getLight("Sun")->setDirection(Ogre::Vector3(0.f, -1.f, -1.f));

	// Create SkyX
	mSkyXController = new SkyX::BasicController();
	mSkyX = new SkyX::SkyX(m_pSceneMgr, mSkyXController);
	mSkyX->create();
	// Set moon phase
	// mSkyXController->setMoonPhase(0.75f);
	// Distance geometry falling is a feature introduced in SkyX 0.2
	// When distance falling is enabled, the geometry linearly falls with the distance and the
	// amount of falling in world units is determinated by the distance between the cloud field "plane"
	// and the camera height multiplied by the falling factor.
	// For this demo, a falling factor of two is good enough for the point of view we're using. That means that if the camera
	// is at a distance of 100 world units from the cloud field, the fartest geometry will fall 2*100 = 200 world units.
	// This way the cloud field covers a big part of the sky even if the camera is in at a very low altitude.
	// The second parameter is the max amount of falling distance in world units. That's needed when for example, you've an
	// ocean and you don't want to have the volumetric cloud field geometry falling into the water when the camera is underwater.
	// -1 means that there's not falling limit.
	mSkyX->getVCloudsManager()->getVClouds()->setDistanceFallingParams(Ogre::Vector2(2.f,-1.f));
	// Register listeners
	m_pRenderWnd->addListener(mSkyX);
	// Clouds generation
	if (!mSkyX->getCloudsManager()->getCloudLayers().empty()) {
		mSkyX->getCloudsManager()->removeAll();
	}
	if (!mSkyX->getVCloudsManager()->isCreated()) {
		mSkyX->getVCloudsManager()->create(mSkyX->getMeshManager()->getSkydomeRadius(m_pSceneMgr->getCamera("CamPrincipal")));
	}

	mSkyX->getVCloudsManager()->setAutoupdate(false);

	mSkyX->setTimeMultiplier(1 / 3600.f);

}

void GraphicsSky::update(float dt)
{
	if(mSkyX)
		mSkyX->update(dt);
}

SkyX::SkyX* GraphicsSky::getSkyX()
{
	return this->mSkyX;
}


} /* namespace Engine */
