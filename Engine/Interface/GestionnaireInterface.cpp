/*
 * \file GestionnaireInterface.cpp
 *
 *  Created on: \date 8 sept. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireInterface.h"

GestionnaireInterface::GestionnaireInterface() {

	interfacePrincipale = false;
	generateID = 0;

	initialisationInterface();

	CEGUI::GlobalEventSet::getSingleton( ).subscribeEvent( CEGUI::Window::EventNamespace + "/" + CEGUI::Window::EventActivated,
			CEGUI::Event::Subscriber(&GestionnaireInterface::onWindowActivated, this) );
	CEGUI::GlobalEventSet::getSingleton( ).subscribeEvent( CEGUI::Window::EventNamespace + "/" + CEGUI::Window::EventDeactivated,
			CEGUI::Event::Subscriber(&GestionnaireInterface::onWindowDeactivated, this) );

	XsiliumFramework::getInstance()->getRoot()->addFrameListener(this);

}

GestionnaireInterface::~GestionnaireInterface() {
	XsiliumFramework::getInstance()->getRoot()->removeFrameListener(this);
	removeAllInterface();
}

void GestionnaireInterface::initialisationInterface()
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


void GestionnaireInterface::interfacePrincipal()
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

void GestionnaireInterface::deleteInterfacePrincipal()
{
	if(interfacePrincipale)
	{
		CEGUI::Window * parent = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
		CEGUI::WindowManager::getSingleton().destroyWindow(parent);
		parent->destroy();
		interfacePrincipale = false;
	}
}


void GestionnaireInterface::addInterface(GuiInterface * interface)
{
	if(!findInterface(interface))
	{
		interface->setIDInterface(generateID + 1);
		listOfInterface.push_back(interface);
	}

}
void GestionnaireInterface::removeInterface(GuiInterface * interface)
{
	if(findInterface(interface))
	{
		listOfInterface.erase(interfaceIterator);
	}
}
void GestionnaireInterface::removeAllInterface()
{
	for (interfaceIterator = listOfInterface.begin() ; interfaceIterator != listOfInterface.end(); ++interfaceIterator)
	{
		listOfInterface.erase(interfaceIterator);
	}
	generateID = 0;
}

bool GestionnaireInterface::findInterface(GuiInterface * interface)
{
	for (interfaceIterator = listOfInterface.begin() ; interfaceIterator != listOfInterface.end(); ++interfaceIterator)
	{
		if(interface == (*interfaceIterator) )
		{
			return true;
		}
	}
	return false;
}

bool GestionnaireInterface::findWindow(CEGUI::Window* window)
{
	for (interfaceIterator = listOfInterface.begin() ; interfaceIterator != listOfInterface.end(); ++interfaceIterator)
	{
		if(window == (*interfaceIterator)->getWindow() )
		{
			return true;
		}
	}
	return false;
}

GuiInterface * GestionnaireInterface::getByName(std::string nameInterface)
{
	return NULL ;
}


bool GestionnaireInterface::onWindowActivated(const CEGUI::EventArgs &ea)
{
	return true;
}
bool GestionnaireInterface::onWindowDeactivated(const CEGUI::EventArgs &ea)
{
	return true;
}

bool GestionnaireInterface::frameStarted(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
bool GestionnaireInterface::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
	for (interfaceIterator=listOfInterface.begin() ; interfaceIterator!=listOfInterface.end() ; ++interfaceIterator)
	{
		(*interfaceIterator)->update();
	}
	return true;
}
bool GestionnaireInterface::frameEnded(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
