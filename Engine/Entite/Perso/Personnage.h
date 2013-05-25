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
#include <OgreEntity.h>

#include "Entite/Entite.h"
#include "Entite/GestionnaireAnimation/Animation.h"
#include "XsiliumFramework.h"

#include "GestionnaireMouvement/MouvementPersonnage.h"

/*
 *
 */
class Personnage : public Entite , public Ogre::FrameListener {
public:
	Personnage(Ogre::Camera* cam);
	virtual ~Personnage();

protected:

	void setupBody(Ogre::SceneManager* sceneMgr);
	void setupCamera(Ogre::Camera* cam);

	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);


	Ogre::SceneNode* mBodyNode;
	Ogre::Entity* mBodyEnt;

	Ogre::SceneManager* sceneManager;

	Ogre::SceneNode* mCameraPivot;
	Ogre::SceneNode* mCameraGoal;
	Ogre::SceneNode* mCameraNode;

	Ogre::AnimationState* mAnims1;
	Ogre::AnimationState* mAnims2;

private:
	MouvementPersonnage * mouvementPersonnage ;
	Animation * animation ;

};

#endif /* PERSONNAGE_H_ */
