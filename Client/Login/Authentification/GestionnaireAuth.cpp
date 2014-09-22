/*
 * \file GestionnaireAuth.cpp
 *
 *  Created on: \date 25 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireAuth.h"

GestionnaireAuth::GestionnaireAuth() {

	compte = Compte::getInstance();
	Engine::GuiManager::getInstance()->addGuiListenner(new GuiAuth());
}

GestionnaireAuth::~GestionnaireAuth() {
	networkManager->removelistenneur((XSILIUM_AUTH * 1000) + ID_AUTH);
}

void GestionnaireAuth::run()
{
	networkManager->addlistenneur((XSILIUM_AUTH * 1000) + ID_AUTH,boost::bind(&GestionnaireAuth::setPacket, this));
	NetworkListener::run();
}

bool GestionnaireAuth::initNetwork()
{

	int messageErreur = networkManager->connexionToHost(AUTH_HOST,AUTH_PORT);
	if( messageErreur == 1)
	{
		//XsiliumFramework::getInstance()->getLog()->logMessage("erreur de connexion : Le serveur est plein desoler ");
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Le serveur est plein desoler");
		Engine::Engine::getInstance()->addEvent(event);
		return false;
	}
	if( messageErreur == 2)
	{
		//XsiliumFramework::getInstance()->getLog()->logMessage("erreur de connexion : Impossible de se connecter au serveur");
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Impossible de se connecter au serveur");
		Engine::Engine::getInstance()->addEvent(event);
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
	{
		compte->setEtapeDeLogin(2);
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("Progression","3");
		event.setProperty("ProgressionTotal","4");
		Engine::Engine::getInstance()->addEvent(event);
		handleEtapeDeux(packet);
	}
	break;
	case ID_REPONSE :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("Progression","4");
		event.setProperty("ProgressionTotal","4");
		Engine::Engine::getInstance()->addEvent(event);

		Event event2 ;
		event.setProperty("GAME","1");
		event.setProperty("ChangeGameState","JeuxState");
		Engine::Engine::getInstance()->addEvent(event);
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

void GestionnaireAuth::processEvent(Event * event)
{
	if(event->hasProperty("AUTH"))
	{
		if( event->hasProperty("Login") && event->hasProperty("PassWord"))
		{
			setAuthentification(event);
		}
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
}


void GestionnaireAuth::setAuthentification(Event * event)
{
	if (!networkManager->isConnected())
	{
		if(!initNetwork())
			return;
		run();
	}

	if( event->getProperty("Login").compare(compte->getLogin()) == 0)
	{
		compte->setEtapeDeLogin(1);
	}

	compte->setLogin(event->getProperty("Login").c_str());
	compte->setPassWord(event->getProperty("PassWord").c_str());
	sendAuthentification();
}

void GestionnaireAuth::gestionnaireErreur(AUTHPACKET_ERROR * packetErreur)
{
	switch(packetErreur->errorID)
	{
	case ID_ERROR_PACKET_SIZE :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Le serveur n'arrive pas a lire les donnees");
		Engine::Engine::getInstance()->addEvent(event);
	}
	break;
	case ID_CONNECTION_BANNED :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","desoler Votre IP est banni ");
		Engine::Engine::getInstance()->addEvent(event);
	}
	break;
	case ID_INVALID_ACCOUNT_OR_PASSWORD :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Le login ou le mot de passe est incorrecte .");
		Engine::Engine::getInstance()->addEvent(event);
	}
	break;
	case ID_COMPTE_BANNIE :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Votre Compte a ete banni . \n Il est impossible de se connecter .");
		Engine::Engine::getInstance()->addEvent(event);
	}
	break;
	case ID_INVALID_IP :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Votre IP a ete banni .\n Il est imposible de se connecter .");
		Engine::Engine::getInstance()->addEvent(event);
	}
	break;
	case ID_ERROR_ETAPE :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Le serveur a rencontre un probleme . ");
		Engine::Engine::getInstance()->addEvent(event);
	}
	break;
	default:
		break;
	}

}

