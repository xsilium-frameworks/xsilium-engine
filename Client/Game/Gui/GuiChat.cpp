/*
 * \file GuiChat.cpp
 *
 *  Created on: \date 4 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "GuiChat.h"

GuiChat::GuiChat() {
	chatWindow = 0;
	chatActif = false;
	d_historyPos = 0;

}

GuiChat::~GuiChat() {
	if(chatWindow)
	{
		chatWindow->destroy();
		CEGUI::WindowManager::getSingleton().destroyWindow(chatWindow);
	}
}

void GuiChat::processEvent(Event* event)
{
	if(event->hasProperty("CHAT"))
	{
		writeMessage(event);
	}
	if(event->hasProperty("Keyboard"))
	{
		if( (event->getProperty("Fonction").compare("ENTREE")) == 0 )
		{
			if(atoi(event->getProperty("Action").c_str()) == 1)
			{
				sendMessage();
			}
		}
	}

}

void GuiChat::writeMessage(Event* event)
{
	if (event->hasProperty("Perso") && event->hasProperty("Message"))
	{
		std::string message = event->getProperty("Perso") + " > " + event->getProperty("Message");
		// add this entry to the command history buffer
		d_history.push_back(message);
		// reset history position
		d_historyPos = d_history.size();
		// append newline to this entry
		message += '\n';
		// get history window
		CEGUI::MultiLineEditbox* history = static_cast<CEGUI::MultiLineEditbox*>(chatWindow->getChild("ListOfMessage"));
		// append new text to history output
		history->setText(history->getText() + message);
		// scroll to bottom of history output
		history->setCaretIndex(static_cast<size_t>(-1));
	}

}

void GuiChat::initGui()
{
	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	chatWindow =  winMgr.loadLayoutFromFile("Console.layout");

	parent->subscribeEvent(CEGUI::Window::EventMouseButtonDown, CEGUI::Event::Subscriber(&GuiChat::handleMouse, this));

	parent->addChild(chatWindow);

	hideChat();
}

bool GuiChat::handleMouse(const CEGUI::EventArgs& args)
{
	hideChat();
	return true;
}

void GuiChat::hideChat()
{
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(chatWindow->getChild("Editbox"));
	editbox->deactivate();
	chatWindow->deactivate();
}

void GuiChat::showSaisi()
{
	chatWindow->activate();
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(chatWindow->getChild("Editbox"));
	editbox->activate();
}

void GuiChat::sendMessage()
{
	Event event ;
	event.setProperty("CHAT","1");
	event.setProperty("Message",chatWindow->getChild("Editbox")->getText().c_str());
	Engine::Engine::getInstance()->addEvent(event);
}

void GuiChat::historiqueHaut()
{
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(chatWindow->getChild("Editbox"));
	d_historyPos = ceguimax(d_historyPos - 1, -1);
	if (d_historyPos >= 0)
	{
		editbox->setText(d_history[d_historyPos]);
		editbox->setCaretIndex(static_cast<size_t>(-1));
	}
	else
	{
		editbox->setText("");
	}

	editbox->activate();
}
void GuiChat::historiqueBas()
{
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(chatWindow->getChild("Editbox"));
	d_historyPos = ceguimin(d_historyPos + 1, static_cast<int>(d_history.size()));
	if (d_historyPos < static_cast<int>(d_history.size()))
	{
		editbox->setText(d_history[d_historyPos]);
		editbox->setCaretIndex(static_cast<size_t>(-1));
	}
	else
	{
		editbox->setText("");
	}

	editbox->activate();
}
