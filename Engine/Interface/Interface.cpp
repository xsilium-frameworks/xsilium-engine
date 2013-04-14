#ifndef INTERFACE_CPP_
#define INTERFACE_CPP_
#include "Interface.h"

Interface::Interface()
{
	isActived = false;
}

Interface::~Interface()
{
	delete eventManager ;
	CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
	d_root->destroy();
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


#endif /* INTERFACE_CPP_ */
