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

#include <Network/NetworkManager.h>
#include "Compte/Compte.h"
#include "Gui/GuiAuth.h"



#define AUTH_HOST "151.80.162.102"
#define AUTH_PORT 60000

enum typeForAuth
{
	ID_CHALLENGE = 0,
	ID_REPONSE,
	ID_REALMSLIST,
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
class GestionnaireAuth : public Engine::NetworkListener {

public:
	GestionnaireAuth();
	virtual ~GestionnaireAuth();

	void run();

	void processPacket(Engine::MessagePacket * messagePacket);

	bool initNetwork();

	void handleEtapeDeux(Engine::MessagePacket * messagePacket);

	bool sendAuthentification();

	void cancelAuthentification();

	void gestionnaireErreur(Engine::MessagePacket * messagePacket);

	void setAuthentification(Event * event);

	void processEvent(Event * event);

	void getRealmslist();


private:
	Compte * compte;
	GuiAuth * guiAuth;
	Engine::NetworkManager * networkManager;


};

#endif /* GESTIONNAIREAUTH_H_ */
