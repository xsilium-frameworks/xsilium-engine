#ifndef INTERFACE_CPP_
#define INTERFACE_CPP_
#include "Interface.h"

Interface::Interface()
{
	isActived = false;
}

Interface::~Interface()
{
	if(d_root)
	{
		CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
		d_root->destroy();
	}
}

void Interface::toggleVisibility()
{
	d_root->isVisible() ? d_root->hide() : d_root->show();
}

bool Interface::isVisible() const
{
	return d_root->isEffectiveVisible();
}

bool Interface::isActive()
{
	CEGUI::Window* windowActuel = CEGUI::System::getSingleton().getDefaultGUIContext().getWindowContainingMouse() ;
	if ( d_root == windowActuel or d_root->isChild(windowActuel) )
		isActived = true;
	else
		isActived = false;
	return isActived;
}

void Interface::initialisationInterface()
{
	CEGUI::OgreRenderer* mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    // set the default resource groups to be used
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeels");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("Lua_scripts");
    CEGUI::AnimationManager::setDefaultResourceGroup("Animations");
    // setup default group for validation schemas
    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");

    CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("AlfiskoSkin/MouseArrow");
}


void Interface::interfacePrincipal()
{

	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

	CEGUI::Window* parent = winMgr.createWindow("DefaultWindow", "InterfaceG");

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(parent);

}

void Interface::deleteInterfacePrincipal()
{
	CEGUI::Window * parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::WindowManager::getSingleton().destroyWindow(parent);
}


#endif /* INTERFACE_CPP_ */
