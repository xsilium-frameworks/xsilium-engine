#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "EventManager/EventManager.h"

#include "Interface/ControleInterface.h"

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

	bool activeInterface(const CEGUI::EventArgs &ea);
	bool desactiveInterface(const CEGUI::EventArgs &ea);

	void initEventInterface();

	bool isActive();

	void setEvent(const char * typeEvent,const char * message = "");

	virtual void update() = 0;

	void EventGlobal();

	void setIDInterface(int IDInterface);
	const int getIDInterface();

	void setControleur(ControleInterface * controleInterface);
	ControleInterface * getControleur();

	CEGUI::Window* getWindow();


protected:
	int IDInterface;
    CEGUI::Window* d_root;
    CEGUI::Window* parent;
    EventManager * eventManager ;
    ControleInterface * controleInterface ;

    bool isActived;
};

#endif /* INTERFACE_H_ */
