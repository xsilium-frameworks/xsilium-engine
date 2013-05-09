/*
 * \file Authentification.cpp
 *
 *  Created on: \date 13 avr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Authentification.h"

Authentification::Authentification() {

	eventManager = new EventManager();
	messageFlag = false;

	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	d_root = winMgr.loadLayoutFromFile("Login.layout");

	frame = d_root->getChild("LoginForm");

	popupLogin = d_root->getChild("PopUp");

	popupProg = d_root->getChild("PopUpLoading");

	popupLogin->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,CEGUI::Event::Subscriber(&Authentification::CloseButton, this));

	popupLogin->getChild("Button")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&Authentification::CloseButton, this));

	frame->getChild("btnConnexion")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&Authentification::PushConnexion, this));


	parent->subscribeEvent(CEGUI::FrameWindow::EventKeyUp,CEGUI::Event::Subscriber(&Authentification::handleKeyUp, this));


	CEGUI::ProgressBar* progressBar = static_cast<CEGUI::ProgressBar*>(popupProg->getChild("ProgressBar"));
	progressBar->setProgress(0.25);
	progressBar->setStepSize(0.25);

	// attach this window if parent is valid
	parent->addChild(d_root);


	parent->activate();

	gestionnaireAuth = new GestionnaireAuth(this);

}

Authentification::~Authentification() {
	if(d_root)
	{
		CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
		d_root->destroy();
	}
	delete gestionnaireAuth ;
	delete eventManager;
}

bool Authentification::handleKeyUp(const CEGUI::EventArgs& args)
{
	const CEGUI::KeyEventArgs& keyEvent = static_cast<const CEGUI::KeyEventArgs&>(args);

	switch(keyEvent.scancode)
	{
	case CEGUI::Key::Tab:
		if(frame->getChild("edtUsername")->isActive())
			frame->getChild("edtPassword")->activate();
		else
			frame->getChild("edtUsername")->activate();
		break;
	case CEGUI::Key::Return:
		frame->setAlpha(0.5);
		popupProg->setVisible("true");
		popupProg->activate();
		popupProg->setAlwaysOnTop(true);
		gestionnaireAuth->setLoginPwd(frame->getChild("edtUsername")->getText().c_str(),frame->getChild("edtPassword")->getText().c_str());
		break;
	default:
		break;
	}
	return true;
}

void Authentification::update()
{
	if( static_cast<CEGUI::ProgressBar*>(popupProg->getChild("ProgressBar"))->getProgress() == 1.0f)
	{
		GameStateManager*	m_pGameStateManager = GameStateManager::getInstance();
		m_pGameStateManager->changeGameState(m_pGameStateManager->findByName("JeuxState"));
		return;
	}

	if(eventManager)
	{

		Event * event = eventManager->getEvent();

		if(event != NULL)
		{
			switch(atoi(event->getProperty("eventType").c_str()))
			{
			case MESSAGE:
				processMessage(event);
				break;
			case PROGRESSION:
				processProgression(event);
				break;
			default:
				break;
			}
			eventManager->removeEvent();
		}
	}
}

void Authentification::processProgression(Event * event)
{
	CEGUI::ProgressBar* progressBar = static_cast<CEGUI::ProgressBar*>(popupProg->getChild("ProgressBar"));
	progressBar->setProgress( (float)(atof(event->getProperty("eventData").c_str()) / 4 ));
}

void Authentification::processMessage(Event * event)
{
	if ((messageFlag == false) && (!popupLogin->isActive()))
	{
		popupProg->setVisible(false);
		messageFlag = true;
		popupLogin->getChild("lblMessage")->setText(event->getProperty("eventData").c_str());
		popupLogin->setVisible("true");
		popupLogin->activate();
		popupLogin->setAlwaysOnTop(true);

	}
}


bool Authentification::PushConnexion(const CEGUI::EventArgs &e)
{
	frame->setAlpha(0.5);
	popupProg->setVisible("true");
	popupProg->activate();
	popupProg->setAlwaysOnTop(true);
	gestionnaireAuth->setLoginPwd(frame->getChild("edtUsername")->getText().c_str(),frame->getChild("edtPassword")->getText().c_str());
	return true;
}

bool Authentification::CloseButton(const CEGUI::EventArgs &e)
{
	popupLogin->setVisible(false);
	frame->setAlpha(1.0);
	frame->getChild("edtUsername")->activate();
	return true;

}
