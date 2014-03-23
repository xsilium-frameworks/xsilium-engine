/*
 * \file GestionnaireChat.cpp
 *
 *  Created on: \date 16 fŽvr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Chat/GestionnaireChat/GestionnaireChat.h"

GestionnaireChat::GestionnaireChat(JeuxState * jeuxState) {
	this->jeuxState = jeuxState ;

	networkManager = NetworkManager::getInstance();
	gestionnaireInterface = GestionnaireInterface::getInstance();
	compte = Compte::getInstance();


	guichat = new Chat(this);
	gestionnaireInterface->addInterface(guichat);

	int messageErreur = networkManager->connexionToHost("85.25.143.49",60001);

	if( messageErreur > 0)
	{
		printf("erreur de connection: %d \n",messageErreur);
	}
	else
	{
		networkManager->addlistenneur((XSILIUM_KINGDOM * 1000) + ID_CHAT,boost::bind(&GestionnaireChat::setPacket, this));
	}

}

GestionnaireChat::~GestionnaireChat() {
	networkManager->removelistenneur((XSILIUM_KINGDOM * 1000) + ID_CHAT);
	gestionnaireInterface->removeInterface(guichat);
	delete guichat;
}

void GestionnaireChat::updateNetwork(int event ,ENetEvent * packet)
{
	switch(event)
		{
		case ENET_EVENT_TYPE_RECEIVE:
		{
			CHATPACKET_C * typePacket = (CHATPACKET_C *) packet->packet->data ;
			if (typePacket->charTypePacket.structure_opcode.cmd == XSILIUM_KINGDOM)
			{
				printf("message recu %s \n",typePacket->message);


				char messageConsole[576];
				std::strcpy(messageConsole,(const char *)typePacket->perso); // copy string one into the result.
				std::strcat(messageConsole," > ");
				std::strcat(messageConsole,(const char *)typePacket->message);


				//guichat->setMessage(messageConsole);

			}
		}
			break;
		default:
			break;
		}
}

void GestionnaireChat::retourInterface(int IDInterface,int retour)
{
}

void GestionnaireChat::processPacket(ENetEvent * packet)
{

}

void GestionnaireChat::sendMessageToChat(const char * message, int to)
{
	CHATPACKET_C messagePacket ;

	messagePacket.charTypePacket.structure_opcode.cmd = XSILIUM_KINGDOM ;
	messagePacket.charTypePacket.structure_opcode.opcode = ID_CHAT ;
	messagePacket.charTypePacket.typeChat = 0;

	std::strcpy(messagePacket.perso,compte->getLogin());
	std::strcpy(messagePacket.message,message);

	//networkManager->sendToHost((const void *)&messagePacket,sizeof(messagePacket) + 1);

}

