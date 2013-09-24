/*
 * \file Authentification.cpp
 *
 *  Created on: \date 13 avr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GuiLogin.h"

GuiLogin::GuiLogin(GestionnaireAuth * gestionnaireAuth) {

	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());
	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	d_root = winMgr.loadLayoutFromFile("Login.layout");
	d_root->getChild("btnConnexion")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiLogin::connexionButton, this));
	d_root->getChild("btnQuitter")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiLogin::quitterButton, this));


	// attach this window if parent is valid
	parent->addChild(d_root);

	this->gestionnaireAuth = gestionnaireAuth ;
}

GuiLogin::~GuiLogin() {
	if(d_root)
	{
		d_root->destroy();
		CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
	}
}

void GuiLogin::switchEditBox()
{
	if(d_root->getChild("edtUsername")->isActive())
		d_root->getChild("edtPassword")->activate();
	else
		d_root->getChild("edtUsername")->activate();
}

void GuiLogin::update()
{
	Event * event = eventManager->getEvent();

	if(event != NULL)
	{
		GuiInterface::EventGlobal();
		switch(atoi(event->getProperty("eventType").c_str()))
		{
		default:
			break;
		}
		eventManager->removeEvent();
	}
}

const char * GuiLogin::getLogin()
{
	return d_root->getChild("edtUsername")->getText().c_str() ;
}

const char * GuiLogin::getPassword()
{
	return d_root->getChild("edtPassword")->getText().c_str() ;
}

bool GuiLogin::quitterButton(const CEGUI::EventArgs &e)
{
	gestionnaireAuth->quitAuthentification();
	return true;
}

bool GuiLogin::connexionButton(const CEGUI::EventArgs &e)
{
	gestionnaireAuth->setAuthentification();
	return true;
}
