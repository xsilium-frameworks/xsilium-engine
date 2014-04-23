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

/*
 *
 */
class GestionnaireMeteo :  public Ogre::FrameListener {
public:
	GestionnaireMeteo(Ogre::SceneManager *sm);
	virtual ~GestionnaireMeteo();

	void createCiel(SkyX::SkyX* mSkyX);
	void createEau(const Ogre::String File);

    bool frameStarted(const Ogre::FrameEvent& evt);

    void updateEnvironmentLighting();


    void updateCouleur();

    void addDepthTechnique(Ogre::MaterialPtr mat);

private:
	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Camera*				m_pCamera;


    SkyX::SkyX* mSkyX ;
    SkyX::BasicController * mBasicController;
    Hydrax::Hydrax* mHydrax;

	// Color gradients
	SkyX::ColorGradient mWaterGradient,
		                mSunGradient,
						mAmbientGradient,
						mDiffuseGradient;

	unsigned int mBeafourt;
};

#endif /* GESTIONNAIREMETEO_H_ */
