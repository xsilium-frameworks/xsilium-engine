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
class GraphicsSky: public Singleton<GraphicsSky> {
	friend class Singleton < GraphicsSky > ;
public:
	GraphicsSky();
	virtual ~GraphicsSky();

	void init(Ogre::SceneManager *sm, Ogre::Root* m_pRoot, Ogre::RenderWindow* m_pRenderWnd,Ogre::Camera* m_pCamera);

	void update(float dt);

	SkyX::SkyX* getSkyX();
	SkyX::BasicController * getBasicController();

private:

	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Root* 				m_pRoot;
	Ogre::RenderWindow* 		m_pRenderWnd;
	Ogre::Camera*				m_pCamera;

	SkyX::SkyX* mSkyX;
	SkyX::BasicController * mSkyXController;


};

} /* namespace Engine */

#endif /* GRAPHICSSKY_H_ */
