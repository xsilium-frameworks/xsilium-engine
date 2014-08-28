/*
 * \file GraphicsObjetManager.h
 *
 *  Created on: \date 27 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSOBJETMANAGER_H_
#define GRAPHICSOBJETMANAGER_H_

#include "Graphics/GraphicsObjet.h"

namespace Engine {

/*
 *
 */
class GraphicsObjetManager {
public:
	GraphicsObjetManager();
	virtual ~GraphicsObjetManager();

	void createEntite(Event * event);
	//Entite * trouverEntite(std::string nom);

	void setSceneManager(Ogre::SceneManager* msceneMgr);

	void update(float time);

	void processEvent(Event * event);


private:
	std::vector<GraphicsObjet *> listOfEntite ;
	std::vector<GraphicsObjet *>::iterator entite ;

	Ogre::SceneManager* msceneMgr;
};

} /* namespace Engine */

#endif /* GRAPHICSOBJETMANAGER_H_ */
