#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

class Interface
{

public:
	Interface();
	~Interface();

	void initialiseDefaultResourceGroups();
	void setupCEGUI();

private:
	CEGUI::OgreRenderer* mRenderer;

};

#endif /* INTERFACE_H_ */
