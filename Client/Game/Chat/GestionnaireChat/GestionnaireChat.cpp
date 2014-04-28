/*
 * \file GestionnaireChat.cpp
 *
 *  Created on: \date 16 fŽvr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Chat/GestionnaireChat/GestionnaireChat.h"

GestionnaireChat::GestionnaireChat() {

	networkManager = NetworkManager::getInstance();
    NetworkManager::getInstance()->createConnexion();
	gestionnaireInterface = GestionnaireInterface::getInstance();
	compte = Compte::getInstance();

	keyboardMap = KeyboardMap::getInstance();
	inputManager = InputManager::getSingletonPtr();


	guichat = new Chat(this);
	gestionnaireInterface->addInterface(guichat);

	int messageErreur = networkManager->connexionToHost("85.25.143.49",60001);

	if( messageErreur > 0)
	{
		printf("erreur de connection: %d \n",messageErreur);
	}
	else
	{
		run();
	}

	inputManager->addKeyListener(this,"GestionnaireChatKey");

}

GestionnaireChat::~GestionnaireChat() {
	networkManager->removelistenneur((XSILIUM_KINGDOM * 1000) + ID_CHAT);
    networkManager->disconnexion();
	inputManager->removeKeyListener(this);
	gestionnaireInterface->removeInterface(guichat);
	delete guichat;
}

void GestionnaireChat::run()
{
	networkManager->addlistenneur((XSILIUM_KINGDOM * 1000) + ID_CHAT,boost::bind(&GestionnaireChat::setPacket, this));

	ModuleActif::run();
}

void GestionnaireChat::retourInterface(int IDInterface,int retour)
{
}

void GestionnaireChat::processPacket(ENetEvent * packet)
{
	CHATPACKET_C * typePacket = (CHATPACKET_C *) packet->packet->data ;
	if (typePacket->charTypePacket.structure_opcode.cmd == XSILIUM_KINGDOM)
	{
		printf("message recu %s \n",typePacket->message);


		char messageConsole[576];
		std::strcpy(messageConsole,(const char *)typePacket->perso); // copy string one into the result.
		std::strcat(messageConsole," > ");
		std::strcat(messageConsole,(const char *)typePacket->message);
        
		guichat->setEvent(ToString(ALL).c_str(),messageConsole);

	}
}

void GestionnaireChat::sendMessageToChat(const char * message, int to)
{
	CHATPACKET_C messagePacket ;

	messagePacket.charTypePacket.structure_opcode.cmd = XSILIUM_KINGDOM ;
	messagePacket.charTypePacket.structure_opcode.opcode = ID_CHAT ;
	messagePacket.charTypePacket.typeChat = 0;

	std::strcpy(messagePacket.perso,compte->getLogin());
	std::strcpy(messagePacket.message,message);

	ENetPacket * packetAEnvoyer = enet_packet_create ((const void *)&messagePacket,sizeof(messagePacket) + 1,ENET_PACKET_FLAG_RELIABLE);
	networkManager->sendPacket(packetAEnvoyer,0);

}


bool GestionnaireChat::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	switch (keyEventRef.key)
	{

	case OIS::KC_RETURN:
		if(guichat->saisiActiver())
		{
			if(std::strcmp(guichat->getSaisi(),""))
			{
				sendMessageToChat(guichat->getSaisi(),0);
			}
			guichat->effaceSaisi();
			GestionnaireMouvement::getInstance()->activeDeplacement();
		}
		else
		{
			GestionnaireMouvement::getInstance()->desactiveDeplacement();
			guichat->activeSaisi();

		}
		break;
	default:
		break;
	}
	return true;


}
bool GestionnaireChat::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return true;
}
