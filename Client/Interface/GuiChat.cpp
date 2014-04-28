#include "GuiChat.h"
//Chat class


Chat::Chat(ControleInterface * controleInterface)
{

	d_historyPos = 0;
	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());
	parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	d_root = winMgr.loadLayoutFromFile("Console.layout");
	d_root->setDestroyedByParent(false);


	parent->subscribeEvent(CEGUI::Window::EventMouseButtonDown, CEGUI::Event::Subscriber(&Chat::handleMouse, this));

	// attach this window if parent is valid
	parent->addChild(d_root);

	this->controleInterface = controleInterface ;

	initEventInterface();
}

Chat::~Chat()
{
	if(d_root)
	{
		CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
		d_root->destroy();
	}
}

bool Chat::saisiActiver()
{
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(d_root->getChild("Editbox"));
	return editbox->isActive() ;
}

void Chat::activeSaisi()
{
	d_root->activate();
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(d_root->getChild("Editbox"));
	editbox->activate();

}

void Chat::processMessage(Event * event)
{
	using namespace CEGUI;

	const char * message = event->getProperty("eventData").c_str() ;

	String messageChat(message);

	// add this entry to the command history buffer
	d_history.push_back(messageChat);
	// reset history position
	d_historyPos = d_history.size();
	// append newline to this entry
	message += '\n';
	// get history window
	MultiLineEditbox* history = static_cast<MultiLineEditbox*>(d_root->getChild("ListOfMessage"));
	// append new text to history output
	history->setText(history->getText() + messageChat);
	// scroll to bottom of history output
	history->setCaretIndex(static_cast<size_t>(-1));

}

void Chat::effaceSaisi()
{
	// get the text entry editbox
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(d_root->getChild("Editbox"));
	editbox->setText("");
	editbox->deactivate();

}

const char * Chat::getSaisi()
{
	return d_root->getChild("Editbox")->getText().c_str();
}

void Chat::historiqueHaut()
{
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(d_root->getChild("Editbox"));
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
void Chat::historiqueBas()
{
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(d_root->getChild("Editbox"));
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

bool Chat::handleMouse(const CEGUI::EventArgs& args)
{
	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(d_root->getChild("Editbox"));
	editbox->deactivate();
	d_root->deactivate();

	return true;
}


void Chat::update()
{
	Event * event = eventManager->getEvent();

	if(event != NULL)
	{
		GuiInterface::EventGlobal();
		switch(atoi(event->getProperty("eventType").c_str()))
		{
		case ALL:
			processMessage(event);
			break;
		default:
			break;
		}
		eventManager->removeEvent();
	}
}
