#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "AppState.h"

class MenuState : public AppState
{
public:
    MenuState();

	DECLARE_APPSTATE_CLASS(MenuState)

	void enter();
	void createScene();
	void exit();


//	void buttonHit(OgreBites::Button* button);

	void update(double timeSinceLastFrame);

private:
	bool m_bQuit;
};

#endif
