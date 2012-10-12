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

	client.sendpassword = false;


}

Authentification::~Authentification() {
}


bool Authentification::InitialisationAuth()
{

	if (networkManager->disconnexion())
	{
		networkManager->connexionToHost("127.0.0.1",60000);
		return true;
	}
	else
	{
		//erreur
		return false;
	}
}

void Authentification::handleReturn(ENetEvent * packet)
{
	if (packet->packet->dataLength < sizeof(sAuthLogonChallenge_S))
	{

	}

	sAuthLogonChallenge_S *data = (sAuthLogonChallenge_S *) packet->packet->data ;

	printf("key : %d \n",data->key);

	client.sendpassword = true;

	sendAuthentification();
}

bool Authentification::sendAuthentification()
{
	if (!client.sendpassword)
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
	else
	{
		sAuthLogonProof_C message;
		message.cmd = XSILIUM_AUTH;
		message.opcode = ID_SEND_REPONSE;
		std::stringstream convert (client.password);
		convert>> std::hex >> message.A;

		return networkManager->sendToHost( (const char *)&message,sizeof(message));
	}
}


void Authentification::setLoginPwd(const char * user,const char * password)
{
	client.login = user;
	client.password = password;

	sendAuthentification();
}

void Authentification::updateNetwork(int event ,ENetEvent * packet)
{
	handleReturn(packet);
}
