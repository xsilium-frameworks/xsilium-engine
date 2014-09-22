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

#include "Engine/Network/NetworkListener.h"
#include "StructurePacket/PacketAuth.h"
#include "Compte/Compte.h"
#include "Gui/GuiAuth.h"



#define AUTH_HOST "85.25.143.49"
//#define AUTH_HOST "127.0.0.1"
#define AUTH_PORT 60000

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
class GestionnaireAuth : public Engine::NetworkListener {

public:
	GestionnaireAuth();
	virtual ~GestionnaireAuth();

	void run();

	void processPacket(ENetEvent * packet);

	bool initNetwork();

	void handleEtapeDeux(ENetEvent * packet);

	bool sendAuthentification();

	void cancelAuthentification();

	void gestionnaireErreur(AUTHPACKET_ERROR * packetErreur );

	void setAuthentification(Event * event);

	void processEvent(Event * event);


private:
	Compte * compte;


};

#endif /* GESTIONNAIREAUTH_H_ */
