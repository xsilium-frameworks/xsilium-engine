/*
 * \file Authentification.h
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef AUTHENTIFICATION_H_
#define AUTHENTIFICATION_H_

#include "StructurePacket/StructurePacket.h"
//#include "Opcode/opcode.h"
#include "Network/NetworkManager.h"
#include "Network/NetworkListener.h"
#include "Singleton/Singleton.h"
#include <sstream>
#include <cstring>

struct cClient
	{
	    uint16_t  build;
	    uint8_t   platform[4];
	    uint8_t   os[4];
	    uint8_t   country[4];
	    const char * login;
	    const char * password;
	    uint8_t etape;
	};

enum Opcode
{
	ID_CONNEXION = 0,
	ID_DECONEXION,
    ID_SEND_USER,
    ID_SEND_CHALLENGE,
    ID_SEND_REPONSE,
    ID_SEND_VALIDATION,
    ID_GET_ROYAUME,
    ID_SEND_ROYAUME,
    ID_CONNECTION_BANNED,
    ID_INVALID_PASSWORD,
    ID_COMPTE_BANNIE
};

enum typerequete
{
   XSILIUM_AUTH = 0,
   XSILIUM_ALL
};


/*
 *
 */
class Authentification : public Singleton<Authentification> , public NetworkListener {

	friend class Singleton<Authentification>;


public:
	Authentification();
	virtual ~Authentification();

	bool InitialisationAuth();

	void handleReturn(ENetEvent * packet);

	bool sendAuthentification();

	void updateNetwork(int event ,ENetEvent * packet);


	void setLoginPwd(const char * user,const char * password);

private:
	NetworkManager * networkManager;
	ENetEvent eventAuth;
	cClient client;

};

#endif /* AUTHENTIFICATION_H_ */
