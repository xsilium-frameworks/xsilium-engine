/*
 * \file GuiErreur.h
 *
 *  Created on: \date 15 aožt 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GUIERREUR_H_
#define GUIERREUR_H_

#include "Interface/Interface.h"

#include "GameState/GameStateManager.h"

enum eventTypeErreur
{
	MESSAGE = LASTIDEVENTTYPE
};

enum eventerreur
{
	OKBOUTON = 1
};

/*
 *
 */
class GuiErreur : public GuiInterface
{
public:
	GuiErreur(ControleInterface * controleInterface);
	virtual ~GuiErreur();

	bool okButton(const CEGUI::EventArgs &e);

	void processMessage(Event * event);

	void update();

private:
	bool messageFlag;
};

#endif /* GUIERREUR_H_ */
