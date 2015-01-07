/*
 * \file GraphicsEntiteManager.h
 *
 *  Created on: \date 4 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSENTITEMANAGER_H_
#define GRAPHICSENTITEMANAGER_H_

#include "Event/Event.h"
#include "GraphicsEntite.h"
#include "Graphics/GraphicsObjetManager.h"
#include <vector>

namespace Engine {

/*
 *
 */
class GraphicsEntiteManager {
public:
	GraphicsEntiteManager();
	virtual ~GraphicsEntiteManager();

	void createEntite(Event * event);
	GraphicsEntite * trouverEntite(int id);
	void deleteEntite(Ogre::String nom);

	void assigneObjet(Event * event);

	void setSceneManager(Ogre::SceneManager* msceneMgr);
	void setObjetManager(GraphicsObjetManager * graphicsObjetManager);

	void update(float time);

	void processEvent(Event * event);


private:
	std::vector<GraphicsEntite *> listOfEntite ;
	std::vector<GraphicsEntite *>::iterator entite ;

	Ogre::SceneManager* msceneMgr;
	GraphicsObjetManager * graphicsObjetManager;
};

} /* namespace Engine */

#endif /* GRAPHICSENTITEMANAGER_H_ */
