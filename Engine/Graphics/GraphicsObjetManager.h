/*
 * \file GraphicsObjetManager.h
 *
 *  Created on: \date 27 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSOBJETMANAGER_H_
#define GRAPHICSOBJETMANAGER_H_

#include "Graphics/GraphicsObjet.h"
#include "Event/Event.h"
#include "Singleton/Singleton.h"

namespace Engine {

/*
 *
 */
class GraphicsObjetManager : public Singleton<GraphicsObjetManager> {
	friend class Singleton < GraphicsObjetManager > ;

public:
	GraphicsObjetManager();
	virtual ~GraphicsObjetManager();

	void createObjet(Event * event);
	GraphicsObjet * trouverObjet(Ogre::String nom);
	void deleteObjet(Ogre::String nom);

	void setSceneManager(Ogre::SceneManager* msceneMgr);

	void update(float time);

	void processEvent(Event * event);


private:
	std::vector<GraphicsObjet *> listOfObjet ;
	std::vector<GraphicsObjet *>::iterator objet ;

	Ogre::SceneManager* msceneMgr;
};

} /* namespace Engine */

#endif /* GRAPHICSOBJETMANAGER_H_ */
