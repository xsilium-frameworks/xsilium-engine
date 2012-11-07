#ifndef LOGIN_STATE_H
#define LOGIN_STATE_H

#include "AppState.h"
#include "Authentification.h"
#include "string.h"
#include "ListOfMessage/ListOfMessage.h"

class Authentification;

class LoginState : public AppState
{
public:
    LoginState();

	DECLARE_APPSTATE_CLASS(LoginState)

	void enter();
	void createScene();
	void exit();

	bool PushConnexion(const CEGUI::EventArgs &e);
	bool CloseButton(const CEGUI::EventArgs &e);
	bool handleSubmit(const CEGUI::EventArgs& args);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);


	void setMessage(int message);
private:
	bool m_bQuit;
	CEGUI::Window* frame;
	CEGUI::Window* popupLogin;
	Authentification * auth;
	bool messageFlag;

protected:

    // convert an OIS mouse button into a CEGUI mouse button
    CEGUI::MouseButton convertOISButtonToCegui(int buttonID);
};


#endif /* LOGIN_STATE_H */
