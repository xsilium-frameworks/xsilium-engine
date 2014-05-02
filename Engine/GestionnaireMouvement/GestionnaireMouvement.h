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

#include "XsiliumFramework.h"

#include "Singleton/Singleton.h"

#define CAM_HEIGHT 0.5

/*
 *
 */
class GestionnaireMouvement : public OIS::KeyListener,public OIS::MouseListener, public Ogre::FrameListener, public xsilium::Singleton<GestionnaireMouvement> {

	friend class xsilium::Singleton<GestionnaireMouvement>;


public:
	GestionnaireMouvement();
	virtual ~GestionnaireMouvement();

	void setCamera(Ogre::Camera* cam);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved( const OIS::MouseEvent &event );
	bool mousePressed( const OIS::MouseEvent &event, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &event, OIS::MouseButtonID id );

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

	void setEntities(Entite * entite);

	void activeDeplacement();
	void desactiveDeplacement();


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
    Ogre::SceneManager* sceneMgr;
    bool clickgauche;
    bool deplacement;
};

#endif /* GESTIONNAIREMOUVEMENT_H_ */
