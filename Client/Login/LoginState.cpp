#include "LoginState.h"


using namespace Ogre;

LoginState::LoginState()
{
	Engine::NetworkManager::getInstance()->createConnexion();
	gestionnaireAuth = NULL;
}

LoginState::~LoginState()
{
	delete gestionnaireAuth;
}
void LoginState::enter()
{
	//	XsiliumFramework::getInstance()->getLog()->logMessage("Entering LoginState...");


	gestionnaireAuth = new GestionnaireAuth();
	createScene();


}

void LoginState::createScene()
{


}

void LoginState::exit()
{
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
