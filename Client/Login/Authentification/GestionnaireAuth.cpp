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
	guiAuth = new GuiAuth();
	Engine::GuiManager::getInstance()->addGuiListenner(guiAuth);
	networkManager = Engine::NetworkManager::getInstance();
}

GestionnaireAuth::~GestionnaireAuth() {
	Engine::GuiManager::getInstance()->removeGuiListenner(guiAuth);
	delete guiAuth;
	networkManager->removelistenneur((XSILIUM_AUTH * 1000) + ID_AUTH);

}

void GestionnaireAuth::run()
{
	networkManager->addlistenneur((XSILIUM_AUTH * 1000) + ID_AUTH,this);
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
		Engine::EventManager::getInstance()->addEvent(event);
		return false;
	}
	if( messageErreur == 2)
	{
		//XsiliumFramework::getInstance()->getLog()->logMessage("erreur de connexion : Impossible de se connecter au serveur");
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Impossible de se connecter au serveur");
		Engine::EventManager::getInstance()->addEvent(event);
		return false;
	}
	return true;
}

void GestionnaireAuth::processPacket(Engine::MessagePacket * messagePacket)
{
	switch(messagePacket->getSousOpcode())
	{
	case ID_CHALLENGE :
	{
		compte->setEtapeDeLogin(2);
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("Progression","3");
		event.setProperty("ProgressionTotal","4");
		Engine::EventManager::getInstance()->addEvent(event);
		handleEtapeDeux(messagePacket);
	}
	break;
	case ID_REPONSE :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("Progression","4");
		event.setProperty("ProgressionTotal","4");
		Engine::EventManager::getInstance()->addEvent(event);

		Event event2 ;
		event.setProperty("GAME","1");
		event.setProperty("ChangeGameState","PlayState");
		Engine::EventManager::getInstance()->addEvent(event);
	}
	break;
	case ID_SEND_CANCEL:
		cancelAuthentification();
		break;
	case ID_ERREUR:
		gestionnaireErreur(messagePacket);
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

void GestionnaireAuth::handleEtapeDeux(Engine::MessagePacket * messagePacket)
{

	Engine::MessagePacket * messagePacketSend = new Engine::MessagePacket();

	messagePacketSend->setOpcode(ID_AUTH);
	messagePacketSend->setSousOpcode(ID_REPONSE);
	messagePacketSend->setProperty("Password",compte->getPassWord());
	networkManager->sendPacket(messagePacketSend);

}

bool GestionnaireAuth::sendAuthentification()
{

	Engine::MessagePacket * messagePacketSend = new Engine::MessagePacket();

	messagePacketSend->setOpcode(ID_AUTH);
	messagePacketSend->setSousOpcode(ID_CHALLENGE);
	messagePacketSend->setProperty("Build",compte->getVersion());
	messagePacketSend->setProperty("Login",compte->getLogin());

	networkManager->sendPacket(messagePacketSend);
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

void GestionnaireAuth::gestionnaireErreur(Engine::MessagePacket * messagePacket)
{
	switch(messagePacket->getSousOpcode())
	{
	case ID_ERROR_PACKET_SIZE :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Le serveur n'arrive pas a lire les donnees");
		Engine::EventManager::getInstance()->addEvent(event);
	}
	break;
	case ID_CONNECTION_BANNED :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","desoler Votre IP est banni ");
		Engine::EventManager::getInstance()->addEvent(event);
	}
	break;
	case ID_INVALID_ACCOUNT_OR_PASSWORD :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Le login ou le mot de passe est incorrecte .");
		Engine::EventManager::getInstance()->addEvent(event);
	}
	break;
	case ID_COMPTE_BANNIE :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Votre Compte a ete banni . \n Il est impossible de se connecter .");
		Engine::EventManager::getInstance()->addEvent(event);
	}
	break;
	case ID_INVALID_IP :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Votre IP a ete banni .\n Il est imposible de se connecter .");
		Engine::EventManager::getInstance()->addEvent(event);
	}
	break;
	case ID_ERROR_ETAPE :
	{
		Event event ;
		event.setProperty("AUTH","1");
		event.setProperty("ErreurMessage","Le serveur a rencontre un probleme . ");
		Engine::EventManager::getInstance()->addEvent(event);
	}
	break;
	default:
		break;
	}

}

