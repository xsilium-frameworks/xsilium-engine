#ifndef INTERFACE_CPP_
#define INTERFACE_CPP_
#include "Interface.h"

GuiInterface::GuiInterface()
{
	isActived = false;
	parent = NULL;
}

GuiInterface::~GuiInterface()
{
}

void GuiInterface::toggleVisibility()
{
	d_root->isVisible() ? d_root->hide() : d_root->show();
}

bool GuiInterface::isVisible() const
{
	return d_root->isEffectiveVisible();
}

bool GuiInterface::isActive()
{
	return isActived;
}

void GuiInterface::initialisationInterface()
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


void GuiInterface::interfacePrincipal()
{

	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

	CEGUI::Window* parent = winMgr.createWindow("DefaultWindow", "InterfaceG");

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(parent);

}

void GuiInterface::deleteInterfacePrincipal()
{
	CEGUI::Window * parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::WindowManager::getSingleton().destroyWindow(parent);
	parent->destroy();
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

#endif /* INTERFACE_CPP_ */
