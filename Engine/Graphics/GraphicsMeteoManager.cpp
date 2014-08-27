/*
 * \file GraphicsMeteoManager.cpp
 *
 *  Created on: \date 26 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsMeteoManager.h"

namespace Engine {

GraphicsMeteoManager::GraphicsMeteoManager(Ogre::SceneManager *sm, Ogre::Root* m_pRoot , Ogre::RenderWindow* m_pRenderWnd) {
	m_pSceneMgr = sm;
	this->m_pRoot = m_pRoot ;
	this->m_pRenderWnd = m_pRenderWnd ;
	m_pCamera = 0;
	mSkyX = 0;
	mSkyXController = 0;
	mHydrax = 0;
	mBeafourt = 0;
	mRain = false;
	nWaves = 0;
	mStorm = false;
}

GraphicsMeteoManager::~GraphicsMeteoManager() {
	if(mSkyX)
	{
		delete mSkyX;
	}
	if(mHydrax)
		delete mHydrax;
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
	SkyX::AtmosphereManager::Options mSkyXOptions = mSkyX->getAtmosphereManager()->getOptions();
	switch(mBeafourt){
	//! Beafourt = 0 : Calm
	case 0:
		// Clouds
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.1f,0.25f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.63f,0.63f,0.7f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.35f, 0.2f, 0.92f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.4f, 0.7f, 0.f, 0.f));
		// Sky environment
		mSkyXOptions.RayleighMultiplier = 0.0022f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.57f, 0.52f, 0.44f);
		mSkyXOptions.Exposure = 3.f;
		break;
		//! Beafourt = 1 : Light air
	case 1:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.1f,0.3f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.63f,0.63f,0.7f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.35f, 0.2f, 0.9f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.4f, 0.7f, 0.05f, 0.f));
		mSkyXOptions.RayleighMultiplier = 0.0025f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.57f, 0.52f, 0.44f);
		mSkyXOptions.Exposure = 3.f;
		break;
		//! Beafourt = 2 : Light breeze
	case 2:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.2f,0.35f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.63f,0.63f,0.7f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.34f, 0.2f, 0.85f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.402f, 0.65f, 0.1f, 0.01f));
		mSkyXOptions.RayleighMultiplier = 0.0028f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.569f, 0.52f, 0.445f);
		mSkyXOptions.Exposure = 3.f;
		break;
		//! Beafourt = 3 : Gentle breeze
	case 3:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.3f,0.4f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.6f,0.6f,0.67f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.33f, 0.22f, 0.8f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.405f, 0.6f, 0.15f, 0.02f));
		mSkyXOptions.RayleighMultiplier = 0.0031f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.568f, 0.52f, 0.45f);
		mSkyXOptions.Exposure = 2.9f;
		break;
		//! Beafourt = 4 : Moderate breeze
	case 4:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.4f,0.5f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.55f,0.55f,0.62f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.32f, 0.24f, 0.75f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.409f, 0.55f, 0.2f, 0.03f));
		mSkyXOptions.RayleighMultiplier = 0.0034f;
		mSkyXOptions.MieMultiplier = 0.000675f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.567f, 0.52f, 0.455f);
		mSkyXOptions.Exposure = 2.8f;
		break;
		//! Beafourt = 5 : Fresh breeze
	case 5:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.5f,0.6f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.5f,0.5f,0.57f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.31f, 0.26f, 0.7f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.413f, 0.51f, 0.25f, 0.04f));
		mSkyXOptions.RayleighMultiplier = 0.0037f;
		mSkyXOptions.MieMultiplier = 0.000625f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.566f, 0.52f, 0.46f);
		mSkyXOptions.Exposure = 2.6f;
		break;
		//! Beafourt = 6 : Strong breeze
	case 6:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.6f,0.7f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.45f,0.45f,0.51f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.30f, 0.28f, 0.65f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.42f, 0.45f, 0.3f, 0.05f));
		mSkyXOptions.RayleighMultiplier = 0.0040f;
		mSkyXOptions.MieMultiplier = 0.000575f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.555f, 0.52f, 0.465f);
		mSkyXOptions.Exposure = 2.2f;
		break;
		//! Beafourt = 7 : High wind, Moderate gale, Near gale
	case 7:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.7f,0.8f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.4f,0.4f,0.45f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.29f, 0.3f, 0.6f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.428f, 0.42f, 0.35f, 0.06f));
		mSkyXOptions.RayleighMultiplier = 0.0043f;
		mSkyXOptions.MieMultiplier = 0.000525f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.554f, 0.52f, 0.47f);
		mSkyXOptions.Exposure = 1.8f;
		break;
		//! Beafourt = 8 : Gale, Fresh gale
	case 8:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.8f,0.9f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.35f,0.35f,0.39f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.28f, 0.32f, 0.58f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.435f, 0.36f, 0.4f, 0.07f));
		mSkyXOptions.RayleighMultiplier = 0.0046f;
		mSkyXOptions.MieMultiplier = 0.000475f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.553f, 0.52f, 0.48f);
		mSkyXOptions.Exposure = 1.4f;
		break;
		//! Beafourt = 9 : Strong gale
	case 9:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(0.9f,1.0f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.30f,0.30f,0.33f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.27f, 0.34f, 0.56f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.441f, 0.33f, 0.45f, 0.08f));
		mSkyXOptions.RayleighMultiplier = 0.0049f;
		mSkyXOptions.MieMultiplier = 0.000425f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.552f, 0.52f, 0.49f);
		mSkyXOptions.Exposure = 1.2f;
		break;
		//! Beafourt = 10 : Storm, Whole gale
	case 10:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(1.0f,1.0f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.25f,0.25f,0.27f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.26f, 0.36f, 0.54f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.445f, 0.31f, 0.5f, 0.09f));
		mSkyXOptions.RayleighMultiplier = 0.0052f;
		mSkyXOptions.MieMultiplier = 0.000375f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.551f, 0.52f, 0.50f);
		mSkyXOptions.Exposure = 1.1f;
		break;
		//! Beafourt = 11 : Violent storm
	case 11:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(1.0f,1.0f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.2f,0.2f,0.21f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.25f, 0.38f, 0.52f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.448f, 0.3f, 0.55f, 0.1f));
		mSkyXOptions.RayleighMultiplier = 0.0052f;
		mSkyXOptions.MieMultiplier = 0.000375f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.55f, 0.52f, 0.51f);
		mSkyXOptions.Exposure = 1.f;
		break;
		//! Beafourt = 12 : Hurricane force
	case 12:
		mSkyX->getVCloudsManager()->getVClouds()->setWheater(1.0f,1.0f,false);
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientColor(Ogre::Vector3(0.2f,0.2f,0.21f));
		mSkyX->getVCloudsManager()->getVClouds()->setLightResponse(Ogre::Vector4(0.24f, 0.4f, 0.5f, 0.1f));
		mSkyX->getVCloudsManager()->getVClouds()->setAmbientFactors(Ogre::Vector4(0.45f, 0.3f, 0.6f, 0.1f));
		mSkyXOptions.RayleighMultiplier = 0.0052f;
		mSkyXOptions.MieMultiplier = 0.000375f;
		mSkyXOptions.WaveLength = Ogre::Vector3(0.55f, 0.52f, 0.52f);
		mSkyXOptions.Exposure = 1.f;
		break;
	}
	mSkyX->getAtmosphereManager()->setOptions(mSkyXOptions);
}

void GraphicsMeteoManager::computeWind()
{
	// Direction (Hydrax compatibility)
	SkyX::VClouds::VClouds* vclouds = mSkyX->getVCloudsManager()->getVClouds();
	vclouds->setWindDirection(Ogre::Radian(180.f));
	// Wind speed
	float v = (mBeafourt+1.f)/13.f;
	mSkyX->getVCloudsManager()->setWindSpeed(3600.f * v);
	mWind = v*Ogre::Vector3(25.f,0.f,0.f);
	//SSS_APP->particlesManager()->rain()->wind(mWind);
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
}

void GraphicsMeteoManager::computeHydrax()
{
	/*
    Hydrax::Module::HydrOCL *mModule = (Hydrax::Module::HydrOCL*)mHydrax->getModule();
    Hydrax::Noise::HydrOCLNoise* mNoise = (Hydrax::Noise::HydrOCLNoise*)mModule->getNoise();
    Hydrax::Noise::HydrOCLPerlin::Options opts = mNoise->getOptions();
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
    } */

}

void GraphicsMeteoManager::updateEnvironmentLighting()
{
	Ogre::Vector3 lightDir = mSkyXController->getSunDirection();

	// Calculate current color gradients point
	float point = (lightDir.y + 1.0f) / 2.0f;
	mHydrax->setWaterColor(mWaterGradient.getColor(point));

	if(lightDir.y > 0.0f)
		lightDir *= -1.0f;
	Ogre::Vector3 sunPos = m_pCamera->getDerivedPosition() - lightDir*mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera)*0.1f;
	mHydrax->setSunPosition(sunPos);

	Ogre::Light *Light0 = m_pSceneMgr->getLight("Sun");

	Light0->setPosition(m_pCamera->getDerivedPosition() - lightDir*mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera)*0.02f);
	Light0->setDirection(lightDir);

	Ogre::Vector3 sunCol = mSunGradient.getColor(point);
	Light0->setSpecularColour(sunCol.x, sunCol.y, sunCol.z);
	Ogre::Vector3 diffuseCol = mDiffuseGradient.getColor(point);
	Light0->setDiffuseColour(diffuseCol.x, diffuseCol.y, diffuseCol.z);
	Ogre::Vector3 ambientCol = mAmbientGradient.getColor(point);
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(ambientCol.x, ambientCol.y, ambientCol.z, 1.f));
	mHydrax->setSunColor(sunCol);
}

void GraphicsMeteoManager::update(float dt)
{
	updateEnvironmentLighting();
	mHydrax->update(dt);
	// SkyX use hours
	mSkyX->update(dt);
}

void GraphicsMeteoManager::initHydrax()
{
	// Create Hydrax object
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
			Hydrax::Module::ProjectedGrid::Options(/*264 /*Generic one*/));	// Set our module
	mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));
	// Load all parameters from config file
	// Remarks: The config file must be in Hydrax resource group.
	// All parameters can be set/updated directly by code(Like previous versions),
	// but due to the high number of customizable parameters, Hydrax 0.4 allows save/load config files.
	mHydrax->loadCfg("Hydrax.hdx");
	// Create water
	mHydrax->create();
}

void GraphicsMeteoManager::initSkyX()
{

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
		mSkyX->getVCloudsManager()->create(mSkyX->getMeshManager()->getSkydomeRadius(m_pCamera));
	}

	mSkyX->getVCloudsManager()->setAutoupdate(false);

	mSkyX->setTimeMultiplier(1 / 3600.f);
	// Register as lighting listener in order to play sounds
	//mSkyX->getVCloudsManager()->getVClouds()->getLightningManager()->addListener(this);

	mHydrax->getRttManager()->addRttListener(new GraphicsHydraxRttListener(mSkyX,mHydrax));
}

unsigned int GraphicsMeteoManager::beafourt(unsigned int beaf)
{
	// New beafourt value (clamped)
	mBeafourt = beaf;
	if(mBeafourt < 0) mBeafourt=0;
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

void GraphicsMeteoManager::createMeteo()
{
	m_pCamera = m_pSceneMgr->getCamera("CamPricipal");
	//! Start Hydrax manager
	initHydrax();
	//! Start SkyX manager
	initSkyX();
	//! Setup initial beafourt number
	beafourt(mBeafourt);

	Ogre::ParticleSystem * ps;
	ps = m_pSceneMgr->createParticleSystem("Rain", "Rain/Droplets");
	m_pSceneMgr->getRootSceneNode()->attachObject(ps);
	ps->setDefaultDimensions(ps->getDefaultWidth(), ps->getDefaultHeight());

	Ogre::ParticleEmitter* partEmm = ps->getEmitter(0);
	partEmm->setEmissionRate((unsigned int)(1000.f));

}

} /* namespace Engine */
