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

	XsiliumFramework::getInstance()->getLog()->logMessage("Xsilium initiliasee!");

	LoginState::create<LoginState>(m_pGameStateManager,"LoginState");

//	JeuxState::create(m_pGameStateManager, "JeuxState");

	m_pGameStateManager->start(m_pGameStateManager->findByName("LoginState"));
}

