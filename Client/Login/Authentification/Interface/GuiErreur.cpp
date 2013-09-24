/*
 * \file GuiErreur.cpp
 *
 *  Created on: \date 15 aožt 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GuiErreur.h"

GuiErreur::GuiErreur(GestionnaireAuth * gestionnaireAuth) {

	messageFlag = false;
	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());
	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	d_root = winMgr.loadLayoutFromFile("Error.layout");
	d_root->getChild("ButtonOK")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiErreur::okButton, this));

	// attach this window if parent is valid
	parent->addChild(d_root);

	this->gestionnaireAuth = gestionnaireAuth ;

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
	gestionnaireAuth->cancelAuthentification();
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

		GuiInterface::EventGlobal();
		switch(atoi(event->getProperty("eventType").c_str()))
		{
		case MESSAGE:
			processMessage(event);
			break;
		default:
			break;
		}
		eventManager->removeEvent();
	}
}
