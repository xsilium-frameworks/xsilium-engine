#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "EventManager/EventManager.h"

class Interface
{

public:
	Interface();
	~Interface();

	void setupCEGUI();

	void toggleVisibility();
	bool isVisible() const;

	bool isActive();

	void update();


protected:
    CEGUI::Window* d_root;
    CEGUI::Window* parent;
    EventManager * eventManager ;

    bool isActived;

private:
    CEGUI::OgreRenderer* mRenderer;

};

#endif /* INTERFACE_H_ */
