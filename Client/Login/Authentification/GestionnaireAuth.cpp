/*
 * \file GestionnaireAuth.cpp
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireAuth.h"

GestionnaireAuth::GestionnaireAuth(GuiInterface * guiInterface) {

	this->guiInterface = guiInterface;
	networkManager = NetworkManager::getInstance();
	networkManager->addNetworkListener(this,"GestionnaireAuth");

	compte = Compte::getInstance();
}

GestionnaireAuth::~GestionnaireAuth() {

	networkManager->removeNetworkListener("GestionnaireAuth");
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
	if (!networkManager->isConnected())
	{
		return;
	}

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
				guiInterface->setEvent("1","3");
				handleEtapeDeux(packet);
				break;
			case ID_INVALID_ACCOUNT_OR_PASSWORD:
				guiInterface->setEvent("0","Le login ou le mot de passe est incorrecte .");
				//login->setMessage(1,ID_INVALID_ACCOUNT_OR_PASSWORD);
				break;
			case ID_SEND_VALIDATION :
			{
				guiInterface->setEvent("1","4");
				//login->setMessage(1,ID_SEND_VALIDATION);
			}
			break;
			case ID_CONNECTION_BANNED:
				guiInterface->setEvent("0","Votre IP a ete banni .\n Il est imposible de se connecter .");
				networkManager->disconnexion();
				break;
			case ID_COMPTE_BANNIE:
				guiInterface->setEvent("0","Votre Compte a ete banni . \n Il est impossible de se connecter .");
				networkManager->disconnexion();
				break;

			default:
				break;

			}
		}
	}
	break;
	case ENET_EVENT_TYPE_DISCONNECT:
		guiInterface->setEvent("0","Déconnexion réussie");
		break;
	default:
		break;
	}
}
