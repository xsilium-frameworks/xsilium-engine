#include "LoginState.h"


using namespace Ogre;

LoginState::LoginState()
{
	m_bQuit         = false;
	changeState 	= false;
	guiAuth = 0;
	//	NetworkManager::getInstance()->createConnexion();
	//    gestionnaireAuth = NULL;
}

LoginState::~LoginState()
{
	delete guiAuth;
}
void LoginState::enter()
{
	//	XsiliumFramework::getInstance()->getLog()->logMessage("Entering LoginState...");


	//    gestionnaireAuth = new GestionnaireAuth(this);
	createScene();

	Engine::GuiManager::getInstance()->addGuiListenner(new GuiAuth());

}

void LoginState::createScene()
{
/*	Event event ;
	event.setProperty("LoadScene","1");
	event.setProperty("NameScene","Xsilium1.scene");
	event.setProperty("NameGroup","General");

	Engine::Engine::getInstance()->addEvent(event);

	Event event2 ;
	event2.setProperty("Entite","1");
	event2.setProperty("CreateEntite","1");
	event2.setProperty("CharHeight","1");
	event2.setProperty("RunSpeed","3");
	event2.setProperty("TurnSpeed","500.0");
	event2.setProperty("NomEntite","Perso1");
	event2.setProperty("fileMesh","Sinbad.mesh");

	event2.setProperty("PositionX","5");
	event2.setProperty("PositionY","5");
	event2.setProperty("Position2","5");


	Engine::Engine::getInstance()->addEvent(event2);

	Event event3 ;
	event3.setProperty("Objet","1");
	event3.setProperty("CreateObjet","1");
	event3.setProperty("NomObjet","SinbadSword1");
	event3.setProperty("fileMesh","Sword.mesh");


	Engine::Engine::getInstance()->addEvent(event3);

	Event event4 ;
	event4.setProperty("Entite","1");
	event4.setProperty("AssigneObjet","1");
	event4.setProperty("NomEntite","Perso1");
	event4.setProperty("NomObjet","SinbadSword1");
	event4.setProperty("Emplacement","Sheath.L");


	Engine::Engine::getInstance()->addEvent(event4);


	Event event5 ;
	event5.setProperty("Objet","1");
	event5.setProperty("CreateObjet","1");
	event5.setProperty("NomObjet","SinbadSword2");
	event5.setProperty("fileMesh","Sword.mesh");


	Engine::Engine::getInstance()->addEvent(event5);

	Event event6 ;
	event6.setProperty("Entite","1");
	event6.setProperty("AssigneObjet","1");
	event6.setProperty("NomEntite","Perso1");
	event6.setProperty("NomObjet","SinbadSword2");
	event6.setProperty("Emplacement","Sheath.R");


	Engine::Engine::getInstance()->addEvent(event6);
*/

}

void LoginState::exit()
{
}

void LoginState::update(double timeSinceLastFrame)
{
	if(m_bQuit)
	{
		popGameState();
	}
	if(changeState)
	{
		changeGameState(findByName("JeuxState"));
	}
}

void LoginState::processEvent(Event * event)
{
	if(event->hasProperty("GUI"))
	{
		if( (event->getProperty("Fonction").compare("QUIT")) == 0 )
		{
			m_bQuit = true;
		}
	}

}
