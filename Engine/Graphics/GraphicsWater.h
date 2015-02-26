/*
 * \file GraphicsWater.h
 *
 *  Created on: \date 25 sept. 2014
 *      Author: \author joda xelfe
 *  \brief : Fichier d'en t�te de la classe GraphicsWater
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
class GraphicsWater : public Singleton<GraphicsWater> {
	friend class Singleton < GraphicsWater > ;
public:
	GraphicsWater();
	virtual ~GraphicsWater();

	void init(Ogre::SceneManager *sm, Ogre::Root* m_pRoot, Ogre::RenderWindow* m_pRenderWnd,Ogre::Camera* m_pCamera);

	void update(float dt);

	void addRttListener(GraphicsHydraxRttListener * graphicsHydraxRttListener);

	Hydrax::Hydrax* getHydraX();

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
