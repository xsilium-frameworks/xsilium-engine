/*
 * \file GuiErreur.cpp
 *
 *  Created on: \date 15 ao�t 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GuiErreur.h"

GuiErreur::GuiErreur() {

	messageFlag = false;
	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());
	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	d_root = winMgr.loadLayoutFromFile("Error.layout");
	d_root->getChild("ButtonOK")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiErreur::okButton, this));

	// attach this window if parent is valid
	parent->addChild(d_root);

	EventEnregistre.push_back(NOTIFICATION);

	initEventInterface();

}

GuiErreur::~GuiErreur() {
	if(d_root)
	{
		d_root->destroy();
		CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
	}
}

bool GuiErreur::okButton(const CEGUI::EventArgs &e)
{
	messageFlag = false;
	d_root->setVisible(false);
	controleInterface->retourInterface(NOTIFICATION,OKBOUTON);
	return true;
}

void GuiErreur::processMessage(Event * event)
{
	if (messageFlag == false)
	{
		messageFlag = true;
		d_root->getChild("lblMessage")->setText(event->getProperty("eventData").c_str());
		d_root->setVisible(true);
		d_root->activate();
	}
}

void GuiErreur::update()
{
	Event * event = eventManager->getEvent();

	if(event != NULL)
	{
		switch(atoi(event->getProperty("eventType").c_str()))
		{
		case MESSAGE:
			processMessage(event);
			deleteEvent = true;
			break;
		default:
			break;
		}
		GuiInterface::EventGlobal();
	}
}
