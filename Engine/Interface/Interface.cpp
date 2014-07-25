#ifndef INTERFACE_CPP_
#define INTERFACE_CPP_
#include "Interface.h"

GuiInterface::GuiInterface()
{
	isActived = false;
	parent = NULL;
	eventManager = new EventManager();
	d_root = NULL;
	controleInterface = NULL;
	deleteEvent = false;

}

GuiInterface::~GuiInterface()
{
	if(eventManager)
		delete eventManager;
}

void GuiInterface::setVisibility(bool visibility)
{
	if(visibility)
		d_root->show();
	else
		d_root->hide();
}

bool GuiInterface::isVisible() const
{
	return d_root->isEffectiveVisible();
}

bool GuiInterface::isActive()
{
	return d_root->isActive();
}

bool GuiInterface::activeInterface(const CEGUI::EventArgs &ea)
{
	d_root->setAlpha(1);
	isActived = true;
	d_root->setAlwaysOnTop(true);
	return true;
}

bool GuiInterface::desactiveInterface(const CEGUI::EventArgs &ea)
{

	d_root->setAlpha(0.3);
	d_root->setAlwaysOnTop(false);
	isActived = false;

	return true;
}

void GuiInterface::setEvent(Event * event)
{
	eventManager->addEvent(*event);
}

CEGUI::Window* GuiInterface::getWindow()
{
	return d_root;
}


void GuiInterface::setControleur(ControleInterface * controleInterface)
{
	this->controleInterface = controleInterface;
}

bool GuiInterface::checkRegistreEvent(EventInterface * eventInterface)
{
	for (std::vector<EventInterface>::iterator it =EventEnregistre.begin() ; it!=EventEnregistre.end() ; ++it)
	{
		if (*it == *eventInterface)
		{
			return true;
		}
	}
	return false;
}

const std::string GuiInterface::getInterfaceName()
{
	return this->name;
}

void GuiInterface::EventGlobal()
{
	switch(atoi(eventManager->getEvent()->getProperty("eventType").c_str()))
	{
	case ACTIVE:
		d_root->activate();
		deleteEvent = true;
		break;
	case DESACTIVE:
		d_root->deactivate();
		deleteEvent = true;
		break;
	case VISIBLE:
		setVisibility(true);
		deleteEvent = true;
		break;
	case INVISIBLE:
		setVisibility(false);
		deleteEvent = true;
		break;
	default:
		break;
	}
	if(deleteEvent)
	{
		deleteEvent = false;
		eventManager->removeEvent();
	}
}

void GuiInterface::initEventInterface()
{
	d_root->subscribeEvent(CEGUI::Window::EventActivated,CEGUI::Event::Subscriber(&GuiInterface::activeInterface, this));
	d_root->subscribeEvent(CEGUI::Window::EventDeactivated,CEGUI::Event::Subscriber(&GuiInterface::desactiveInterface, this));
}

#endif /* INTERFACE_CPP_ */
