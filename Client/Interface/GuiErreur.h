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

/*
 *
 */
class GuiErreur : public GuiInterface
{
public:
	GuiErreur();
	virtual ~GuiErreur();

	bool okButton(const CEGUI::EventArgs &e);

	void processMessage(Event * event);

	void update();

private:
	bool messageFlag;
};

#endif /* GUIERREUR_H_ */
