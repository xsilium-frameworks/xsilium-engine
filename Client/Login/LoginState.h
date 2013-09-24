#ifndef LOGIN_STATE_H
#define LOGIN_STATE_H

#include "GameState/GameState.h"
#include "Authentification/GestionnaireAuth.h"
#include "string.h"

class GestionnaireAuth;

class LoginState : public GameState
{
public:
    LoginState();
    virtual ~LoginState();

	void enter();
	void createScene();

	void exit();

	bool PushConnexion(const CEGUI::EventArgs &e);
	bool CloseButton(const CEGUI::EventArgs &e);
	bool handleSubmit(const CEGUI::EventArgs& args);

	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);

	void setExit();

private:
	bool m_bQuit;
	GestionnaireAuth * gestionnaireAuth;

};


#endif /* LOGIN_STATE_H */
