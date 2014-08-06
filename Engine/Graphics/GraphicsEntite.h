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
#include "GraphicsObjet.h"
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

	void degainerArme();

	void update(double timeSinceLastFrame);

	void processEngine(Event * event);

	void addEquipement(Ogre::String nomObjet,Ogre::String fileMesh,Ogre::String emplacement);

	void runAnimation();
	void idleAnimation();

private:
	Ogre::String  nom;

	int  charHeight ;
	int  runSpeed ;
	double  turnSpeed ;

	Ogre::SceneManager* msceneMgr;
	Ogre::SceneNode* mBodyNode;
	Ogre::Entity* mBodyEnt;

	GraphicsAnimation * graphicsAnimation ;

	std::map<int,GraphicsObjet*> listOfObject;
	int countObjet;

	bool degainer;


};

} /* namespace Engine */

#endif /* GRAPHICSENTITE_H_ */
