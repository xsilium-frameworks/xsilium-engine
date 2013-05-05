/*
 * \file Authentification.h
 *
 *  Created on: \date 13 avr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef AUTHENTIFICATION_H_
#define AUTHENTIFICATION_H_

#include "Interface/Interface.h"
#include "Authentification/GestionnaireAuth.h"

#include "GameState/GameStateManager.h"


enum eventType
{
	MESSAGE = 0,
	PROGRESSION
};

/*
 *
 */
class Authentification : public Interface
{
public:
	Authentification();
	virtual ~Authentification();

    void processMessage(Event * event);
    void processProgression(Event * event);

    bool PushConnexion(const CEGUI::EventArgs &e);
    bool CloseButton(const CEGUI::EventArgs &e);


    bool handleKeyUp(const CEGUI::EventArgs& args);

    void update();

private:
	CEGUI::Window* frame;
	CEGUI::Window* popupLogin;
	CEGUI::Window* popupProg;

	CEGUI::Event::Connection connectionGlobalEvent;

	GestionnaireAuth * gestionnaireAuth ;

	bool messageFlag;
};

#endif /* AUTHENTIFICATION_H_ */
