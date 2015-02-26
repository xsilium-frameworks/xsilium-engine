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
	Engine::Engine::getInstance()->initEngine("Xsilium",4);
	logManager = Engine::LogManager::getInstance();
	logManager->initLog("client");

    logManager->setLogMessage("Initialisation de l\'engine", Engine::NOTIFICATION);
    Engine::Engine::getInstance()->initOgre("Xsilium");

	graphicsManager = Engine::GraphicsManager::getInstance();
	graphicsManager->initOgre();
	graphicsManager->createWindow();
	graphicsManager->loadRessource();

	gameStateManager = new Engine::GameStateManager();

	guiManager = Engine::GuiManager::getInstance();

	LoginState::create<LoginState>(gameStateManager, "LoginState");
	PlayState::create<PlayState>(gameStateManager, "PlayState");

	Engine::KeyboardManager::getInstance();

	gameStateManager->start(gameStateManager->findByName("PlayState"));

}

Ogre::RenderWindow* XsiliumApp::getWindow()
{
    return graphicsManager->getRenderWindow();
}



