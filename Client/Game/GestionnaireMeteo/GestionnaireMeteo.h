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

#include "SkyX.h"
#include "Hydrax.h"
#include "Noise/Perlin/Perlin.h"
#include "Modules/ProjectedGrid/ProjectedGrid.h"

/*
 *
 */
class GestionnaireMeteo :  public Ogre::FrameListener {
public:
	GestionnaireMeteo(Ogre::SceneManager *sm, Ogre::Camera *c);
	virtual ~GestionnaireMeteo();

	void create();

    bool frameStarted(const Ogre::FrameEvent& evt);

private:
	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Camera*				m_pCamera;


    SkyX::SkyX* mSkyX ;
    SkyX::BasicController* mBasicController;
    Hydrax::Hydrax* mHydrax;
};

#endif /* GESTIONNAIREMETEO_H_ */
