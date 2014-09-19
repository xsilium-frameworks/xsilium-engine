#include "XsiliumApp.h"

XsiliumApp::XsiliumApp()
{
	graphicsManager = 0;
	gameStateManager = 0;
	guiManager = 0;
	logManager = NULL;
}

XsiliumApp::~XsiliumApp()
{
	Engine::KeyboardManager::DestroyInstance();
	Engine::GuiManager::DestroyInstance()  ;
	delete gameStateManager;
	Engine::GraphicsManager::DestroyInstance();
	Engine::Engine::DestroyInstance();
	Engine::LogManager::DestroyInstance();
}

void XsiliumApp::start()
{
	logManager = Engine::LogManager::getInstance();
	logManager->setFileLog("client");

	logManager->setLogMessage("Initialisation de l\'engine", "notification");
	Engine::Engine::getInstance()->initEngine("Xsilium",4);
	graphicsManager = Engine::GraphicsManager::getInstance();
	graphicsManager->initOgre();
	graphicsManager->createWindow();
	graphicsManager->loadRessource();

	gameStateManager = new Engine::GameStateManager();

	guiManager = Engine::GuiManager::getInstance();

	LoginState::create<LoginState>(gameStateManager, "LoginState");

	Engine::KeyboardManager::getInstance();

	gameStateManager->start(gameStateManager->findByName("LoginState"));

}


