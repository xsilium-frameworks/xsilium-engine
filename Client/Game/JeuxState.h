#ifndef JEUX_STATE_H
#define JEUX_STATE_H

#include "GameState/GameState.h"

#include"Chat/GestionnaireChat/GestionnaireChat.h"

#include "Entite/Perso/Personnage.h"
#include "Entite/GestionnaireEntite.h"

#include "Interface/GestionnaireInterface.h"
#include "DotSceneLoader/DotSceneLoader.h"

class JeuxState :public OIS::KeyListener, public GameState
{
public:
	JeuxState();
	virtual ~JeuxState();

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();

    void buildGUI();

	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);


private:

	InputManager * 				inputManager;
    DotSceneLoader* 			m_Loader;

    GestionnaireChat * gestionnaireChat;
	KeyboardMap * keyboardMap ;

	GestionnaireEntite * gestionnaireEntite;

	Personnage * perso;
	Personnage * perso2;

	GestionnaireMouvement * gestionnaireMouvement;



};



#endif
