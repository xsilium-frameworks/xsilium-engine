#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "EventManager/EventManager.h"

#include "Interface/ControleInterface.h"

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

	void setEvent(Event * event);

	virtual void update() = 0;

	void EventGlobal();

	const std::string getInterfaceName();

	void setControleur(ControleInterface * controleInterface);

	CEGUI::Window* getWindow();


	bool checkRegistreEvent(EventInterface * eventInterface);


protected:
	std::string name;
	CEGUI::Window* d_root;
	CEGUI::Window* parent;
	EventManager * eventManager ;
	ControleInterface * controleInterface;
	bool isActived;
	bool deleteEvent;

	std::vector<EventInterface> EventEnregistre;

};

#endif /* INTERFACE_H_ */
