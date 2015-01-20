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
#include "Graphics/GraphicsCamera.h"
#include "Event/Event.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsEntite.h"

namespace Engine {

enum AnimEntiteID
{
	ANIM_IDLE_BASE,
	ANIM_IDLE_TOP,

	ANIM_RUN_BASE,
	ANIM_RUN_TOP,

	ANIM_HANDS_CLOSED,
	ANIM_HANDS_RELAXED,

	ANIM_DRAW_SWORDS,

	ANIM_SLICE_VERTICAL,
	ANIM_SLICE_HORIZONTAL,

	ANIM_JUMP_START,
	ANIM_JUMP_LOOP,
	ANIM_JUMP_END
};

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
	void setID(int id);
	int getID();

	void setPosition(Ogre::Vector3 position);

	Ogre::Vector3 getWorldPosition ();
	Ogre::String * getNom();

	void degainerArme();

	void update(double timeSinceLastFrame);

	void updateAnimation(double timeSinceLastFrame);

	void processEvent(Event * event);

	void addEquipement(Ogre::Entity * objet,Ogre::String emplacement);
	void deleteEquipement(Ogre::String emplacement);

	void deplaceEntite(Ogre::Vector3 direction );

	void setOrientation(Ogre::Quaternion orientation);

private:
	Ogre::String  nom;
	int id;

	int  charHeight ;
	int  runSpeed ;
	double  turnSpeed ;

	Ogre::SceneManager* msceneMgr;
	Ogre::SceneNode *mMainNode; // Main character node
	Ogre::Entity* mBodyEnt;

	GraphicsAnimation * graphicsAnimation ;

	std::map<Ogre::String,Ogre::Entity*> listOfObject;

	bool degainer;

	Ogre::Vector3 direction;

	Ogre::String animNames[12];

	bool mMoving;
	bool mIsFalling;

	PhysicsEntite * physicsEntite;

};

} /* namespace Engine */

#endif /* GRAPHICSENTITE_H_ */
