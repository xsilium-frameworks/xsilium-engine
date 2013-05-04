/*
 * \file GestionnaireAuth.cpp
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireAuth.h"

GestionnaireAuth::GestionnaireAuth(Interface * interface) {

	this->interface = interface;
	networkManager = NetworkManager::getInstance();

	compte = Compte::getInstance();
}

GestionnaireAuth::~GestionnaireAuth() {

	networkManager->removeNetworkListener("GestionnaireAuth");
	networkManager->disconnexion();

}


void GestionnaireAuth::InitialisationAuth()
{
	if (!networkManager->isConnected())
	{
		int messageErreur = networkManager->connexionToHost("85.25.251.97",60000);
		if( messageErreur > 0)
		{
			printf("erreur de connection: %d \n",messageErreur);
			//login->setMessage(0,messageErreur);
		}
		else
		{
			networkManager->addNetworkListener(this,"GestionnaireAuth");
			//login->setProgression(2);
		}
	}
}

void GestionnaireAuth::handleEtapeDeux(ENetEvent * packet)
{
	if (packet->packet->dataLength < sizeof(sAuthLogonChallenge_S))
	{

	}

	sAuthLogonChallenge_S *data = (sAuthLogonChallenge_S *) packet->packet->data ;

	printf("key : %d \n",data->key);

	sAuthLogonProof_C message2;
	message2.structure_opcode.cmd = XSILIUM_AUTH;
	message2.structure_opcode.opcode = ID_SEND_REPONSE;
	std::strcpy(message2.A,compte->getPassWord());
	networkManager->sendToHost( (const void *)&message2,sizeof(message2));
}

bool GestionnaireAuth::sendAuthentification()
{
		sAuthLogonChallenge_C message;
		message.structure_opcode.cmd = XSILIUM_AUTH;
		message.structure_opcode.opcode = ID_SEND_USER;
		message.build = compte->getVersion();
		message.login_len = std::strlen(compte->getLogin());
		std::strcpy(message.login,compte->getLogin());
		return networkManager->sendToHost( (const void *)&message,sizeof(message));
}


void GestionnaireAuth::setLoginPwd(const char * user,const char * password)
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

void GestionnaireAuth::updateNetwork(int event ,ENetEvent * packet)
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
				//login->setProgression(3);
				handleEtapeDeux(packet);
				break;
			case ID_INVALID_ACCOUNT_OR_PASSWORD:
				//login->setMessage(1,ID_INVALID_ACCOUNT_OR_PASSWORD);
				break;
			case ID_SEND_VALIDATION :
				//login->setProgression(4);
				////login->setMessage(1,ID_SEND_VALIDATION);
				break;
			case ID_CONNECTION_BANNED:
				//login->setMessage(1,ID_CONNECTION_BANNED);
				networkManager->disconnexion();
				break;
			case ID_COMPTE_BANNIE:
				//login->setMessage(1,ID_COMPTE_BANNIE);
				networkManager->disconnexion();
				break;

			default:
				break;

			}
		}
	}
		break;
	case ENET_EVENT_TYPE_DISCONNECT:
		//login->setMessage(0,3);
		break;
	default:
		break;
	}
}
