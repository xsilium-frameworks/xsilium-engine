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
    gestionnaireChat = 0;
    entiteManager = 0;
}

PlayState::~PlayState() {
    delete gestionnaireChat;
    delete entiteManager;
}

void PlayState::enter() {
    Engine::LogManager::getInstance()->setLogMessage("Entree dans PlayState", Engine::NORMAL);
    createScene();

    Engine::NetworkManager::getInstance()->connexionToHost("151.80.162.102", 60001);
    gestionnaireChat = new GestionnaireChat();
    gestionnaireChat->run();

    entiteManager = new EntiteManager();
    entiteManager->run();
}

void PlayState::createScene() {
    Event event;
    event.setProperty("LoadScene", "1");
    event.setProperty("NameScene", "SampleXSILIUM.scene");
    event.setProperty("NameGroup", "General");

    Engine::EventManager::getInstance()->addEvent(event);

    /*Event event3 ;
     event3.setProperty("Entite","1");
     event3.setProperty("IdEntite","1");
     event3.setProperty("Camera","1");
     Engine::Engine::getInstance()->addEvent(event3);*/

}

void PlayState::exit() {
    Engine::LogManager::getInstance()->setLogMessage("Sortie du PlayState", Engine::NORMAL);
    delete gestionnaireChat;
    Engine::NetworkManager::getInstance()->disconnexion();
}

void PlayState::update(double timeSinceLastFrame) {
}

void PlayState::processEvent(Event* event) {

    gestionnaireChat->processEvent(event);

}
