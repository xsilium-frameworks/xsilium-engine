/*
 * \file MouvementPersonnage.h
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef MOUVEMENTPERSONNAGE_H_
#define MOUVEMENTPERSONNAGE_H_

#include <OgreSceneNode.h>


#include "InputManager/InputManager.h"
#include "KeyboardMap/KeyboardMap.h"

#define NUM_ANIMS 13           // number of animations the character has
#define CHAR_HEIGHT 5          // height of character's center of mass above ground
#define CAM_HEIGHT 2           // height of camera above character's center of mass
#define RUN_SPEED 17           // character running speed in units per second
#define TURN_SPEED 500.0f      // character turning in degrees per second
#define ANIM_FADE_SPEED 7.5f   // animation crossfade speed in % of full weight per second
#define JUMP_ACCEL 30.0f       // character jump acceleration in upward units per squared second
#define GRAVITY 90.0f          // gravity in downward units per squared second


/*
 *
 */
class MouvementPersonnage : public OIS::KeyListener,public OIS::MouseListener {
public:
	MouvementPersonnage(Ogre::SceneNode* mBodyNode,Ogre::SceneNode* mCameraNode,Ogre::SceneNode* mCameraPivot,Ogre::SceneNode* mCameraGoal);
	virtual ~MouvementPersonnage();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

    bool mouseMoved( const OIS::MouseEvent &event );
    bool mousePressed( const OIS::MouseEvent &event, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &event, OIS::MouseButtonID id );

    void update(double timeSinceLastFrame);


private:

    void updateBody(double timeSinceLastFrame);

    void updateCamera(double timeSinceLastFrame);


    KeyboardMap * keyboardMap ;
    InputManager * inputManager;

    Ogre::Vector3 mKeyDirection;      // player's local intended direction based on keyboard
    Ogre::Vector3 mGoalDirection;     // actual intended direction in world-space
    Ogre::SceneNode* mBodyNode;
    Ogre::SceneNode* mCameraNode;
    Ogre::SceneNode* mCameraPivot;
    Ogre::SceneNode* mCameraGoal;

};

#endif /* MOUVEMENTPERSONNAGE_H_ */
