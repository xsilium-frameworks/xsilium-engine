/*
 * \file GestionnaireChat.h
 *
 *  Created on: \date 16 f�vr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIRECHAT_H_
#define GESTIONNAIRECHAT_H_

#include <Network/NetworkManager.h>
#include "Gui/GuiChat.h"

#include "Compte/Compte.h"

enum typeForChat
{
	ID_TOPERSO = 0
};

/*
 *
 */
class GestionnaireChat : public Engine::NetworkListener {
public:
	GestionnaireChat();
	virtual ~GestionnaireChat();

	void run();

	void processPacket(Engine::MessagePacket * messagePacket);

	void sendMessageChat(Event * event);

	void affichageMessage();

	void processEvent(Event * event);


private:
	Engine::NetworkManager * networkManager;
	GuiChat * guiChat;

};

#endif /* GESTIONNAIRECHAT_H_ */
