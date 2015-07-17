#include "LoginState.h"


using namespace Ogre;

LoginState::LoginState()
{
	Engine::NetworkManager::getInstance()->createConnexion();
	gestionnaireAuth = 0;
}

LoginState::~LoginState()
{
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
	gestionnaireAuth->processEvent(event);
}
