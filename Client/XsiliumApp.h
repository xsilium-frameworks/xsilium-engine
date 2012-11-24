#ifndef OGRE_XSILIUM_H
#define OGRE_XSILIUM_H

#include "OgreFramework.h"
#include "AppStateManager.h"

class XsiliumApp
{
public:
	XsiliumApp();
	~XsiliumApp();

	void startXsilium();

private:
	AppStateManager*	m_pAppStateManager;
};

#endif