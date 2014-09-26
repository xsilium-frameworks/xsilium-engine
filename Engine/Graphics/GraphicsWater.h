/*
 * \file GraphicsWater.h
 *
 *  Created on: \date 25 sept. 2014
 *      Author: \author joda xelfe
 *  \brief :
 */
#ifndef GRAPHICSWATER_H_
#define GRAPHICSWATER_H_

#include "Hydrax.h"
#include "Noise/Perlin/Perlin.h"
#include "Modules/ProjectedGrid/ProjectedGrid.h"

namespace Engine {

/*
 *
 */
class GraphicsWater {
public:
	GraphicsWater(Ogre::SceneManager *sm, Ogre::Root* m_pRoot, Ogre::RenderWindow* m_pRenderWnd);
	virtual ~GraphicsWater();

	void initHydrax();

private:
	Hydrax::Hydrax* mHydrax;

	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Root* 				m_pRoot;
	Ogre::RenderWindow* 		m_pRenderWnd;
	Ogre::Camera*				m_pCamera;
};

} /* namespace Engine */

#endif /* GRAPHICSWATER_H_ */
