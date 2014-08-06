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


	Event event ;
	event.setProperty("LoadScene","1");
	event.setProperty("NameScene","Xsilium1.scene");
	event.setProperty("NameGroup","General");

	Engine::Engine::getInstance()->addEvent(event);

}

