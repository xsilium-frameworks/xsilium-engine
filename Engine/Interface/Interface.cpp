#ifndef INTERFACE_CPP_
#define INTERFACE_CPP_
#include "Interface.h"

GuiInterface::GuiInterface()
{
	isActived = true;
	parent = NULL;
	eventManager = new EventManager();
	d_root = NULL;
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
	return isActived;
}

void GuiInterface::activeInterface()
{
	d_root->setAlpha(1);
	isActived = true;
	d_root->setAlwaysOnTop(true);
}

void GuiInterface::desactiveInterface()
{
	d_root->setAlpha(0.5);
	d_root->setAlwaysOnTop(false);
	isActived = false;
}

void GuiInterface::setEvent(const char * typeEvent,const char * message)
{
	Event event;
	std::string typeEvent_str(typeEvent);
	std::string message_str(message);
	event.setProperty("eventType",typeEvent_str);
	event.setProperty("eventData",message_str);
	eventManager->addEvent(event);
}

CEGUI::Window* GuiInterface::getWindow()
{
	return d_root;
}

#endif /* INTERFACE_CPP_ */
