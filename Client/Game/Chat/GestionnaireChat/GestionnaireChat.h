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

#include "Chat/UI/Chat.h"

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

};

#endif /* GESTIONNAIRECHAT_H_ */
