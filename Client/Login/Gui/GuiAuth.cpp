/*
 * \file GuiAuth.cpp
 *
 *  Created on: \date 2 sept. 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GuiAuth.h"

GuiAuth::GuiAuth() {
	loginWindow = 0;
}

GuiAuth::~GuiAuth() {
	if(loginWindow)
	{
		loginWindow->destroy();
		CEGUI::WindowManager::getSingleton().destroyWindow(loginWindow);
	}
}

void GuiAuth::processEvent(Event* event)
{

}

void GuiAuth::initGui()
{
	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	loginWindow = winMgr.loadLayoutFromFile("Login.layout");
//	loginWindow->getChild("btnConnexion")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiLogin::connexionButton, this));
//	loginWindow->getChild("btnQuitter")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiLogin::quitterButton, this));
	parent->addChild(loginWindow);
}

