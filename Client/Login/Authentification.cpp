/*
 * \file Authentification.cpp
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#include "Authentification.h"
Authentification::Authentification() {

	networkManager = NetworkManager::getInstance();
	networkManager->addNetworkListener(this,"Authentification");

	client.etape = 1;


}

Authentification::~Authentification() {
}


void Authentification::InitialisationAuth()
{
	if (networkManager->isConnected())
	{
		networkManager->disconnexion();
	}

	int messageErreur = networkManager->connexionToHost("127.0.0.1",60000);
	if( messageErreur > 0)
	{
		printf("test %d \n",messageErreur);
		login->setMessage(messageErreur);
	}
}

void Authentification::setLogin(LoginState *login)
{
	this->login = login;
}

void Authentification::handleReturn(ENetEvent * packet)
{
	if (packet->packet->dataLength < sizeof(sAuthLogonChallenge_S))
	{

	}

	sAuthLogonChallenge_S *data = (sAuthLogonChallenge_S *) packet->packet->data ;

	printf("key : %d \n",data->key);

	sendAuthentification();
}

bool Authentification::sendAuthentification()
{
	int returnErreur;

	switch(client.etape)
	{
	case 1:
	{
		sAuthLogonChallenge_C message;
		message.cmd = XSILIUM_AUTH;
		message.opcode = ID_SEND_USER;
		message.build = client.build;
		message.login_len = std::strlen(client.login);
		std::stringstream convert (client.login);
		convert>> std::hex >> message.login;
		returnErreur =  networkManager->sendToHost( (const char *)&message,sizeof(message));
		break;
	}
	case 2:
	{
		sAuthLogonProof_C message2;
		message2.cmd = XSILIUM_AUTH;
		message2.opcode = ID_SEND_REPONSE;
		std::stringstream convert2 (client.password);
		convert2>> std::hex >> message2.A;
		returnErreur =  networkManager->sendToHost( (const char *)&message2,sizeof(message2));
		break;
	}
	case 3:
	{
		returnErreur = -1;
		break;
	}
	}

	return returnErreur;
}


void Authentification::setLoginPwd(const char * user,const char * password)
{
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

			if ((uint8_t)packet->packet->data[1] == ID_SEND_CHALLENGE)
			{
				client.etape = 2;
				handleReturn(packet);
			}
			else
			{
				login->setMessage((int)packet->packet->data[1]);
			}
		}
		break;
	case ENET_EVENT_TYPE_DISCONNECT:
		break;
	default:
		break;
	}
}
