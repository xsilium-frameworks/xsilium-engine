/*
 * \file GestionnaireInterface.cpp
 *
 *  Created on: \date 8 sept. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "GestionnaireInterface.h"

GestionnaireInterface::GestionnaireInterface() {

	inputManager = InputManager::getInstance();
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
	CEGUI::OgreRenderer* renderer = &CEGUI::OgreRenderer::bootstrapSystem();

	const OIS::MouseState state = inputManager->getMouse()->getMouseState();
    CEGUI::Vector2f mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(state.X.abs-mousePos.d_x,state.Y.abs-mousePos.d_y);

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

		pWinHistory.push_back(parent);

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
		generateID += 1;
		interface->setIDInterface(generateID);
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
		delete interfaceIterator->second;
	}
	listOfInterface.clear();
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


bool GestionnaireInterface::onWindowActivated(const CEGUI::EventArgs &ea)
{
	try {
		const CEGUI::WindowEventArgs& we = static_cast<const CEGUI::WindowEventArgs&>(ea);
		CEGUI::Window *pLastWin = pWinHistory.back( );

        // We only work with FrameWindows.
		printf("test %s\n",we.window->getType().c_str());
        
        if(we.window->getType().compare("DragContainer"))
			return true;
        
		// If it is the same window as before, ignore it.
		if( pLastWin == we.window )
			return true;

		if( pLastWin != CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow() ) {
			// If every time a window gets activated we make the last active window become
			// transparent, this will result in all inactive windows being transparent.
			pLastWin->deactivate();

			// But we never make the root window transparent, as this would make all tooltips
			// become transparent, and we don't want this !
		}

		// We need the active window to not inherit the transparence of its parents.
		we.window->setProperty( "InheritsAlpha", "false" );

		// Finally, we add the new window to the stack.

		// One could also check if it's already present in the stack and if yes, just put it on the top.
		// You would have to do this if you want to set the transparency depending on the window's position
		// in the stack (see "Extending the effect").
		pWinHistory.push_back( we.window );
	} catch( CEGUI::Exception& e ) {
		fprintf( stderr, "CEGUI error: %s\n", e.getMessage( ).c_str( ) );
		return true;
	}

	return true;
}
bool GestionnaireInterface::onWindowDeactivated(const CEGUI::EventArgs &ea)
{
	try {
		const CEGUI::WindowEventArgs& we = static_cast<const CEGUI::WindowEventArgs&>(ea);
		CEGUI::Window *pLastWin = NULL;

        if(we.window->getType().compare("DragContainer"))
			return true;

		// Delete the current window from the stack.
		// CARE: std::list::remove removes ALL occurences of we.window from the stack !
		// This is VERY important to know, as if you activate window A, then window B and then A again,
		// the stack will contain A twice: {A,B,A}.
		pWinHistory.remove( we.window );

		// Now we get the window that was active before the current one:
		pLastWin = pWinHistory.back( );
		// re-activate it (like windos, linux, .. all do).
		pLastWin->activate();

	} catch( CEGUI::Exception& e ) {
		fprintf( stderr, "CEGUI error: %s\n", e.getMessage( ).c_str( ) );
		return true;
	}

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
