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
	event.setProperty("NameScene", "Xsilium1.scene");
	event.setProperty("NameGroup", "General");

	Engine::Engine::getInstance()->addEvent(event);

	Event event2 ;
	event2.setProperty("Entite","1");
	event2.setProperty("CreateEntite","1");
	event2.setProperty("idEntite","1");
	event2.setProperty("CharHeight","5");
	event2.setProperty("RunSpeed","17");
	event2.setProperty("TurnSpeed","500.0");
	event2.setProperty("NomEntite","Perso1");
	event2.setProperty("fileMesh","Sinbad.mesh");

	event2.setProperty("PositionX","5");
	event2.setProperty("PositionY","50");
	event2.setProperty("PositionZ","5");


	Engine::Engine::getInstance()->addEvent(event2);

	/*	Event event3;

	event3.setProperty("Water","1");
	event3.setProperty("InitWater","1");
	Engine::Engine::getInstance()->addEvent(event3);*/

	Event event4;

	event4.setProperty("Sky","1");
	event4.setProperty("InitSky","1");
	Engine::Engine::getInstance()->addEvent(event4);

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
