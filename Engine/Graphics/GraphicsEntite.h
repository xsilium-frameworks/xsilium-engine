/*
 * \file GraphicsEntite.h
 *
 *  Created on: \date 4 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSENTITE_H_
#define GRAPHICSENTITE_H_

#include <Ogre.h>
#include "GraphicsAnimation.h"
#include "Event/Event.h"

namespace Engine {

/*
 *
 */
class GraphicsEntite {
public:
	GraphicsEntite();
	virtual ~GraphicsEntite();

	void initEntite(Ogre::SceneManager* sceneMgr,Ogre::String nom,Ogre::String fileMesh);

	void setCharHeight(int charHeight);
	void setRunSpeed(int runSpeed);
	void setTurnSpeed(double turnSpeed);

	void setPosition(Ogre::Vector3 position);

	Ogre::Vector3 getWorldPosition ();
	Ogre::String * getNom();

	void degainerArme();

	void update(double timeSinceLastFrame);

	void processEngine(Event * event);

	void addEquipement(Ogre::Entity * objet,Ogre::String emplacement);
	void deleteEquipement(Ogre::String emplacement);

	void runAnimation();
	void idleAnimation();

private:
	Ogre::String  nom;

	int  charHeight ;
	int  runSpeed ;
	double  turnSpeed ;

	Ogre::SceneManager* msceneMgr;
	Ogre::SceneNode *mMainNode; // Main character node
	Ogre::Entity* mBodyEnt;

	GraphicsAnimation * graphicsAnimation ;

	std::map<Ogre::String,Ogre::Entity*> listOfObject;

	bool degainer;


};

} /* namespace Engine */

#endif /* GRAPHICSENTITE_H_ */
