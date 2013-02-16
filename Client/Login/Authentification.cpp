/*
 * \file Authentification.cpp
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#include "Authentification.h"
Authentification::Authentification(LoginState *login) {

	this->login = login;
	networkManager = NetworkManager::getInstance();
	networkManager->addNetworkListener(this,"Authentification");
}

Authentification::~Authentification() {
}


void Authentification::InitialisationAuth()
{
	if (!networkManager->isConnected())
	{
		int messageErreur = networkManager->connexionToHost("85.25.251.97",60000);
		if( messageErreur > 0)
		{
			printf("erreur de connection: %d \n",messageErreur);
			login->setMessage(0,messageErreur);
		}
		else
		{
			login->setProgression(2);
		}
	}
}

void Authentification::handleEtapeDeux(ENetEvent * packet)
{
	if (packet->packet->dataLength < sizeof(sAuthLogonChallenge_S))
	{

	}

	sAuthLogonChallenge_S *data = (sAuthLogonChallenge_S *) packet->packet->data ;

	printf("key : %d \n",data->key);

	sAuthLogonProof_C message2;
	message2.cmd = XSILIUM_AUTH;
	message2.opcode = ID_SEND_REPONSE;
	std::stringstream convert2 (client.password);
	convert2>> std::hex >> message2.A;
	networkManager->sendToHost( (const char *)&message2,sizeof(message2));
}

bool Authentification::sendAuthentification()
{
		sAuthLogonChallenge_C message;
		message.cmd = XSILIUM_AUTH;
		message.opcode = ID_SEND_USER;
		message.build = client.build;
		message.login_len = std::strlen(client.login);
		std::stringstream convert (client.login);
		convert>> std::hex >> message.login;
		return networkManager->sendToHost( (const char *)&message,sizeof(message));
}


void Authentification::setLoginPwd(const char * user,const char * password)
{
	InitialisationAuth();
	/*if (std::strcmp(user,client.login) == 0)
	{
		client.etape = 1;
	}*/
	client.login = user;
	client.password = password;

	sendAuthentification();
}

void Authentification::updateNetwork(int event ,ENetEvent * packet)
{
	switch(event)
	{
	case ENET_EVENT_TYPE_RECEIVE:
		if ((uint8_t)packet->packet->data[0] == XSILIUM_AUTH)
		{
			printf("message recu %d \n",(uint8_t)packet->packet->data[1]);

			switch((uint8_t)packet->packet->data[1])
			{
			case ID_SEND_CHALLENGE :
				client.etape = 2;
				login->setProgression(3);
				handleEtapeDeux(packet);
				break;
			case ID_INVALID_ACCOUNT_OR_PASSWORD:
				login->setMessage(1,ID_INVALID_ACCOUNT_OR_PASSWORD);
				break;
			case ID_SEND_VALIDATION :
				login->setProgression(4);
				//login->setMessage(1,ID_SEND_VALIDATION);
				break;
			case ID_CONNECTION_BANNED:
				login->setMessage(1,ID_CONNECTION_BANNED);
				networkManager->disconnexion();
				break;
			case ID_COMPTE_BANNIE:
				login->setMessage(1,ID_COMPTE_BANNIE);
				networkManager->disconnexion();
				break;

			default:
				break;

			}
		}
		break;
	case ENET_EVENT_TYPE_DISCONNECT:
		login->setMessage(0,3);
		break;
	default:
		break;
	}
}
