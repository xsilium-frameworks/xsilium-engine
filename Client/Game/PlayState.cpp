/*
 * \file PlayState.cpp
 *
 *  Created on: \date 23 septembre 2014
 *      Author: \author xelfe
 *  \brief : Fichier source de la classe PlayState
 */
#include "PlayState.h"

using namespace Ogre;

PlayState::PlayState() {
	Engine::NetworkManager::getInstance()->createConnexion();
	gestionnaireChat = NULL;
}

PlayState::~PlayState() {
}

void PlayState::enter() {
	Engine::LogManager::getInstance()->setLogMessage("Entree dans PlayState", Engine::NORMAL);
	createScene();
	gestionnaireChat = new GestionnaireChat();
}

void PlayState::createScene() {
	Event event;
	event.setProperty("LoadScene", "1");
	event.setProperty("NameScene", "SampleXSILIUM.scene");
	event.setProperty("NameGroup", "General");

	Engine::Engine::getInstance()->addEvent(event);

	/*for(int i = 1;i <2; i++)
	{

		Event event2 ;
		event2.setProperty("Entite","1");
		event2.setProperty("CreateEntite",i);
		event2.setProperty("CharHeight","5");
		event2.setProperty("RunSpeed","17");
		event2.setProperty("TurnSpeed","500.0");
		event2.setProperty("NomEntite","Perso" + i );
		event2.setProperty("fileMesh","Sinbad.mesh");

		event2.setProperty("PositionX","5");
		event2.setProperty("PositionY","1000");
		event2.setProperty("PositionZ","5");

		Engine::Engine::getInstance()->addEvent(event2);

	}*/

	/*Event event3 ;
	event3.setProperty("Entite","1");
	event3.setProperty("IdEntite","1");
	event3.setProperty("Camera","1");
	Engine::Engine::getInstance()->addEvent(event3);*/



}

void PlayState::exit() {
	Engine::LogManager::getInstance()->setLogMessage("Sortie du PlayState", Engine::NORMAL);
	delete gestionnaireChat;
}

void PlayState::update(double timeSinceLastFrame) {
}

void PlayState::processEvent(Event* event) {


	gestionnaireChat->processEvent(event);

}
