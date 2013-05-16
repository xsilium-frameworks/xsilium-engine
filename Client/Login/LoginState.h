#ifndef LOGIN_STATE_H
#define LOGIN_STATE_H

#include "GameState/GameState.h"
#include "Authentification/Interface/Authentification.h"
#include "string.h"


class LoginState : public OIS::KeyListener,public GameState
{
public:
    LoginState();

    DECLARE_GAMESTATE_CLASS(LoginState)

	void enter();
	void createScene();

    void buildGUI();

	void exit();

	bool PushConnexion(const CEGUI::EventArgs &e);
	bool CloseButton(const CEGUI::EventArgs &e);
	bool handleSubmit(const CEGUI::EventArgs& args);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);

	void initialisationNetwork();

private:
	bool m_bQuit;
	Authentification * auth;
	InputManager * inputManager;
};


#endif /* LOGIN_STATE_H */
