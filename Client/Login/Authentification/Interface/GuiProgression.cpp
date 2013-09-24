/*
 * \file GuiProgression.cpp
 *
 *  Created on: \date 15 aožt 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GuiProgression.h"

GuiProgression::GuiProgression(GestionnaireAuth * gestionnaireAuth) {

	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());
	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	d_root = winMgr.loadLayoutFromFile("progressBar.layout");
	d_root->getChild("ButtonAnnuler")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiProgression::connexionAnnuler, this));
	// attach this window if parent is valid
	parent->addChild(d_root);

	this->gestionnaireAuth = gestionnaireAuth ;

}

GuiProgression::~GuiProgression() {
	if(d_root)
	{
		d_root->destroy();
		CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
	}
}

bool GuiProgression::connexionAnnuler(const CEGUI::EventArgs &e)
{
	gestionnaireAuth->cancelAuthentification();
	return true;
}

void GuiProgression::processProgression(Event * event)
{
	CEGUI::ProgressBar* progressBar = static_cast<CEGUI::ProgressBar*>(d_root->getChild("ProgressBar"));
	progressBar->setProgress( (float)(atof(event->getProperty("eventData").c_str()) / 4 ));
}


void GuiProgression::update()
{
	Event * event = eventManager->getEvent();

	if(event != NULL)
	{
		switch(atoi(event->getProperty("eventType").c_str()))
		{
		case PROGRESSION:
			processProgression(event);
			break;
		default:
			break;
		}
		eventManager->removeEvent();
	}
}
