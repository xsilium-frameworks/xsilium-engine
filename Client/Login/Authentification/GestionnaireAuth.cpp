/*
 * \file GestionnaireAuth.cpp
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireAuth.h"

GestionnaireAuth::GestionnaireAuth(LoginState * loginState) {

	keyboardMap = KeyboardMap::getInstance();
	inputManager = InputManager::getSingletonPtr();

	networkManager = NetworkManager::getInstance();

	compte = Compte::getInstance();

	gestionnaireInterface = GestionnaireInterface::getInstance();
	gestionnaireInterface->interfacePrincipal();

	this->loginState = loginState;

	guiLogin = new GuiLogin(this);
	gestionnaireInterface->addInterface(guiLogin);

	guiErreur = new GuiErreur(this);
	gestionnaireInterface->addInterface(guiErreur);

	guiProgression = new GuiProgression(this);
	gestionnaireInterface->addInterface(guiProgression);

	inputManager->addKeyListener(this,"GestionnaireAuthKey");


}

GestionnaireAuth::~GestionnaireAuth() {

	networkManager->removelistenneur((XSILIUM_AUTH * 1000) + ID_AUTH);
	inputManager->removeKeyListener(this);
	gestionnaireInterface->removeInterface(guiLogin);
	gestionnaireInterface->removeInterface(guiErreur);
	gestionnaireInterface->removeInterface(guiProgression);
	delete guiLogin;
	delete guiErreur;
	delete guiProgression;
}


bool GestionnaireAuth::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	switch (keyEventRef.key)
	{

	case OIS::KC_RETURN:
		if(guiLogin->isActive())
			setAuthentification();
		else if(guiErreur->isActive())
			cancelAuthentification();
		break;
	case OIS::KC_TAB:
		guiLogin->switchEditBox();
		break;
	default:
		break;
	}
	return true;


}
bool GestionnaireAuth::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return true;
}

bool GestionnaireAuth::initNetwork()
{

	int messageErreur = networkManager->connexionToHost(AUTH_HOST,AUTH_PORT);
	if( messageErreur == 1)
	{
		XsiliumFramework::getInstance()->getLog()->logMessage("erreur de connexion : Le serveur est plein desoler ");
		guiErreur->activeInterface();
		guiErreur->setEvent("0","Le serveur est plein desoler");
		return false;
	}
	if( messageErreur == 2)
	{
		XsiliumFramework::getInstance()->getLog()->logMessage("erreur de connexion : Impossible de se connecter au serveur");
		guiErreur->activeInterface();
		guiErreur->setEvent("0","Impossible de se connecter au serveur");
		return false;
	}
	networkManager->addlistenneur((XSILIUM_AUTH * 1000) + ID_AUTH,boost::bind(&GestionnaireAuth::setPacket, this));
	guiLogin->desactiveInterface();
	guiProgression->activeInterface();
	guiProgression->setVisibility(true) ;
	guiProgression->setEvent("0","1");
	return true;
}

void GestionnaireAuth::handleEtapeDeux(ENetEvent * packet)
{
	if (packet->packet->dataLength < sizeof(AUTHPACKET_LC_S))
	{

	}

	AUTHPACKET_LC_S *data = (AUTHPACKET_LC_S *) packet->packet->data ;

	printf("key : %d \n",data->key);

	AUTHPACKET_P_C message2;
	message2.authTypePacket.structure_opcode.cmd = XSILIUM_AUTH;
	message2.authTypePacket.structure_opcode.opcode = ID_AUTH;
	message2.authTypePacket.typeAuth = ID_REPONSE ;
	std::strcpy(message2.A,compte->getPassWord());

	ENetPacket * packetAEnvoyer = enet_packet_create ((const void *)&message2,sizeof(message2) + 1,ENET_PACKET_FLAG_RELIABLE);
	networkManager->sendPacket (packetAEnvoyer,0);
}

bool GestionnaireAuth::sendAuthentification()
{

	AUTHPACKET_LC_C message;
	message.authTypePacket.structure_opcode.cmd = XSILIUM_AUTH;
	message.authTypePacket.structure_opcode.opcode = ID_AUTH;
	message.authTypePacket.typeAuth = ID_CHALLENGE;
	message.build = compte->getVersion();
	message.login_len = std::strlen(compte->getLogin());
	std::strcpy(message.login,compte->getLogin());
	ENetPacket * packetAEnvoyer = enet_packet_create ((const void *)&message,sizeof(message) + 1,ENET_PACKET_FLAG_RELIABLE);
	networkManager->sendPacket (packetAEnvoyer,0);
}

void GestionnaireAuth::cancelAuthentification()
{
	guiProgression->setVisibility(false);
	guiProgression->desactiveInterface();
	guiErreur->desactiveInterface();
	guiLogin->activeInterface();
}

void GestionnaireAuth::quitAuthentification()
{
	loginState->setExit();
}


void GestionnaireAuth::setAuthentification()
{
	if (!networkManager->isConnected())
	{
		if(!initNetwork())
			return;
	}

	if (std::strcmp(guiLogin->getLogin(),compte->getLogin()) == 0)
	{
		compte->setEtapeDeLogin(1);
	}

	compte->setLogin(guiLogin->getLogin());
	compte->setPassWord(guiLogin->getPassword());

	sendAuthentification();
}

void GestionnaireAuth::gestionnaireErreur(AUTHPACKET_ERROR * packetErreur)
{
	switch(packetErreur->errorID)
	{
	case ID_ERROR_PACKET_SIZE :
	//	guiProgression->setVisibility(false);
	//	guiProgression->desactiveInterface();
	//	guiErreur->activeInterface();
	//	guiErreur->setEvent("0","Le serveur n'arrive pas a lire les donnees");
		break;
	case ID_CONNECTION_BANNED :
	//	guiProgression->setVisibility(false);
	//	guiProgression->desactiveInterface();
	//	guiErreur->activeInterface();
	//	guiErreur->setEvent("0","Le serveur est plein desoler");
		break;
	case ID_INVALID_ACCOUNT_OR_PASSWORD :
		guiProgression->setVisibility(false);
	//	guiProgression->desactiveInterface();
	//	guiErreur->activeInterface();
	//	guiErreur->setEvent("0","Le login ou le mot de passe est incorrecte .");
		break;
	case ID_COMPTE_BANNIE :
		//	guiProgression->setVisibility(false);
		//	guiProgression->desactiveInterface();
	//	guiErreur->activeInterface();
	//	guiErreur->setEvent("0","Votre Compte a ete banni . \n Il est impossible de se connecter .");
		break;
	case ID_INVALID_IP :
		//	guiProgression->setVisibility(false);
		//	guiProgression->desactiveInterface();
	//	guiErreur->activeInterface();
	//	guiErreur->setEvent("0","Votre IP a ete banni .\n Il est imposible de se connecter .");
		break;
	case ID_ERROR_ETAPE :
		//	guiProgression->setVisibility(false);
		//	guiProgression->desactiveInterface();
	//	guiErreur->activeInterface();
	//	guiErreur->setEvent("0","Le serveur a rencontre un probleme . ");
		break;
	default:
		break;
	}
}

void GestionnaireAuth::updateNetwork(int event ,ENetEvent * packet)
{
	switch(event)
	{
	case ENET_EVENT_TYPE_RECEIVE:
	{
		AUTHPACKET_TYPE * typePacket = (AUTHPACKET_TYPE *) packet->packet->data ;
		if (typePacket->structure_opcode.cmd == XSILIUM_AUTH && typePacket->structure_opcode.opcode == ID_AUTH)
		{
			printf("message recu %d \n",typePacket->typeAuth);

			switch(typePacket->typeAuth)
			{
			case ID_CHALLENGE :
				compte->setEtapeDeLogin(2);
				guiProgression->setEvent("0","3");
				handleEtapeDeux(packet);
				break;
			case ID_REPONSE :
			{
				guiProgression->setEvent("1","4");
			}
			break;
			case ID_SEND_CANCEL:
				cancelAuthentification();
				break;
			case ID_ERREUR:
				gestionnaireErreur( (AUTHPACKET_ERROR *) packet->packet->data);
				break;
			default:
				break;

			}
		}
	}
	break;
	case ENET_EVENT_TYPE_DISCONNECT:
		//guiInterface->setEvent("0","Déconnexion réussie");
		break;
	default:
		break;
	}
}

