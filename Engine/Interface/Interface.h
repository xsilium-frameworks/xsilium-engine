#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

class Interface : public Ogre::Singleton<OgreFramework>
{

public:
	Interface();
	~Interface();

protected:
	CEGUI::OgreRenderer* mRenderer;
    void initialiseDefaultResourceGroups();
    void setupCEGUI();

};

#endif /* INTERFACE_H_ */
