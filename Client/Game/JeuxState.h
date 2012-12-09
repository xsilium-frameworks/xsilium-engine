#ifndef JEUX_STATE_H
#define JEUX_STATE_H

#include "GameState/GameState.h"

#include "DotSceneLoader.h"

#include"Console/Console.h"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>

class JeuxState :public OIS::KeyListener,public GameState
{
public:
	JeuxState();

	DECLARE_GAMESTATE_CLASS(JeuxState)

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();

	void moveCamera();
	void getInput();

//    void buildGUI();
//    void itemSelected(OgreBites::SelectMenu* menu);

	void update(double timeSinceLastFrame);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

private:

	bool						m_bQuit;

	Ogre::Vector3				m_TranslateVector;
	Ogre::Real					m_MoveSpeed;
	Ogre::Degree				m_RotateSpeed;
	float						m_MoveScale;
	Ogre::Degree				m_RotScale;

	Ogre::RaySceneQuery*		m_pRSQ;
	Ogre::SceneNode*			m_pCurrentObject;
	Ogre::Entity*				m_pCurrentEntity;
	bool						m_bSettingsMode;

	InputManager * inputManager;

};



#endif
