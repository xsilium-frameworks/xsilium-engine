/*
 * \file GuiAuth.h
 *
 *  Created on: \date 2 sept. 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GUIAUTH_H_
#define GUIAUTH_H_

#include "Engine/Gui/GuiListenner.h"


/*
 *
 */
class GuiAuth : public Engine::GuiListenner {
public:
	GuiAuth();
	virtual ~GuiAuth();

	void processEvent(Event* event);

	void initGui();

    bool validButton(const CEGUI::EventArgs &e);
    bool cancelButton(const CEGUI::EventArgs &e);

    void switchEditBox();

    void validationAuth();
    void genererErreur(Event * event);
    void updateProgression(Event * event);

    void showLogin();
    void hideLogin();

    void showErreur();
    void hideErreur();

    void showProgression();
    void hideProgression();

private:

	CEGUI::Window* loginWindow;
	CEGUI::Window* progressionWindow;
	CEGUI::Window* erreurWindow;

	bool messageErreurActif;
	bool progressionActif;
	bool loginActif;

};

#endif /* GUIAUTH_H_ */
