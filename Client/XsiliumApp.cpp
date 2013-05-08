#include "XsiliumApp.h"

XsiliumApp::XsiliumApp()
{
	m_pGameStateManager = GameStateManager::getInstance();

	compte = Compte::getInstance();

}

XsiliumApp::~XsiliumApp()
{
	GameStateManager::DestroyInstance();
	Compte::DestroyInstance();
    XsiliumFramework::DestroyInstance();
}

void XsiliumApp::startXsilium()
{
	if(!XsiliumFramework::getInstance()->initOgre("Xsilium Client","Client"))
		return;
	XsiliumFramework::getInstance()->loadRessource();

	XsiliumFramework::getInstance()->m_pLog->logMessage("Xsilium initiliasee!");

	LoginState::create(m_pGameStateManager,"LoginState");

//	MenuState::Create(m_pAppStateManager, "MenuState");
	JeuxState::create(m_pGameStateManager, "JeuxState");
//    PauseState::create(m_pAppStateManager, "PauseState");

	m_pGameStateManager->start(m_pGameStateManager->findByName("LoginState"));
}
