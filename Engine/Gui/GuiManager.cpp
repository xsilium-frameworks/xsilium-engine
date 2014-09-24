/*
 * \file GuiManager.cpp
 *
 *  Created on: \date 7 aožt 2014
 *      Author: \author joda xelfe
 *  \brief :
 */
#include "GuiManager.h"

namespace Engine {

GuiManager::GuiManager() {
	interfacePrincipale = false;

	Engine::getInstance()->addListenner(this);
	Engine::getInstance()->getRoot()->addFrameListener(this);

	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

	guiInput = new GuiInput();
	loadRessource();
}

GuiManager::~GuiManager() {
	Engine::getInstance()->getRoot()->removeFrameListener(this);
	std::vector<GuiListenner*>::iterator guiIterator;

	for (guiIterator = listOfInterface.begin() ; guiIterator != listOfInterface.end(); ++guiIterator)
	{
		delete *guiIterator;
	}
	listOfInterface.clear();

	delete guiInput;
	deleteInterfacePrincipal();
}

void GuiManager::processEvent(Event* event)
{
	if(event->hasProperty("GuiTheme"))
	{
		setTheme(event);
	}

	std::vector<GuiListenner*>::iterator guiIterator;

	for (guiIterator = listOfInterface.begin() ; guiIterator != listOfInterface.end(); ++guiIterator)
	{
		(*guiIterator)->processEvent(event);
	}
}

bool GuiManager::frameStarted(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
bool GuiManager::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
	if(!isEmpty())
	{
		Event* event = getEvent();
		processEvent(event);
		deleteEvent();
	}
	return true;
}
bool GuiManager::frameEnded(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}

void GuiManager::setTheme(Event* event)
{
	theme = event->getProperty("GuiTheme");

	CEGUI::SchemeManager::getSingleton().createFromFile(getTheme() + "Skin.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(getTheme() + "Skin/MouseArrow");
}

void GuiManager::setTheme(Ogre::String theme)
{
	this->theme = theme;

	CEGUI::SchemeManager::getSingleton().createFromFile(getTheme() + "Skin.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(getTheme() + "Skin/MouseArrow");
}

std::string GuiManager::getTheme()
{
	return theme;
}

void GuiManager::interfacePrincipal()
{
	if(!interfacePrincipale)
	{
		setTheme("Alfisko");

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

void GuiManager::loadRessource()
{
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
}

void GuiManager::addGuiListenner(GuiListenner* guiListenner)
{
	interfacePrincipal();
	guiListenner->initGui();
	listOfInterface.push_back(guiListenner);
}

void GuiManager::removeGuiListenner(GuiListenner* guiListenner)
{
	std::vector<GuiListenner*>::iterator guiIterator;

		for (guiIterator = listOfInterface.begin() ; guiIterator != listOfInterface.end(); )
		{
			if( (*guiIterator) == guiListenner)
				guiIterator = listOfInterface.erase(guiIterator);
			else
				++guiIterator;
		}
}


} /* namespace Engine */
