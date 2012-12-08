#include "XsiliumApp.h"

#include "UI/LoginState.h"
#include "MenuState.h"
#include "GameState.h"

XsiliumApp::XsiliumApp()
{
	m_pGameStateManager = 0;
}

XsiliumApp::~XsiliumApp()
{
	delete m_pGameStateManager;
    XsiliumFramework::DestroyInstance();
}

void XsiliumApp::startXsilium()
{
	if(!XsiliumFramework::getInstance()->initOgre("Xsilium Client"))
		return;

	XsiliumFramework::getInstance()->m_pLog->logMessage("Xsilium initiliasee!");

	m_pGameStateManager = new GameStateManager();

	LoginState::create(m_pGameStateManager, "LoginState");
//	MenuState::create(m_pAppStateManager, "MenuState");
	GameState::create(m_pGameStateManager, "GameState");
//    PauseState::create(m_pAppStateManager, "PauseState");

	m_pGameStateManager->start(m_pGameStateManager->findByName("LoginState"));
}
