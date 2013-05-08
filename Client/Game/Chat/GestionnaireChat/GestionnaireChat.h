/*
 * \file GestionnaireChat.h
 *
 *  Created on: \date 16 févr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIRECHAT_H_
#define GESTIONNAIRECHAT_H_

#include "Network/NetworkManager.h"
#include "Network/NetworkListener.h"

#include "Chat/Interface/Chat.h"
#include "Shared/Network/Opcode.h"

#include "Game/Chat/StructurePacket/PacketChat.h"

#include "Compte/Compte.h"

class Chat;

/*
 *
 */
class GestionnaireChat : public NetworkListener {
public:
	GestionnaireChat(Chat * chatUI);
	virtual ~GestionnaireChat();


	void updateNetwork(int event ,ENetEvent * packet);

	void sendMessageToChat(const char * message, int to);


private:
	NetworkManager * networkManager;
	Chat * chatUI;
	Compte * compte;

};

#endif /* GESTIONNAIRECHAT_H_ */
