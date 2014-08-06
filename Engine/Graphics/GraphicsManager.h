/*
 * \file GraphicsManager.h
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSMANAGER_H_
#define GRAPHICSMANAGER_H_

#include "Engine/Engine.h"
#include "Graphics/GraphicsEntiteManager.h"
#include "Graphics/GraphicsSceneLoader.h"

namespace Engine {

/*
 *
 */
class GraphicsManager : public EngineListenner , public Ogre::FrameListener {
public:
	GraphicsManager();
	virtual ~GraphicsManager();

	void initOgre();

	void setParamettreOgre(Ogre::String key, Ogre::String valeur);

	void createWindow();

	void loadRessource();

	void loadScene(Event * event);

	Ogre::RenderWindow* getRenderWindow();

	void processEvent(Event * event);

	void shutdown();

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

private:
	Ogre::String m_SceneFile;

	Ogre::String mResourcePath ;

	Ogre::RenderSystem*			m_pRenderSystem;
	Ogre::RenderWindow*			m_pRenderWnd;
	Ogre::Root*					m_pRoot;
	Ogre::SceneManager*			m_pSceneMgr;

	Ogre::String fenetreName;
	bool sauvegardeParam;

	GraphicsEntiteManager * graphicsEntiteManager;
	GraphicsSceneLoader * graphicsSceneLoader;

};

} /* namespace Engine */

#endif /* GRAPHICSMANAGER_H_ */
