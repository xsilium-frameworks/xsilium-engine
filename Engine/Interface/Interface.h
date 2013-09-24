#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "EventManager/EventManager.h"

enum eventType
{
	ACTIVE = 0,
	DESACTIVE,
	VISIBLE,
	INVISIBLE,
	LASTIDEVENTTYPE
};

class GuiInterface
{

public:
	GuiInterface();
	virtual ~GuiInterface();

	void setVisibility(bool visibility);
	bool isVisible() const;

	void activeInterface();
	void desactiveInterface();

	bool isActive();

	void setEvent(const char * typeEvent,const char * message = "");

	virtual void update() = 0;

	void EventGlobal();

	CEGUI::Window* getWindow();


protected:
    CEGUI::Window* d_root;
    CEGUI::Window* parent;
    EventManager * eventManager ;

    bool isActived;
};

#endif /* INTERFACE_H_ */
