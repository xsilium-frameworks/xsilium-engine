/*
 * \file GestionnaireAuth.h
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIREAUTH_H_
#define GESTIONNAIREAUTH_H_

#include "StructurePacket/PacketAuth.h"
#include "Shared/Network/Opcode.h"
#include "Network/NetworkManager.h"
#include "Network/NetworkListener.h"
#include <sstream>
#include <cstring>

#include "Interface/Interface.h"

#include "Compte/Compte.h"


/*
 *
 */
class GestionnaireAuth : public NetworkListener {

public:
	GestionnaireAuth(Interface * interface);
	virtual ~GestionnaireAuth();

	void handleEtapeDeux(ENetEvent * packet);

	bool sendAuthentification();

	void updateNetwork(int event ,ENetEvent * packet);


	void setLoginPwd(const char * user,const char * password);

private:
	NetworkManager * networkManager;
	ENetEvent eventAuth;
	Interface * interface;
	Compte * compte;

};

#endif /* GESTIONNAIREAUTH_H_ */
