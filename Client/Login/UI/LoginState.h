#ifndef LOGIN_STATE_H
#define LOGIN_STATE_H

#include "GameState/GameState.h"
#include "Authentification.h"
#include "string.h"
#include "ListOfMessage/ListOfMessage.h"


class Authentification;

enum eventType
{
	MESSAGE = 0,
	PROGRESSION
};

class LoginState : public OIS::KeyListener,public GameState
{
public:
    LoginState();

    DECLARE_GAMESTATE_CLASS(LoginState)

	void enter();
	void createScene();
	void exit();

	bool PushConnexion(const CEGUI::EventArgs &e);
	bool CloseButton(const CEGUI::EventArgs &e);
	bool handleSubmit(const CEGUI::EventArgs& args);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	void update(double timeSinceLastFrame);


	void setMessage(int typeMessage,int message);
	void setProgression(int progression);

	void processMessage(Event * event);
	void processProgression(Event * event);

private:
	bool m_bQuit;
	CEGUI::Window* frame;
	CEGUI::Window* popupLogin;
	CEGUI::Window* popupProg;
	Authentification * auth;
	InputManager * inputManager;
	bool messageFlag;
};


#endif /* LOGIN_STATE_H */
