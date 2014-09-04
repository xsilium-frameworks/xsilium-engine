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

    bool connexionButton(const CEGUI::EventArgs &e);
    bool quitterButton(const CEGUI::EventArgs &e);

    void switchEditBox();

    const char * getLogin();
    const char * getPassword();



    void processEvent();

private:

	CEGUI::Window* loginWindow;
};

#endif /* GUIAUTH_H_ */
