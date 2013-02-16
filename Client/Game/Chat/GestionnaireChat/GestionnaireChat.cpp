/*
 * \file GestionnaireChat.cpp
 *
 *  Created on: \date 16 f�vr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Chat/GestionnaireChat/GestionnaireChat.h"

GestionnaireChat::GestionnaireChat(Chat * chatUI) {
	this->chatUI = chatUI ;

	networkManager = NetworkManager::getInstance();
	networkManager->addNetworkListener(this,"Chat");

}

GestionnaireChat::~GestionnaireChat() {
	networkManager->removeNetworkListener("Chat");
}

void GestionnaireChat::updateNetwork(int event ,ENetEvent * packet)
{

}

