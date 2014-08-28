/*
 * \file GraphicsEntite.h
 *
 *  Created on: \date 4 aožt 2014
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

	Ogre::Vector3 getWorldPosition ();

	void degainerArme();

	void update(double timeSinceLastFrame);

	void processEngine(Event * event);

	void addEquipement(Ogre::Entity * objet,Ogre::String emplacement);

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

	bool degainer;


};

} /* namespace Engine */

#endif /* GRAPHICSENTITE_H_ */
