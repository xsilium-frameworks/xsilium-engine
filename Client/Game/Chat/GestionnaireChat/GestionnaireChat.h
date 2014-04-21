/*
 * \file GestionnaireChat.h
 *
 *  Created on: \date 16 févr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIRECHAT_H_
#define GESTIONNAIRECHAT_H_

#include "Network/NetworkManager.h"

#include "Interface/GestionnaireInterface.h"
#include "Interface/GuiChat.h"

#include "Game/JeuxState.h"

#include "Network/Opcode/Opcode.h"

#include "Game/Chat/StructurePacket/PacketChat.h"

#include "Compte/Compte.h"

#include "ModuleActif/ModuleActif.h"

class Chat;
class JeuxState;

/*
 *
 */
class GestionnaireChat : public ModuleActif , public ControleInterface , public OIS::KeyListener {
public:
	GestionnaireChat(JeuxState * jeuxState);
	virtual ~GestionnaireChat();

	void run();

	void processPacket(ENetEvent * packet);

	void retourInterface(int IDInterface,int retour);

	void sendMessageToChat(const char * message, int to);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);


private:
	NetworkManager * networkManager;
	Chat * guichat;
	Compte * compte;
	JeuxState * jeuxState;
	GestionnaireInterface * gestionnaireInterface;

	KeyboardMap * keyboardMap ;
	InputManager * inputManager;

};

#endif /* GESTIONNAIRECHAT_H_ */
