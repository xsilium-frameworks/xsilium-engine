#ifndef LOGIN_STATE_H
#define LOGIN_STATE_H

#include "Authentification/GestionnaireAuth.h"
#include "string.h"

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

private:
	GestionnaireAuth * gestionnaireAuth;

};


#endif /* LOGIN_STATE_H */
