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

namespace Engine {

/*
 *
 */
class GraphicsManager : public EngineListenner {
public:
	GraphicsManager();
	virtual ~GraphicsManager();

	void setParamettreOgre(std::string key, std::string valeur);

	void createWindow();


	void loadRessource();

	Ogre::RenderWindow* getRenderWindow();

	void processEvent(Event * event);

private:
	Ogre::String m_SceneFile;

	Ogre::String mResourcePath ;

	Ogre::RenderSystem*			m_pRenderSystem;
	Ogre::RenderWindow*			m_pRenderWnd;
	Ogre::Root*					m_pRoot;

	Ogre::String fenetreName;
	bool sauvegardeParam;

};

} /* namespace Engine */

#endif /* GRAPHICSMANAGER_H_ */
