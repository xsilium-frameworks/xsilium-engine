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
	messageErreurActif = false;
	progressionActif = false;
	loginActif = false;
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
				if(loginActif)
				{
					validationAuth();
				}
				if(progressionActif)
				{
					hideProgression();
					showLogin();
				}
				if(messageErreurActif)
				{
					hideErreur();
					showLogin();
				}
			}
		}
	}

	if(event->hasProperty("AUTH"))
	{
		if(event->hasProperty("ErreurMessage"))
		{
			genererErreur(event);
		}

		if(event->hasProperty("Progression"))
		{
			updateProgression(event);
		}

	}

}

void GuiAuth::initGui()
{
	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	loginWindow =  winMgr.loadLayoutFromFile("login.layout");
	erreurWindow = winMgr.loadLayoutFromFile("error.layout");
	progressionWindow = winMgr.loadLayoutFromFile("progressBar.layout");

	loginWindow->getChild("btnConnexion")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiAuth::validButton, this));
	loginWindow->getChild("btnQuitter")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiAuth::cancelButton, this));

	progressionWindow->getChild("ButtonAnnuler")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiAuth::cancelButton, this));

	erreurWindow->getChild("ButtonOK")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GuiAuth::validButton, this));


	parent->addChild(loginWindow);
	parent->addChild(erreurWindow);
	parent->addChild(progressionWindow);

	showLogin();
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
		event.setProperty("AUTH","1");
		event.setProperty("Fonction","QUIT");
		Engine::EventManager::getInstance()->addEvent(event);
	}
	if (senderID == "ButtonAnnuler")
	{
		hideProgression();
		showLogin();
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
	if (senderID == "ButtonOK")
	{
		hideErreur();
		showLogin();
	}
	return true;
}

void GuiAuth::validationAuth()
{
	Event event ;
	event.setProperty("AUTH","1");
	event.setProperty("Login",loginWindow->getChild("edtUsername")->getText().c_str());
	event.setProperty("PassWord",loginWindow->getChild("edtPassword")->getText().c_str());
	Engine::EventManager::getInstance()->addEvent(event);
	loginWindow->getChild("edtUsername")->setText("");
	loginWindow->getChild("edtPassword")->setText("");

}

void GuiAuth::genererErreur(Event * event)
{
	if (messageErreurActif == false)
	{
		hideProgression();
		hideLogin();

		erreurWindow->getChild("lblMessage")->setText(event->getProperty("ErreurMessage").c_str());
		showErreur();
	}
}

void GuiAuth::updateProgression(Event * event)
{
	CEGUI::ProgressBar* progressBar = static_cast<CEGUI::ProgressBar*>(progressionWindow->getChild("ProgressBar"));
	progressBar->setProgress( (float)(atof(event->getProperty("Progression").c_str()) / atof(event->getProperty("ProgressionTotal").c_str()) ));
	if(!progressionActif)
	{
		hideLogin();
		showProgression();
	}
}

void GuiAuth::showLogin()
{
	if(!loginActif)
	{
		loginWindow->setAlpha(1);
		loginWindow->setAlwaysOnTop(true);
		loginWindow->setVisible(true);
		loginWindow->activate();
		loginActif = true;
	}
}
void GuiAuth::hideLogin()
{
	if(loginActif)
	{
		loginWindow->setAlpha(0.3);
		loginWindow->setAlwaysOnTop(false);
		loginWindow->deactivate();
		loginActif = false;
	}
}

void GuiAuth::showErreur()
{
	if(!messageErreurActif)
	{
		erreurWindow->setAlpha(1);
		erreurWindow->setAlwaysOnTop(true);
		messageErreurActif = true;
		erreurWindow->setVisible(true);
		erreurWindow->activate();
	}
}
void GuiAuth::hideErreur()
{
	if(messageErreurActif)
	{
		erreurWindow->setAlpha(0.3);
		erreurWindow->setAlwaysOnTop(false);
		messageErreurActif = false;
		erreurWindow->setVisible(false);
		erreurWindow->deactivate();
	}
}

void GuiAuth::showProgression()
{
	if(!progressionActif)
	{
		progressionWindow->setAlpha(1);
		progressionWindow->setAlwaysOnTop(true);
		progressionActif = true;
		progressionWindow->setVisible(true);
		progressionWindow->activate();
	}
}
void GuiAuth::hideProgression()
{
	if(progressionActif)
	{
		progressionWindow->setAlpha(0.3);
		progressionWindow->setAlwaysOnTop(false);
		progressionActif = false;
		progressionWindow->setVisible(false);
		progressionWindow->deactivate();
	}
}

