/*
 * \file Authentification.h
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef AUTHENTIFICATION_H_
#define AUTHENTIFICATION_H_

#include "StructurePacket/PacketAuth.h"
#include "Shared/Network/Opcode.h"
#include "Network/NetworkManager.h"
#include "Network/NetworkListener.h"
#include <sstream>
#include <cstring>
#include "Login/LoginState.h"

#include "Compte/Compte.h"

class LoginState;


/*
 *
 */
class Authentification : public NetworkListener {

public:
	Authentification(LoginState *login);
	virtual ~Authentification();

	void InitialisationAuth();

	void handleEtapeDeux(ENetEvent * packet);

	bool sendAuthentification();

	void updateNetwork(int event ,ENetEvent * packet);


	void setLoginPwd(const char * user,const char * password);

private:
	NetworkManager * networkManager;
	LoginState *login;
	ENetEvent eventAuth;
	Compte * compte;

};

#endif /* AUTHENTIFICATION_H_ */
