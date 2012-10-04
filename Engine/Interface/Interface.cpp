#ifndef INTERFACE_CPP_
#define INTERFACE_CPP_
#include "Interface.h"

Interface::Interface()
: mRenderer(0)
{
}

Interface::~Interface()
{
}

void Interface::initialiseDefaultResourceGroups()

{

	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();


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

void Interface::setupCEGUI()
{
    CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("AlfiskoSkin/MouseArrow");

}



#endif /* INTERFACE_CPP_ */
