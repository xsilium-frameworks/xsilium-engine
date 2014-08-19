/*
 * \file GuiManager.cpp
 *
 *  Created on: \date 7 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GuiManager.h"

namespace Engine {

GuiManager::GuiManager() {

	interfacePrincipale = false;

//	initialisationInterface();
	Event* event = getEvent();
	processEvent(event);

	Engine::getInstance()->addListenner(this);
	Engine::getInstance()->getRoot()->addFrameListener(this);

}

GuiManager::~GuiManager() {
	// TODO Auto-generated destructor stub
}

void GuiManager::processEvent(Event* event)
{
	if(event->hasProperty("GuiTheme"))
	{
		initialisationInterface(event);
	}
}

void GuiManager::shutdown()
{

}

bool GuiManager::frameStarted(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
bool GuiManager::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
bool GuiManager::frameEnded(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}

void GuiManager::initialisationInterface(Event* event)
{
	CEGUI::OgreRenderer::bootstrapSystem();

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

	CEGUI::SchemeManager::getSingleton().createFromFile(event->getProperty("GuiTheme") + "Skin.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(event->getProperty("GuiTheme") + "Skin/MouseArrow");

	//inputInterface->initialisationMouse();

	interfacePrincipal();
}

void GuiManager::interfacePrincipal()
{
	if(!interfacePrincipale)
	{
		CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

		CEGUI::Window* parent = winMgr.createWindow("DefaultWindow", "InterfaceG");

		parent->activate();

		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(parent);

		interfacePrincipale = true;
	}

}

void GuiManager::deleteInterfacePrincipal()
{
	if(interfacePrincipale)
	{
		CEGUI::Window * parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
		CEGUI::WindowManager::getSingleton().destroyWindow(parent);
		parent->destroy();
		interfacePrincipale = false;
	}
}


} /* namespace Engine */
