/*
 * \file GuiProgression.h
 *
 *  Created on: \date 15 aožt 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GUIPROGRESSION_H_
#define GUIPROGRESSION_H_


#include "Interface/Interface.h"
#include "Authentification/GestionnaireAuth.h"

#include "GameState/GameStateManager.h"

class GestionnaireAuth;

enum eventTypeProgression
{
	PROGRESSION = 2
};

/*
 *
 */
class GuiProgression : public GuiInterface
{
public:
	GuiProgression(GestionnaireAuth * gestionnaireAuth);
	virtual ~GuiProgression();

    bool connexionAnnuler(const CEGUI::EventArgs &e);

    void processProgression(Event * event);

	void update();

private:
	GestionnaireAuth * gestionnaireAuth ;

};

#endif /* GUIPROGRESSION_H_ */
