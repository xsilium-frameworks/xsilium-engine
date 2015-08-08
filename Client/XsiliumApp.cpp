#include "XsiliumApp.h"

XsiliumApp::XsiliumApp()
{
}

XsiliumApp::~XsiliumApp()
{
	Engine::Engine::DestroyInstance();
}

void XsiliumApp::start()
{
	Engine::Engine::getInstance()->initEngine("Xsilium");

	Engine::GameStateManager* gameStateManager = Engine::GameStateManager::getInstance();

	LoginState::create<LoginState>(gameStateManager, "LoginState");
	PlayState::create<PlayState>(gameStateManager, "PlayState");

	gameStateManager->start(gameStateManager->findByName("PlayState"));

}

Ogre::RenderWindow* XsiliumApp::getWindow()
{
	return Engine::Engine::getInstance()->getRenderWindow();
}



