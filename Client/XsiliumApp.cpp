#include "XsiliumApp.h"

#include "UI/LoginState.h"
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
    XsiliumFramework::DestroyInstance();
}

void XsiliumApp::startXsilium()
{
	if(!XsiliumFramework::getInstance()->initOgre("Xsilium Client"))
		return;

	XsiliumFramework::getInstance()->m_pLog->logMessage("Xsilium initiliasee!");

	m_pAppStateManager = AppStateManager::getInstance();

	LoginState::create(m_pAppStateManager, "LoginState");
//	MenuState::create(m_pAppStateManager, "MenuState");
//	GameState::create(m_pAppStateManager, "GameState");
//    PauseState::create(m_pAppStateManager, "PauseState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("LoginState"));
}
