#include "XsiliumApp.h"

#include "LoginState.h"
#include "MenuState.h"
#include "GameState.h"
//#include "PauseState.h"

XsiliumApp::XsiliumApp()
{
	m_pAppStateManager = 0;
}

XsiliumApp::~XsiliumApp()
{
	delete m_pAppStateManager;
    delete OgreFramework::getSingletonPtr();
}

void XsiliumApp::startXsilium()
{
	new OgreFramework();
	if(!OgreFramework::getSingletonPtr()->initOgre("Xsilium Client", 0, 0))
		return;

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Xsilium initiliasee!");

	m_pAppStateManager = new AppStateManager();

	LoginState::create(m_pAppStateManager, "LoginState");
	MenuState::create(m_pAppStateManager, "MenuState");
	GameState::create(m_pAppStateManager, "GameState");
//    PauseState::create(m_pAppStateManager, "PauseState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("LoginState"));
}
