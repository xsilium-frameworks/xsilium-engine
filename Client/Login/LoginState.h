#ifndef LOGIN_STATE_H
#define LOGIN_STATE_H

#include "Authentification/GestionnaireAuth.h"
#include "GameState/GameState.h"


class LoginState : public GameState
{
public:
    LoginState();
    virtual ~LoginState();

	void enter();
	void createScene();

	void exit();

	void update(double timeSinceLastFrame);

	void processEvent(Event * event);

private:
	GestionnaireAuth * gestionnaireAuth;


};


#endif /* LOGIN_STATE_H */
