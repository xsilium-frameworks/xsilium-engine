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

#include "GameState/GameStateManager.h"

enum eventTypeProgression
{
	PROGRESSION = LASTIDEVENTTYPE
};

enum eventprogression
{
	CANCELBOUTON = 1
};

/*
 *
 */
class GuiProgression : public GuiInterface
{
public:
	GuiProgression(ControleInterface * controleInterface);
	virtual ~GuiProgression();

    bool connexionAnnuler(const CEGUI::EventArgs &e);

    void processProgression(Event * event);

	void update();

private:
	ControleInterface * controleInterface ;

};

#endif /* GUIPROGRESSION_H_ */
