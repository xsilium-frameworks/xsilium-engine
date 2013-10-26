/*
 * \file GestionnaireAuth.h
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIREAUTH_H_
#define GESTIONNAIREAUTH_H_

#include <sstream>
#include <cstring>

#include "StructurePacket/PacketAuth.h"
#include "InputManager/InputManager.h"

#include "Login/LoginState.h"

#include "Interface/GestionnaireInterface.h"
#include "Interface/GuiLogin.h"
#include "Interface/GuiErreur.h"
#include "Interface/GuiProgression.h"

#include "Compte/Compte.h"

#include "ModuleActif/ModuleActif.h"


#define AUTH_HOST "85.25.143.49"
//#define AUTH_HOST "127.0.0.1"
#define AUTH_PORT 60000


class LoginState;
class GuiLogin;
class GuiErreur;
class GuiProgression;

enum typeForAuth
{
	ID_CHALLENGE = 0,
	ID_REPONSE,
	ID_SEND_CANCEL,
	ID_ERREUR
};

enum erreurOfAuth
{
	ID_NOERROR = 0,
	ID_ERROR_PACKET_SIZE,
	ID_CONNECTION_BANNED,
	ID_INVALID_ACCOUNT_OR_PASSWORD,
	ID_COMPTE_BANNIE,
	ID_INVALID_IP,
	ID_ERROR_ETAPE
};


/*
 *
 */
class GestionnaireAuth : public OIS::KeyListener , public ModuleActif {

public:
	GestionnaireAuth(LoginState * loginState);
	virtual ~GestionnaireAuth();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	void run();

	void processPacket(ENetEvent * packet);

	bool initNetwork();

	void handleEtapeDeux(ENetEvent * packet);

	bool sendAuthentification();

	void updateNetwork(int event ,ENetEvent * packet);

	void cancelAuthentification();

	void quitAuthentification();

	void gestionnaireErreur(AUTHPACKET_ERROR * packetErreur );


	void setAuthentification();


protected:
	GuiLogin * guiLogin;
	GuiErreur * guiErreur;
	GuiProgression * guiProgression;

	Compte * compte;

	LoginState * loginState;


private:

	static void  threadAuthentification(void * arguments);

	KeyboardMap * keyboardMap ;
	InputManager * inputManager;

	GestionnaireInterface * gestionnaireInterface;

};

#endif /* GESTIONNAIREAUTH_H_ */
