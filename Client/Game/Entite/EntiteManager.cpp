/*
 * EntiteManager.cpp
 *
 *  Created on: 11 avr. 2016
 *      Author: joda
 */

#include "EntiteManager.h"

EntiteManager::EntiteManager() {
    networkManager = Engine::NetworkManager::getInstance();

}

EntiteManager::~EntiteManager() {
    networkManager->removelistenneur(ID_WORLD);
}

void EntiteManager::run() {
    networkManager->addlistenneur(ID_WORLD, this);
    NetworkListener::run();

}

void EntiteManager::processPacket(Engine::MessagePacket * messagePacket) {
    Event event;
    event.setProperty("Entite", 1);
    event.setProperty("CharHeight", "5");
    event.setProperty("RunSpeed", "17");
    event.setProperty("TurnSpeed", "500.0");
    event.setProperty("NomEntite", "test");
    event.setProperty("fileMesh", "Sinbad.mesh");

    event.setProperty("PositionX", "-120");
    event.setProperty("PositionY", "500");
    event.setProperty("PositionZ", "-150");

    Engine::EventManager::getInstance()->addEvent(event);
}

void EntiteManager::processEvent(Event * event) {

}
