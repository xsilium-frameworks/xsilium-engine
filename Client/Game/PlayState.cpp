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

}

PlayState::~PlayState() {
	Engine::LogManager::DestroyInstance();
}

void PlayState::enter() {
	Engine::LogManager::getInstance()->setLogMessage("Entree dans PlayState", Engine::NORMAL);
	createScene();
}

void PlayState::createScene() {
	Event event;
	event.setProperty("LoadScene", "1");
	event.setProperty("NameScene", "Xsilium1.scene");
	event.setProperty("NameGroup", "General");

	Engine::Engine::getInstance()->addEvent(event);
}

void PlayState::exit() {
	Engine::LogManager::getInstance()->setLogMessage("Sortie du PlayState", Engine::NORMAL);
}

void PlayState::update(double timeSinceLastFrame) {

}

void PlayState::processEvent(Event* event) {

}
