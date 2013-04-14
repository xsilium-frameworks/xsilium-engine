/*
 * \file Authentification.cpp
 *
 *  Created on: \date 13 avr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Authentification.h"

Authentification::Authentification() {

	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	d_root = winMgr.loadLayoutFromFile("XsiliumLogin.layout");

	frame = d_root->getChild("LoginForm");

	popupLogin = d_root->getChild("PopUp");

	popupProg = d_root->getChild("PopUpLoading");

	popupLogin->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,CEGUI::Event::Subscriber(&Authentification::CloseButton, this));

	popupLogin->getChild("Button")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&Authentification::CloseButton, this));

	frame->getChild("btnConnexion")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&Authentification::PushConnexion, this));


	CEGUI::ProgressBar* progressBar = static_cast<CEGUI::ProgressBar*>(popupProg->getChild("ProgressBar"));
	progressBar->setProgress(0.25);
	progressBar->setStepSize(0.25);

	// attach this window if parent is valid
	parent->addChild(d_root);

	frame->getChild("edtUsername")->activate();

}

Authentification::~Authentification() {
	// TODO Auto-generated destructor stub
}

bool Authentification::handleKeyDown(const CEGUI::EventArgs& args)
{
	const CEGUI::KeyEventArgs& keyEvent = static_cast<const CEGUI::KeyEventArgs&>(args);

	if (CEGUI::Key::Escape == keyEvent.scancode)
	switch(keyEvent.scancode)
	{
	case CEGUI::Key::Tab:
		frame->getChild("edtPassword")->activate();
		break;
	case CEGUI::Key::Return:
		frame->setAlpha(0.5);
		popupProg->setVisible("true");
		popupProg->activate();
		popupProg->setAlwaysOnTop(true);
		auth->setLoginPwd(frame->getChild("edtUsername")->getText().c_str(),frame->getChild("edtPassword")->getText().c_str());
		break;
	}
	return true;
}

void Authentification::update()
{
	Event * event = eventManager->getEvent();

	if(event != NULL)
	{
		switch(atoi(event->getProperty("eventType").c_str()))
		{
		case 0:
			processMessage(event);
			break;
		case 1:
			processProgression(event);
			break;
		default:
			break;
		}
		eventManager->removeEvent();
	}
}

void Authentification::setMessage(int typeMessage ,int message)
{
	Event event;
	event.setProperty("eventType",ToString(MESSAGE));
	event.setProperty("typeMessage",ToString(typeMessage));
	event.setProperty("message",ToString(message));

	eventManager->addEvent(event);
}

void Authentification::setProgression(int progression)
{
	Event event;
	event.setProperty("eventType",ToString(PROGRESSION));
	event.setProperty("progression",ToString(progression));
	eventManager->addEvent(event);
}

void Authentification::processProgression(Event * event)
{
	CEGUI::ProgressBar* progressBar = static_cast<CEGUI::ProgressBar*>(popupProg->getChild("ProgressBar"));
	progressBar->setProgress( (float)(atof(event->getProperty("progression").c_str()) / 4 ));
}

void Authentification::processMessage(Event * event)
{
	if ((messageFlag == false) && (!popupLogin->isActive()))
	{
		popupProg->setVisible(false);
		messageFlag = true;
		switch (atoi(event->getProperty("typeMessage").c_str()))
		{
		case 0:
			switch (atoi(event->getProperty("message").c_str()))
			{
			case 1:
				popupLogin->getChild("lblMessage")->setText("Les serveur est full dsl ");
				break;
			case 2:
				popupLogin->getChild("lblMessage")->setText("Impossible de se connecter au serveur");
				break;

			case 3:
				popupLogin->getChild("lblMessage")->setText("Déconnexion réussie");
				break;

			default:
				popupLogin->getChild("lblMessage")->setText("Erreur inconnue");
				break;
			}
			break;
			case 1:
				switch (atoi(event->getProperty("message").c_str() ))
				{
				case ID_INVALID_ACCOUNT_OR_PASSWORD:
					popupLogin->getChild("lblMessage")->setText("Le login ou le mot de passe est incorrecte .");
					break;
				case ID_CONNECTION_BANNED:
					popupLogin->getChild("lblMessage")->setText("Votre IP a ete banni .\n Il est imposible de se connecter .");
					break;

				case ID_COMPTE_BANNIE:
					popupLogin->getChild("lblMessage")->setText("Votre Compte a ete banni . \n Il est impossible de se connecter .");
					break;
				case ID_SEND_VALIDATION:
					popupLogin->getChild("lblMessage")->setText("Vous avez correctement ete authentifier .");
					break;

				default:
					popupLogin->getChild("lblMessage")->setText("Erreur inconnue");

					break;
				}
				break;
				default:
					popupLogin->getChild("lblMessage")->setText("Erreur inconnue");
					break;
		}
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
	auth->setLoginPwd(frame->getChild("edtUsername")->getText().c_str(),frame->getChild("edtPassword")->getText().c_str());
	return true;
}

bool Authentification::CloseButton(const CEGUI::EventArgs &e)
{
	popupLogin->setVisible(false);
	frame->setAlpha(1.0);
	frame->getChild("edtUsername")->activate();
	return true;

}
