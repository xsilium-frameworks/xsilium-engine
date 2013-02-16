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

	compte = Compte::getInstance();
}

Authentification::~Authentification() {

	networkManager->removeNetworkListener("Authentification");

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
	message2.structure_opcode.cmd = XSILIUM_AUTH;
	message2.structure_opcode.opcode = ID_SEND_REPONSE;
	std::stringstream convert2 (compte->getPassWord());
	convert2>> std::hex >> message2.A;
	networkManager->sendToHost( (const char *)&message2,sizeof(message2));
}

bool Authentification::sendAuthentification()
{
		sAuthLogonChallenge_C message;
		message.structure_opcode.cmd = XSILIUM_AUTH;
		message.structure_opcode.opcode = ID_SEND_USER;
		message.build = compte->getVersion();
		message.login_len = std::strlen(compte->getLogin());
		std::stringstream convert (compte->getLogin());
		convert>> std::hex >> message.login;
		return networkManager->sendToHost( (const char *)&message,sizeof(message));
}


void Authentification::setLoginPwd(const char * user,const char * password)
{
	InitialisationAuth();

	if (std::strcmp(user,compte->getLogin()) == 0)
	{
		compte->setEtapeDeLogin(1);
	}
	compte->setLogin(user);
	compte->setPassWord(password);

	sendAuthentification();
}

void Authentification::updateNetwork(int event ,ENetEvent * packet)
{
	switch(event)
	{
	case ENET_EVENT_TYPE_RECEIVE:
	{
		structure_opcodeT * typePacket = (structure_opcodeT *) packet->packet->data ;
		if (typePacket->cmd == XSILIUM_AUTH)
		{
			printf("message recu %d \n",typePacket->opcode);

			switch(typePacket->opcode)
			{
			case ID_SEND_CHALLENGE :
				compte->setEtapeDeLogin(2);
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
	}
		break;
	case ENET_EVENT_TYPE_DISCONNECT:
		login->setMessage(0,3);
		break;
	default:
		break;
	}
}
