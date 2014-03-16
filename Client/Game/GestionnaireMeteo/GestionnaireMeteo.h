/*
 * \file GestionnaireMeteo.h
 *
 *  Created on: \date 14 févr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIREMETEO_H_
#define GESTIONNAIREMETEO_H_

#include "XsiliumFramework.h"
#include <OgreMaterialManager.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>

#include "HydraxRttListener/HydraxRttListener.h"


// Shadow config struct
struct ShadowConfig
{
	bool Enable;
	int  Size;
    
	ShadowConfig(const bool& Enable_, const int& Size_)
    : Enable(Enable_)
    , Size(Size_)
	{
	}
};

// Shadow mode
enum ShadowMode
{
	SM_NONE = 0,
	SM_HIGH = 1
};

/*
 *
 */
class GestionnaireMeteo :  public Ogre::FrameListener {
public:
	GestionnaireMeteo(Ogre::SceneManager *sm, Ogre::Camera *c,SkyX::SkyX* mSkyX);
	virtual ~GestionnaireMeteo();

	void create();

    bool frameStarted(const Ogre::FrameEvent& evt);

    void updateEnvironmentLighting();
    void updateShadowFarDistance();
    
    void setShadowMode(Ogre::SceneManager *sm, const ShadowMode& smode);

private:
	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Camera*				m_pCamera;


    SkyX::SkyX* mSkyX ;
    SkyX::BasicController * mBasicController;
    Hydrax::Hydrax* mHydrax;


	// Color gradients
	SkyX::ColorGradient mWaterGradient,
		                mSunGradient,
						mAmbientGradient;

	Ogre::Real mLastPositionLength;
    
    // Current shadow mode
    int mShadowMode ;
    // To disable shadows in night
    bool mForceDisableShadows ;

};

#endif /* GESTIONNAIREMETEO_H_ */
