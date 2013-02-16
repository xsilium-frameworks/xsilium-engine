/*
 * \file GestionnaireChat.cpp
 *
 *  Created on: \date 16 fŽvr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Chat/GestionnaireChat/GestionnaireChat.h"

GestionnaireChat::GestionnaireChat(Chat * chatUI) {
	this->chatUI = chatUI ;

	networkManager = NetworkManager::getInstance();

}

GestionnaireChat::~GestionnaireChat() {
	// TODO Auto-generated destructor stub
}

void GestionnaireChat::updateNetwork(int event ,ENetEvent * packet)
{

}
