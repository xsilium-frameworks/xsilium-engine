/*
 * \file GraphicsMeteoManager.cpp
 *
 *  Created on: \date 26 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsMeteoManager.h"

namespace Engine {

GraphicsMeteoManager::GraphicsMeteoManager(Ogre::SceneManager *sm, Ogre::Root* m_pRoot , Ogre::RenderWindow* m_pRenderWnd , Ogre::Camera* m_pCamera) {
	m_pSceneMgr = sm;
	this->m_pRoot = m_pRoot ;
	this->m_pRenderWnd = m_pRenderWnd ;
	this->m_pCamera = m_pCamera;
	mBeafourt = 0;
	mRain = false;
	nWaves = 0;
	mStorm = false;

	graphicsSky = GraphicsSky::getInstance();
	graphicsWater = GraphicsWater::getInstance();
}

GraphicsMeteoManager::~GraphicsMeteoManager() {
	GraphicsSky::DestroyInstance();
	GraphicsWater::DestroyInstance();
}

void GraphicsMeteoManager::computeColours()
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

void GraphicsMeteoManager::computeSkyX()
{

	SkyX::AtmosphereManager::Options mSkyXOptions = graphicsSky->getSkyX()->getAtmosphereManager()->getOptions();
	switch(mBeafourt){
	//! Beafourt = 0 : Calm
	case 0:
		// Clouds
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.1f,0.25f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.63f,0.63f,0.7f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.35f, 0.2f, 0.92f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.4f, 0.7f, 0.f, 0.f));
		// Sky environment
		mSkyXOptions.RayleighMultiplier = 0.0022f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.57f, 0.52f, 0.44f);
		mSkyXOptions.Exposure = 3.f;
		break;
		//! Beafourt = 1 : Light air
	case 1:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.1f,0.3f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.63f,0.63f,0.7f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.35f, 0.2f, 0.9f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.4f, 0.7f, 0.05f, 0.f));
		mSkyXOptions.RayleighMultiplier = 0.0025f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.57f, 0.52f, 0.44f);
		mSkyXOptions.Exposure = 3.f;
		break;
		//! Beafourt = 2 : Light breeze
	case 2:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.2f,0.35f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.63f,0.63f,0.7f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.34f, 0.2f, 0.85f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.402f, 0.65f, 0.1f, 0.01f));
		mSkyXOptions.RayleighMultiplier = 0.0028f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.569f, 0.52f, 0.445f);
		mSkyXOptions.Exposure = 3.f;
		break;
		//! Beafourt = 3 : Gentle breeze
	case 3:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.3f,0.4f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.6f,0.6f,0.67f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.33f, 0.22f, 0.8f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.405f, 0.6f, 0.15f, 0.02f));
		mSkyXOptions.RayleighMultiplier = 0.0031f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.568f, 0.52f, 0.45f);
		mSkyXOptions.Exposure = 2.9f;
		break;
		//! Beafourt = 4 : Moderate breeze
	case 4:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.4f,0.5f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.55f,0.55f,0.62f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.32f, 0.24f, 0.75f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.409f, 0.55f, 0.2f, 0.03f));
		mSkyXOptions.RayleighMultiplier = 0.0034f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.567f, 0.52f, 0.455f);
		mSkyXOptions.Exposure = 2.8f;
		break;
		//! Beafourt = 5 : Fresh breeze
	case 5:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.5f,0.6f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.5f,0.5f,0.57f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.31f, 0.26f, 0.7f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.413f, 0.51f, 0.25f, 0.04f));
		mSkyXOptions.RayleighMultiplier = 0.0037f;
		mSkyXOptions.MieMultiplier = 0.000625f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.566f, 0.52f, 0.46f);
		mSkyXOptions.Exposure = 2.6f;
		break;
		//! Beafourt = 6 : Strong breeze
	case 6:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.6f,0.7f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.45f,0.45f,0.51f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.30f, 0.28f, 0.65f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.42f, 0.45f, 0.3f, 0.05f));
		mSkyXOptions.RayleighMultiplier = 0.0040f;
		mSkyXOptions.MieMultiplier = 0.000575f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.555f, 0.52f, 0.465f);
		mSkyXOptions.Exposure = 2.2f;
		break;
		//! Beafourt = 7 : High wind, Moderate gale, Near gale
	case 7:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.7f,0.8f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.4f,0.4f,0.45f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.29f, 0.3f, 0.6f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.428f, 0.42f, 0.35f, 0.06f));
		mSkyXOptions.RayleighMultiplier = 0.0043f;
		mSkyXOptions.MieMultiplier = 0.000525f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.554f, 0.52f, 0.47f);
		mSkyXOptions.Exposure = 1.8f;
		break;
		//! Beafourt = 8 : Gale, Fresh gale
	case 8:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.8f,0.9f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.35f,0.35f,0.39f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.28f, 0.32f, 0.58f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.435f, 0.36f, 0.4f, 0.07f));
		mSkyXOptions.RayleighMultiplier = 0.0046f;
		mSkyXOptions.MieMultiplier = 0.000475f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.553f, 0.52f, 0.48f);
		mSkyXOptions.Exposure = 1.4f;
		break;
		//! Beafourt = 9 : Strong gale
	case 9:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(0.9f,1.0f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.30f,0.30f,0.33f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.27f, 0.34f, 0.56f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.441f, 0.33f, 0.45f, 0.08f));
		mSkyXOptions.RayleighMultiplier = 0.0049f;
		mSkyXOptions.MieMultiplier = 0.000425f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.552f, 0.52f, 0.49f);
		mSkyXOptions.Exposure = 1.2f;
		break;
		//! Beafourt = 10 : Storm, Whole gale
	case 10:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(1.0f,1.0f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.25f,0.25f,0.27f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.26f, 0.36f, 0.54f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.445f, 0.31f, 0.5f, 0.09f));
		mSkyXOptions.RayleighMultiplier = 0.0052f;
		mSkyXOptions.MieMultiplier = 0.000375f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.551f, 0.52f, 0.50f);
		mSkyXOptions.Exposure = 1.1f;
		break;
		//! Beafourt = 11 : Violent storm
	case 11:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(1.0f,1.0f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.2f,0.2f,0.21f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.25f, 0.38f, 0.52f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.448f, 0.3f, 0.55f, 0.1f));
		mSkyXOptions.RayleighMultiplier = 0.0052f;
		mSkyXOptions.MieMultiplier = 0.000375f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.55f, 0.52f, 0.51f);
		mSkyXOptions.Exposure = 1.f;
		break;
		//! Beafourt = 12 : Hurricane force
	case 12:
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setWheater(1.0f,1.0f,false);
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.2f,0.2f,0.21f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.24f, 0.4f, 0.5f, 0.1f));
		graphicsSky->getSkyX()->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.45f, 0.3f, 0.6f, 0.1f));
		mSkyXOptions.RayleighMultiplier = 0.0052f;
		mSkyXOptions.MieMultiplier = 0.000375f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.55f, 0.52f, 0.52f);
		mSkyXOptions.Exposure = 1.f;
		break;
	}
	graphicsSky->getSkyX()->getAtmosphereManager()->setOptions(mSkyXOptions);

}

void GraphicsMeteoManager::computeWind()
{
	/*
	// Direction (Hydrax compatibility)
	SkyX::VClouds::VClouds* vclouds = mSkyX->getVCloudsManager()->getVClouds();
	vclouds->setWindDirection(Ogre::Radian(180.f));
	// Wind speed
	float v = (mBeafourt+1.f)/13.f;
	mSkyX->getVCloudsManager()->setWindSpeed(3600.f * v);
	mWind = v*Ogre::Vector3(25.f,0.f,0.f);
	//SSS_APP->particlesManager()->rain()->wind(mWind);
	 */
}

void GraphicsMeteoManager::computeRain()
{
	/*
    if(mRainSound) SSS_SOUND->stop(mRainSound); mRainSound=NULL;
    if( (!mRain) || (mBeafourt <= 2) ){
        SSS_APP->particlesManager()->rain()->dropletRate(0.f);
        return;
    }
    float rate = (mBeafourt-2.f)/10.f;
    SSS_APP->particlesManager()->rain()->dropletRate(rate);
    if(mBeafourt <= 6){
        mRainSound = SSS_SOUND->play("Rain_Droplets.wav", true);
    }
    else{
        mRainSound = SSS_SOUND->play("Rain_Shower.wav", true);
    }
	 */
}

void GraphicsMeteoManager::computeStorm()
{
	/*
	SkyX::VClouds::VClouds* vclouds = mSkyX->getVCloudsManager()->getVClouds();
	if( (!mStorm) || (mBeafourt <= 4) ){
		vclouds->getLightningManager()->setEnabled(false);
		return;
	}
	float t = 10.f*(1.f - (mBeafourt - 4.f)/9.f);
	vclouds->getLightningManager()->setEnabled(true);
	vclouds->getLightningManager()->setAverageLightningApparitionTime(t);
	vclouds->getLightningManager()->setLightningColor(Ogre::Vector3(1,0.976,0.92));
	vclouds->getLightningManager()->setLightningTimeMultiplier(2.f);
	 */
}

void GraphicsMeteoManager::setWaves(unsigned int n, Ogre::Vector2 A, Ogre::Vector2 T, Ogre::Vector2 varDir, float varP)
{
	/*  unsigned int i;
    Hydrax::Module::ProjectedGrid *mModule = (Hydrax::Module::ProjectedGrid*)mHydrax->getModule();
    Hydrax::Noise::Perlin* mNoise = (Hydrax::Noise::Perlin*) mModule->getNoise();
    // Hydrax reinitialization
    for(i=0;i<nWaves;i++)
        mNoise->  removeWave(0);
    // Add waves
    nWaves = n;
    for(i=0;i<nWaves;i++){
        Ogre::Vector2 dir;
        dir.x = Ogre::Math::RangeRandom(1.f - varDir.x, 1.f + varDir.x);
        dir.y = Ogre::Math::RangeRandom(-varDir.y, varDir.y);
        dir.normalise();
        float wA = Ogre::Math::RangeRandom(A.x, A.y);
        float wT = Ogre::Math::RangeRandom(T.x, T.y);
        float wP = Ogre::Math::RangeRandom(0.f, varP);
        Hydrax::Noise::HydrOCLNoise::Wave w = Hydrax::Noise::HydrOCLNoise::Wave(dir,wA,wT,wP);
        static_cast<Hydrax::Noise::HydrOCLNoise*>(mModule->getNoise())->addWave(w);
    } */

}

void GraphicsMeteoManager::computeHydrax()
{
	/*
    Hydrax::Module::ProjectedGrid *mModule = (Hydrax::Module::ProjectedGrid*) mHydrax->getModule();
    Hydrax::Noise::Perlin * mNoise = (Hydrax::Noise::Perlin*)mModule->getNoise();
    Hydrax::Noise::Perlin::Options opts = mNoise->getOptions();
    switch(mBeafourt){
        //! Beafourt = 0 : Calm
        case 0:
            // Waves
            setWaves(3, Ogre::Vector2(0.02f,0.15f), Ogre::Vector2(8.f,11.f));
            // Sea noise
            opts.GPU_Strength = 2.f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 1 : Light air
        case 1:
            setWaves(4, Ogre::Vector2(0.05f,0.2f), Ogre::Vector2(8.f,11.f));
            opts.GPU_Strength = 2.25f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 2 : Light breeze
        case 2:
            setWaves(5, Ogre::Vector2(0.1f,0.25f), Ogre::Vector2(8.f,11.f));
            opts.GPU_Strength = 2.5f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 3 : Gentle breeze
        case 3:
            setWaves(6, Ogre::Vector2(0.1f,0.3f), Ogre::Vector2(7.f,11.f));
            opts.GPU_Strength = 2.75f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 4 : Moderate breeze
        case 4:
            setWaves(7, Ogre::Vector2(0.15f,0.35f), Ogre::Vector2(7.f,11.f));
            opts.GPU_Strength = 3.f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 5 : Fresh breeze
        case 5:
            setWaves(8, Ogre::Vector2(0.15f,0.4f), Ogre::Vector2(7.f,11.f));
            opts.GPU_Strength = 3.5f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 6 : Strong breeze
        case 6:
            setWaves(9, Ogre::Vector2(0.15f,0.45f), Ogre::Vector2(7.f,12.f));
            opts.GPU_Strength = 4.f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 7 : High wind, Moderate gale, Near gale
        case 7:
            setWaves(10, Ogre::Vector2(0.15f,0.5f), Ogre::Vector2(5.f,12.f));
            opts.GPU_Strength = 4.5f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 8 : Gale, Fresh gale
        case 8:
            setWaves(12, Ogre::Vector2(0.15f,0.6f), Ogre::Vector2(4.f,13.f));
            opts.GPU_Strength = 5.f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 9 : Strong gale
        case 9:
            setWaves(14, Ogre::Vector2(0.2f,0.7f), Ogre::Vector2(4.f,13.f));
            opts.GPU_Strength = 5.25f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 10 : Storm, Whole gale
        case 10:
            setWaves(16, Ogre::Vector2(0.2f,0.8f), Ogre::Vector2(4.f,13.f));
            opts.GPU_Strength = 5.5f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 11 : Violent storm
        case 11:
            setWaves(18, Ogre::Vector2(0.3f,0.9f), Ogre::Vector2(4.f,13.f));
            opts.GPU_Strength = 5.75f; mNoise->setOptions(opts);
            break;
        //! Beafourt = 12 : Hurricane force
        case 12:
            setWaves(20, Ogre::Vector2(0.3f,1.f), Ogre::Vector2(4.f,13.f));
            opts.GPU_Strength = 6.f; mNoise->setOptions(opts);
            break;
    }
	 */

}

void GraphicsMeteoManager::updateEnvironmentLighting()
{

	Ogre::Vector3 lightDir = graphicsSky->getBasicController()->getSunDirection();

	float point = (lightDir.y + 1.0f) / 2.0f;

	Ogre::Light *sun = m_pSceneMgr->getLight("Sun");

	Ogre::Vector3 sunCol = mSunGradient.getColor(point);
	sun->setSpecularColour(sunCol.x, sunCol.y, sunCol.z);
	Ogre::Vector3 ambientCol = mAmbientGradient.getColor(point);
	sun->setDiffuseColour(ambientCol.x, ambientCol.y, ambientCol.z);
	graphicsWater->getHydraX()->setWaterColor(mWaterGradient.getColor(point));
	graphicsWater->getHydraX()->setSunColor(mSunGradient.getColor(point));



	if(graphicsSky->getBasicController()->getTime().x > graphicsSky->getBasicController()->getTime().y && graphicsSky->getBasicController()->getTime().x < graphicsSky->getBasicController()->getTime().z )
	{
		lightDir = graphicsSky->getBasicController()->getMoonDirection();
		Ogre::Vector3 sunPos = m_pCamera->getDerivedPosition() - lightDir*graphicsSky->getSkyX()->getMeshManager()->getSkydomeRadius(m_pCamera)*0.1;
		graphicsWater->getHydraX()->setSunPosition(sunPos);

		sun->setDirection(lightDir);
		sun->setPosition(m_pCamera->getDerivedPosition() - lightDir*graphicsSky->getSkyX()->getMeshManager()->getSkydomeRadius(m_pCamera)*0.02);



	}
	else
	{
		lightDir = graphicsSky->getBasicController()->getSunDirection();
		Ogre::Vector3 sunPos = m_pCamera->getDerivedPosition() - lightDir*graphicsSky->getSkyX()->getMeshManager()->getSkydomeRadius(m_pCamera)*0.1;
		graphicsWater->getHydraX()->setSunPosition(sunPos);

		sun->setDirection(lightDir);
		sun->setPosition(m_pCamera->getDerivedPosition() - lightDir*graphicsSky->getSkyX()->getMeshManager()->getSkydomeRadius(m_pCamera)*0.02);

	}




}

void GraphicsMeteoManager::updateShadowFarDistance()
{
	Ogre::Light* sun = m_pSceneMgr->getLight("Sun");
	float currentLength = (Ogre::Vector3(1500, 100, 1500) - m_pCamera->getDerivedPosition()).length();

	if (currentLength < 1000)
	{
		mLastPositionLength = currentLength;
		return;
	}

	if (currentLength - mLastPositionLength > 100)
	{
		mLastPositionLength += 100;

		sun->setShadowFarDistance(sun->getShadowFarDistance() + 100);
	}
	else if (currentLength - mLastPositionLength < -100)
	{
		mLastPositionLength -= 100;

		sun->setShadowFarDistance(sun->getShadowFarDistance() - 100);
	}
}

void GraphicsMeteoManager::update(float dt)
{
	if (graphicsSky->getSkyX() && graphicsWater->getHydraX())
	{
		updateEnvironmentLighting();
		updateShadowFarDistance();
	}

	graphicsSky->update(dt);
	graphicsWater->update(dt);
}

void GraphicsMeteoManager::beafourt(unsigned int beaf)
{
	// New beafourt value (clamped)
	mBeafourt = beaf;
	if(mBeafourt > 12) mBeafourt=12;
	// Compute environment values asssociated
	computeColours();
	computeSkyX();
	computeWind();
	computeRain();
	computeStorm();
	computeHydrax();
}

void GraphicsMeteoManager::rain(bool flag)
{
	mRain = flag;
	computeRain();
}

void GraphicsMeteoManager::storm(bool flag)
{
	mStorm = flag;
	computeStorm();
}

void GraphicsMeteoManager::init()
{
	graphicsSky->init(m_pSceneMgr,m_pRoot,m_pRenderWnd,m_pCamera);
	graphicsWater->init(m_pSceneMgr,m_pRoot,m_pRenderWnd,m_pCamera);
	graphicsWater->addRttListener(new GraphicsHydraxRttListener(graphicsSky->getSkyX(),graphicsWater->getHydraX()));

	beafourt(mBeafourt);

	// Shadows
	m_pSceneMgr->setShadowCameraSetup(Ogre::ShadowCameraSetupPtr(new Ogre::FocusedShadowCameraSetup()));

	mLastPositionLength =  (Ogre::Vector3(1500, 100, 1500) - m_pCamera->getDerivedPosition()).length();
}

} /* namespace Engine */
