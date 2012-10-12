#ifndef LOGIN_STATE_H
#define LOGIN_STATE_H

#include "AppState.h"
#include "Authentification/Authentification.h"

class LoginState : public AppState
{
public:
    LoginState();

	DECLARE_APPSTATE_CLASS(LoginState)

	void enter();
	void createScene();
	void exit();

	bool PushConnexion(const CEGUI::EventArgs &e);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);


//	void buttonHit(OgreBites::Button* button);

	void update(double timeSinceLastFrame);

private:
	bool m_bQuit;
	bool handleSubmit(const CEGUI::EventArgs& args);

protected:
	CEGUI::Window* fldUsername;
	Authentification * auth;

    // convert an OIS mouse button into a CEGUI mouse button
    CEGUI::MouseButton convertOISButtonToCegui(int buttonID);
};


#endif /* LOGIN_STATE_H */
