/*
 * \file GuiChat.h
 *
 *  Created on: \date 4 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef CLIENT_GAME_GUI_GUICHAT_H_
#define CLIENT_GAME_GUI_GUICHAT_H_

#include "Engine/Gui/GuiListenner.h"
#include <vector>

/*
 *
 */
class GuiChat : public Engine::GuiListenner {
public:
	GuiChat();
	virtual ~GuiChat();

	void processEvent(Event* event);

	void initGui();

	void showSaisi();
	void hideChat();

	void writeMessage(Event* event);
	void sendMessage();

	bool handleMouse(const CEGUI::EventArgs& args);

	void historiqueHaut();
	void historiqueBas();

private:
	CEGUI::Window* chatWindow;

	bool chatActif;

	int d_historyPos;
	std::vector<CEGUI::String> d_history;
};

#endif /* CLIENT_GAME_GUI_GUICHAT_H_ */
