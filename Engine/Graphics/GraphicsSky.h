/*
 * \file GraphicsSky.h
 *
 *  Created on: \date 25 sept. 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSSKY_H_
#define GRAPHICSSKY_H_

#include "SkyX.h"
#include "Logging/LogManager.h"

namespace Engine {

/*
 *
 */
class GraphicsSky {
public:
	GraphicsSky(Ogre::SceneManager *sm, Ogre::Root* m_pRoot, Ogre::RenderWindow* m_pRenderWnd);
	virtual ~GraphicsSky();

	void initSkyX();

	void update(float dt);

	SkyX::SkyX* getSkyX();

private:

	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Root* 				m_pRoot;
	Ogre::RenderWindow* 		m_pRenderWnd;

	SkyX::SkyX* mSkyX;
	SkyX::BasicController * mSkyXController;

	/// Water color gradient
	SkyX::ColorGradient mWaterGradient;
	/// Sun color gradient
	SkyX::ColorGradient mSunGradient;
	/// Diffuse color gradient
	SkyX::ColorGradient mDiffuseGradient;
	/// Ambient color gradient
	SkyX::ColorGradient mAmbientGradient;

};

} /* namespace Engine */

#endif /* GRAPHICSSKY_H_ */
