/*
 * \file GraphicsWater.h
 *
 *  Created on: \date 25 sept. 2014
 *      Author: \author joda xelfe
 *  \brief : Fichier d'en tête de la classe GraphicsWater
 */
#ifndef GRAPHICSWATER_H_
#define GRAPHICSWATER_H_

#include "OgreTerrainGroup.h"
#include "Graphics/GraphicsHydraxRttListener.h"
#include "Logging/LogManager.h"

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

	void update(float dt);

private:

	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Root* 				m_pRoot;
	Ogre::RenderWindow* 		m_pRenderWnd;
	Ogre::Camera*				m_pCamera;
	Ogre::TerrainGroup*			m_pTerrainGroup;
	Hydrax::Hydrax*				m_pHydrax;
};

} /* namespace Engine */

#endif /* GRAPHICSWATER_H_ */
