/*
 * \file GestionnaireChat.cpp
 *
 *  Created on: \date 16 fŽvr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Chat/GestionnaireChat/GestionnaireChat.h"

GestionnaireChat::GestionnaireChat(Chat * chatUI) {
	this->chatUI = chatUI ;

	networkManager = NetworkManager::getInstance();

	int messageErreur = networkManager->connexionToHost("127.0.0.1",60001);

	if( messageErreur > 0)
	{
		printf("erreur de connection: %d \n",messageErreur);
	}
	else
	{
		networkManager->addNetworkListener(this,"Chat");
	}

}

GestionnaireChat::~GestionnaireChat() {
	networkManager->removeNetworkListener("Chat");
}

void GestionnaireChat::updateNetwork(int event ,ENetEvent * packet)
{
	switch(event)
		{
		case ENET_EVENT_TYPE_RECEIVE:
		{
			CHATPACKET_C * typePacket = (CHATPACKET_C *) packet->packet->data ;
			if (typePacket->structure_opcode.cmd == XSILIUM_KINGDOM)
			{
				printf("message recu %s \n",typePacket->message);

				chatUI->setMessage((const char *)typePacket->message);

			}
		}
			break;
		default:
			break;
		}
}

void GestionnaireChat::sendMessageToChat(const char * message, int to)
{
	CHATPACKET_C messagePacket ;

	messagePacket.structure_opcode.cmd = XSILIUM_KINGDOM ;
	messagePacket.structure_opcode.opcode = ID_CHAT ;
	messagePacket.typeChat = 0;

	std::strcpy(messagePacket.perso,"Joda");
	std::strcpy(messagePacket.message,message);

	networkManager->sendToHost((const void *)&messagePacket,sizeof(messagePacket) + 1);

}

