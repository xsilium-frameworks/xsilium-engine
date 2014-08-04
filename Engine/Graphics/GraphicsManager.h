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

	Ogre::RenderWindow* getRenderWindow();

	void processEvent(Event * event);

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

private:
	Ogre::String m_SceneFile;

	Ogre::String mResourcePath ;

	Ogre::RenderSystem*			m_pRenderSystem;
	Ogre::RenderWindow*			m_pRenderWnd;
	Ogre::Root*					m_pRoot;

	Ogre::String fenetreName;
	bool sauvegardeParam;

	GraphicsEntiteManager * graphicsEntiteManager;

};

} /* namespace Engine */

#endif /* GRAPHICSMANAGER_H_ */
