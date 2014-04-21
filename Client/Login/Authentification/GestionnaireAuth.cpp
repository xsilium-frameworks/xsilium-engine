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

	compte = Compte::getInstance();
    
    gestionnaireInterface = GestionnaireInterface::getInstance();

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

void GestionnaireAuth::run()
{
	networkManager->addlistenneur((XSILIUM_AUTH * 1000) + ID_AUTH,boost::bind(&GestionnaireAuth::setPacket, this));

	ModuleActif::run();
}

bool GestionnaireAuth::initNetwork()
{

	int messageErreur = networkManager->connexionToHost(AUTH_HOST,AUTH_PORT);
	if( messageErreur == 1)
	{
		XsiliumFramework::getInstance()->getLog()->logMessage("erreur de connexion : Le serveur est plein desoler ");
		guiErreur->setEvent(ToString(ACTIVE).c_str());
		guiErreur->setEvent(ToString(MESSAGE).c_str(),"Le serveur est plein desoler");
		return false;
	}
	if( messageErreur == 2)
	{
		XsiliumFramework::getInstance()->getLog()->logMessage("erreur de connexion : Impossible de se connecter au serveur");
		guiErreur->setEvent(ToString(ACTIVE).c_str());
		guiErreur->setEvent(ToString(MESSAGE).c_str(),"Impossible de se connecter au serveur");
		return false;
	}
	return true;
}

void GestionnaireAuth::processPacket(ENetEvent * packet)
{
	AUTHPACKET_TYPE *data = (AUTHPACKET_TYPE *) packet->packet->data ;
	switch(data->typeAuth)
	{
	case ID_CHALLENGE :
		compte->setEtapeDeLogin(2);
		guiProgression->setEvent(ToString(PROGRESSION).c_str(),"3");
		handleEtapeDeux(packet);
		break;
	case ID_REPONSE :
		guiProgression->setEvent(ToString(PROGRESSION).c_str(),"4");
		loginState->setChangeState();
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
	networkManager->sendPacket(packetAEnvoyer,0);
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
	return true;
}

void GestionnaireAuth::cancelAuthentification()
{
	guiProgression->setEvent(ToString(INVISIBLE).c_str());
	guiProgression->setEvent(ToString(DESACTIVE).c_str());
	guiErreur->setEvent(ToString(DESACTIVE).c_str());
	guiLogin->setEvent(ToString(ACTIVE).c_str());
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
		run();
	}
	guiLogin->setEvent(ToString(DESACTIVE).c_str());
	guiProgression->setEvent(ToString(ACTIVE).c_str());
	guiProgression->setEvent(ToString(VISIBLE).c_str());
	guiProgression->setEvent(ToString(PROGRESSION).c_str(),"1");

	if (std::strcmp(guiLogin->getLogin(),compte->getLogin()) == 0)
	{
		compte->setEtapeDeLogin(1);
	}

	compte->setLogin(guiLogin->getLogin());
	compte->setPassWord(guiLogin->getPassword());

	sendAuthentification();
}

void GestionnaireAuth::retourInterface(int IDInterface,int retour)
{
	if(IDInterface == guiLogin->getIDInterface())
	{
		switch(retour)
		{
		case QUITBOUTON :
			quitAuthentification();
			break;
		case CONNEXIONBOUTON:
			setAuthentification();
			break;
		default:
			break;
		}
	}

	if(IDInterface == guiErreur->getIDInterface())
	{
		switch(retour)
		{
		case OKBOUTON :
			cancelAuthentification();
			break;
		default:
			break;
		}
	}

	if(IDInterface == guiProgression->getIDInterface())
	{
		switch(retour)
		{
		case CANCELBOUTON :
			cancelAuthentification();
			break;
		default:

			break;
		}
	}
}

void GestionnaireAuth::gestionnaireErreur(AUTHPACKET_ERROR * packetErreur)
{
	switch(packetErreur->errorID)
	{
	case ID_ERROR_PACKET_SIZE :
		guiProgression->setEvent(ToString(INVISIBLE).c_str());
		guiProgression->setEvent(ToString(DESACTIVE).c_str());
		guiErreur->setEvent(ToString(ACTIVE).c_str());
		guiErreur->setEvent(ToString(MESSAGE).c_str(),"Le serveur n'arrive pas a lire les donnees");
		break;
	case ID_CONNECTION_BANNED :
		guiProgression->setEvent(ToString(INVISIBLE).c_str());
		guiProgression->setEvent(ToString(DESACTIVE).c_str());
		guiErreur->setEvent(ToString(ACTIVE).c_str());
		guiErreur->setEvent(ToString(MESSAGE).c_str(),"desoler Votre IP est banni ");
		break;
	case ID_INVALID_ACCOUNT_OR_PASSWORD :
		guiProgression->setEvent(ToString(INVISIBLE).c_str());
		guiProgression->setEvent(ToString(DESACTIVE).c_str());
		guiErreur->setEvent(ToString(ACTIVE).c_str());
		guiErreur->setEvent(ToString(MESSAGE).c_str(),"Le login ou le mot de passe est incorrecte .");
		break;
	case ID_COMPTE_BANNIE :
		guiProgression->setEvent(ToString(INVISIBLE).c_str());
		guiProgression->setEvent(ToString(DESACTIVE).c_str());
		guiErreur->setEvent(ToString(ACTIVE).c_str());
		guiErreur->setEvent(ToString(MESSAGE).c_str(),"Votre Compte a ete banni . \n Il est impossible de se connecter .");
		break;
	case ID_INVALID_IP :
		guiProgression->setEvent(ToString(INVISIBLE).c_str());
		guiProgression->setEvent(ToString(DESACTIVE).c_str());
		guiErreur->setEvent(ToString(ACTIVE).c_str());
		guiErreur->setEvent(ToString(MESSAGE).c_str(),"Votre IP a ete banni .\n Il est imposible de se connecter .");
		break;
	case ID_ERROR_ETAPE :
		guiProgression->setEvent(ToString(INVISIBLE).c_str());
		guiProgression->setEvent(ToString(DESACTIVE).c_str());
		guiErreur->setEvent(ToString(ACTIVE).c_str());
		guiErreur->setEvent(ToString(MESSAGE).c_str(),"Le serveur a rencontre un probleme . ");
		break;
	default:
		break;
	}

}

