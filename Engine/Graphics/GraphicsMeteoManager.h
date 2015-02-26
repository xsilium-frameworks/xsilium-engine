/*
 * \file GraphicsMeteoManager.h
 *
 *  Created on: \date 26 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSMETEOMANAGER_H_
#define GRAPHICSMETEOMANAGER_H_

#include "GraphicsHydraxRttListener.h"
#include "GraphicsWater.h"
#include "GraphicsSky.h"

namespace Engine {

/*
 *
 */
class GraphicsMeteoManager {
public:
	GraphicsMeteoManager(Ogre::SceneManager *sm, Ogre::Root* m_pRoot , Ogre::RenderWindow* m_pRenderWnd,Ogre::Camera* m_pCamera);
	virtual ~GraphicsMeteoManager();

	void init();

	/** Set beafourt number.
	 * @param beaf Beafourt number.
	 * @return None.
	 * @note Beafourt njumber will be clamped between 0-12.
	 */
	void beafourt(unsigned int beaf);
	/** Get active beafourt number.
	 * @return Beafourt number.
	 */
	unsigned int beafourt(){return mBeafourt;}

	/** Set rain state.
	 * @param flag true if rain must be activated, false
	 * otherwise.
	 * @warning Rain level depends on beafourt number, so
	 * if beafourt number is too low rain will undetectable.
	 */
	void rain(bool flag);
	/** Get rain state.
	 * @return true if rain is activated, false otherwise.
	 */
	bool rain(){return mRain;}

	/** Set storm state.
	 * @param flag true if storm must be activated, false
	 * otherwise.
	 * @warning Lightings level depends on beafourt number, so
	 * if beafourt number is too low rain will undetectable.
	 */
	void storm(bool flag);
	/** Get storm state.
	 * @return true if storm is activated, false otherwise.
	 */
	bool storm(){return mStorm;}

	/** Get wind vector.
	 * @return Wind vector (length is the wind speed).
	 */
	Ogre::Vector3 wind(){return mWind;}

	/** Update method, that must be called every frame.
	 * @param dt Time elapsed between frames (Time
	 * multiplier will be imposed into the function).
	 */
	void update(float dt);

	/** Method called authomatically when a lighting is generated.
	 * @param l Lightning that has been added
	 */
	//void lightningAdded(SkyX::VClouds::Lightning* l);


protected:

	/** Setup the lighting according with setup.
	 */
	void updateEnvironmentLighting();
	void updateShadowFarDistance();

private:
	/** Compute color gradients, function of beafourt number.
	 */
	void computeColours();
	/** Compute SkyX environment parameters (Beafourt dependent).
	 */
	void computeSkyX();
	/** Compute wind (Beafourt dependent).
	 */
	void computeWind();
	/** Compute rain parameters.
	 */
	void computeRain();
	/** Compute storm parameters.
	 */
	void computeStorm();
	/** Compute Hydrax environment parameters (Beafourt dependent).
	 */
	void computeHydrax();
	/** Set system waves.
	 * @param n Number of waves to add.
	 * @param A Waves amplitude bounds [m].
	 * @param T Waves period bounds [s].
	 * @param varDir Direction dispersion.
	 * @param varP Waves period variance [rad].
	 * @note Default waves direction is [1.0,0.0]
	 */
	void setWaves(unsigned int n, Ogre::Vector2 A, Ogre::Vector2 T, Ogre::Vector2 varDir=Ogre::Vector2(0.f,0.2f), float varP=2.f);

	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Root* 				m_pRoot ;
	Ogre::RenderWindow* 		m_pRenderWnd ;
	Ogre::Camera*				m_pCamera;

	GraphicsSky * graphicsSky;
	GraphicsWater * graphicsWater;


	/// Sun color gradient
	SkyX::ColorGradient mSunGradient;
	/// Diffuse color gradient
	SkyX::ColorGradient mDiffuseGradient;
	/// Ambient color gradient
	SkyX::ColorGradient mAmbientGradient;

	unsigned int mBeafourt;
	/// Water color gradient
	SkyX::ColorGradient mWaterGradient;
	/// Number of waves (added to Hydrax)
	unsigned int nWaves;
	/// Rain active/unactive
	bool mRain;
	/// Storm active/unactive
	bool mStorm;
	/// Wind vector
	Ogre::Vector3 mWind;

	Ogre::Real mLastPositionLength;

};

} /* namespace Engine */

#endif /* GRAPHICSMETEOMANAGER_H_ */
