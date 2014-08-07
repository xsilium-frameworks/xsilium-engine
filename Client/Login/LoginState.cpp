#include "LoginState.h"


using namespace Ogre;

LoginState::LoginState()
{
	m_bQuit         = false;
	changeState 	= false;
//	NetworkManager::getInstance()->createConnexion();
//    gestionnaireAuth = NULL;
}

LoginState::~LoginState()
{
}
void LoginState::enter()
{
//	XsiliumFramework::getInstance()->getLog()->logMessage("Entering LoginState...");


//    gestionnaireAuth = new GestionnaireAuth(this);
	createScene();

}

void LoginState::createScene()
{
	Event event ;
	event.setProperty("LoadScene","1");
	event.setProperty("NameScene","Xsilium1.scene");
	event.setProperty("NameGroup","General");

	Engine::Engine::getInstance()->addEvent(event);
}

void LoginState::exit()
{
}

bool LoginState::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
	if(m_bQuit)
	{
		popGameState();
		return false;
	}
	if(changeState)
	{
		changeGameState(findByName("JeuxState"));
	}
	return true;
}


