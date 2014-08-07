#include "XsiliumApp.h"

XsiliumApp::XsiliumApp()
{
	graphicsManager = 0;
	gameStateManager = 0;
}

XsiliumApp::~XsiliumApp()
{
	delete gameStateManager;
	delete graphicsManager;
	Engine::Engine::DestroyInstance();
}

void XsiliumApp::start()
{
	Engine::Engine::getInstance()->initEngine("Xsilium",4);
	graphicsManager = new Engine::GraphicsManager();
	graphicsManager->initOgre();
	graphicsManager->createWindow();
	graphicsManager->loadRessource();

	gameStateManager = new Engine::GameStateManager();

    LoginState::create<LoginState>(gameStateManager, "LoginState");
    
	gameStateManager->start(gameStateManager->findByName("LoginState"));

}

