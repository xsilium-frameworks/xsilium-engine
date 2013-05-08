/*
 * \file Personnage.h
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef PERSONNAGE_H_
#define PERSONNAGE_H_

#include <OgreSceneManager.h>
#include <OgreRibbonTrail.h>
#include <OgreEntity.h>

#include "Entite/Entite.h"

#include "GestionnaireMouvement/MouvementPersonnage.h"

/*
 *
 */
class Personnage : public Entite {
public:
	Personnage(Ogre::Camera* cam);
	virtual ~Personnage();

	void update(double timeSinceLastFrame);

protected:

	void setupBody(Ogre::SceneManager* sceneMgr);
	void setupCamera(Ogre::Camera* cam);


	Ogre::SceneNode* mBodyNode;
	Ogre::Entity* mBodyEnt;

	Ogre::SceneNode* mCameraPivot;
	Ogre::SceneNode* mCameraGoal;
	Ogre::SceneNode* mCameraNode;

private:
	MouvementPersonnage * mouvementPersonnage ;

};

#endif /* PERSONNAGE_H_ */
