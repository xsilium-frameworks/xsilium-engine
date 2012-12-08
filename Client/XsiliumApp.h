#ifndef OGRE_XSILIUM_H
#define OGRE_XSILIUM_H

#include "XsiliumFramework.h"
#include "GameState/GameStateManager.h"

class XsiliumApp
{
public:
	XsiliumApp();
	~XsiliumApp();

	void startXsilium();

private:
	GameStateManager*	m_pGameStateManager;
};

#endif
