/*
 * \file GestionnaireChat.cpp
 *
 *  Created on: \date 16 f�vr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Chat/GestionnaireChat.h"

GestionnaireChat::GestionnaireChat() {

	guiChat = new GuiChat();
	Engine::GuiManager::getInstance()->addGuiListenner(guiChat);
	networkManager = Engine::NetworkManager::getInstance();
}

GestionnaireChat::~GestionnaireChat() {
	Engine::GuiManager::getInstance()->removeGuiListenner(guiChat);
	delete guiChat;
	networkManager->removelistenneur(ID_CHAT);
}

void GestionnaireChat::run()
{
	networkManager->addlistenneur(ID_CHAT,this);
	NetworkListener::run();

}

void GestionnaireChat::processPacket(Engine::MessagePacket * messagePacket)
{
	Event event ;
	event.setProperty("CHAT","1");
	event.setProperty("Perso",messagePacket->getProperty("Perso").c_str());
	event.setProperty("Message",messagePacket->getProperty("Text").c_str());
	Engine::Engine::getInstance()->addEvent(event);
}

void GestionnaireChat::sendMessageChat(Event * event)
{
	if(event->hasProperty("Message") && !event->hasProperty("Perso") )
	{
		Engine::MessagePacket * messagePacketSend = new Engine::MessagePacket();
		messagePacketSend->setOpcode(ID_CHAT);
		messagePacketSend->setSousOpcode(0);
		messagePacketSend->setProperty("Perso","Joda");
		messagePacketSend->setProperty("Canal","1");
		messagePacketSend->setProperty("Text",event->getProperty("Message").c_str() );

		networkManager->sendPacket(messagePacketSend);
	}
}

void GestionnaireChat::processEvent(Event * event)
{
	if(event->hasProperty("CHAT"))
	{
		sendMessageChat(event);
	}

}
