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
	progressionWindow = 0;
	erreurWindow = 0;
}

GuiAuth::~GuiAuth() {
	if(loginWindow)
	{
		loginWindow->destroy();
		CEGUI::WindowManager::getSingleton().destroyWindow(loginWindow);
	}
	if(erreurWindow)
	{
		erreurWindow->destroy();
		CEGUI::WindowManager::getSingleton().destroyWindow(erreurWindow);
	}
	if(progressionWindow)
	{
		progressionWindow->destroy();
		CEGUI::WindowManager::getSingleton().destroyWindow(progressionWindow);
	}
}

void GuiAuth::processEvent(Event* event)
{
	if(event->hasProperty("Keyboard"))
	{
		if( (event->getProperty("Fonction").compare("TABULATION")) == 0 )
		{
			if(atoi(event->getProperty("Action").c_str()) == 1)

			{
				switchEditBox();
			}
		}

		if( (event->getProperty("Fonction").compare("ENTREE")) == 0 )
		{
			if(atoi(event->getProperty("Action").c_str()) == 1)
			{
				validationAuth();
			}
		}
	}

}

void GuiAuth::initGui()
{
	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	loginWindow =  winMgr.loadLayoutFromFile("Login.layout");
	erreurWindow = winMgr.loadLayoutFromFile("Error.layout");
	progressionWindow = winMgr.loadLayoutFromFile("progressBar.layout");

	loginWindow->getChild("btnConnexion")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiAuth::validButton, this));
	loginWindow->getChild("btnQuitter")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiAuth::cancelButton, this));

	progressionWindow->getChild("ButtonAnnuler")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiAuth::cancelButton, this));

	erreurWindow->getChild("ButtonOK")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiAuth::cancelButton, this));


	parent->addChild(loginWindow);
	parent->addChild(erreurWindow);
	parent->addChild(progressionWindow);
}

void GuiAuth::switchEditBox()
{
	if(loginWindow->getChild("edtUsername")->isActive())
		loginWindow->getChild("edtPassword")->activate();
	else
		loginWindow->getChild("edtUsername")->activate();
}

bool GuiAuth::cancelButton(const CEGUI::EventArgs &e)
{
	const CEGUI::MouseEventArgs& we = static_cast<const CEGUI::MouseEventArgs&>(e);

	CEGUI::String senderID = we.window->getName();

	if (senderID == "btnQuitter")
	{
		Event event ;
		event.setProperty("GUI","1");
		event.setProperty("Fonction","QUIT");
		Engine::Engine::getInstance()->addEvent(event);
	}
	if (senderID == "ButtonAnnuler")
	{

	}
	return true;
}

bool GuiAuth::validButton(const CEGUI::EventArgs &e)
{
	const CEGUI::MouseEventArgs& we = static_cast<const CEGUI::MouseEventArgs&>(e);

	CEGUI::String senderID = we.window->getName();

	if (senderID == "btnConnexion")
	{
		validationAuth();
	}
	return true;
}

void GuiAuth::validationAuth()
{
	if(loginWindow->getChild("edtUsername")->getText().empty())
	{

		return;
	}

	if(loginWindow->getChild("edtPassword")->getText().empty())
	{
		return;
	}
	Event event ;
	event.setProperty("AUTH","1");
	event.setProperty("Login",loginWindow->getChild("edtUsername")->getText().c_str());
	event.setProperty("PassWord",loginWindow->getChild("edtPassword")->getText().c_str());
	Engine::Engine::getInstance()->addEvent(event);

}

