#include "LoginState.h"


using namespace Ogre;

LoginState::LoginState()
{
	Engine::NetworkManager::getInstance()->createConnexion();
	gestionnaireAuth = NULL;
}

LoginState::~LoginState()
{
	Engine::LogManager::DestroyInstance();
}
void LoginState::enter()
{
	Engine::LogManager::getInstance()->setLogMessage("Entree dans LoginState", Engine::NORMAL);

	gestionnaireAuth = new GestionnaireAuth();
	createScene();


}

void LoginState::createScene()
{


}

void LoginState::exit()
{
	delete gestionnaireAuth;
}

void LoginState::update(double timeSinceLastFrame)
{
}

void LoginState::processEvent(Event * event)
{
	if(event->hasProperty("GUI"))
	{
		if( (event->getProperty("Fonction").compare("QUIT")) == 0 )
		{
			popGameState();
		}
	}
	gestionnaireAuth->processEvent(event);

}
