/*
 * \file GestionnaireMouvement.h
 *
 *  Created on: \date 29 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIREMOUVEMENT_H_
#define GESTIONNAIREMOUVEMENT_H_

#include <OgreSceneNode.h>

#include "InputManager/InputManager.h"
#include "KeyboardMap/KeyboardMap.h"

#include "Entite/Entite.h"

/*
 *
 */
class GestionnaireMouvement {
public:
	GestionnaireMouvement(Ogre::Camera* cam);
	virtual ~GestionnaireMouvement();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved( const OIS::MouseEvent &event );
	bool mousePressed( const OIS::MouseEvent &event, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &event, OIS::MouseButtonID id );

	void update(double timeSinceLastFrame);

	void setEntities(Entite * entite);


private:
	void updateBody(double timeSinceLastFrame);

	void updateCamera(double timeSinceLastFrame);

	void updateCameraGoal(Ogre::Real deltaYaw, Ogre::Real deltaPitch, Ogre::Real deltaZoom);


	KeyboardMap * keyboardMap ;
	InputManager * inputManager;
    Ogre::Vector3 mKeyDirection;      // player's local intended direction based on keyboard
    Ogre::Vector3 mGoalDirection;     // actual intended direction in world-space
    Ogre::SceneNode* mCameraNode;
    Ogre::SceneNode* mCameraPivot;
    Ogre::SceneNode* mCameraGoal;
    Ogre::Real mPivotPitch;

    Entite * entite;
};

#endif /* GESTIONNAIREMOUVEMENT_H_ */
