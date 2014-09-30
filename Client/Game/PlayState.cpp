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
	event2.setProperty("PositionY","5");
	event2.setProperty("PositionZ","5");


	Engine::Engine::getInstance()->addEvent(event2);

	Event event3;

	event3.setProperty("Water","1");
	event3.setProperty("InitWater","1");
	Engine::Engine::getInstance()->addEvent(event3);
    
  /*  Event event3 ;
    event3.setProperty("Entite","1");
    event3.setProperty("deplaceEntite","1");
    event3.setProperty("idEntite","1");
    event3.setProperty("NewPositionX","1");
    event3.setProperty("NewPositionY","0");
    event3.setProperty("NewPositionZ","0");
    Engine::Engine::getInstance()->addEvent(event3); */



}

void PlayState::exit() {
	Engine::LogManager::getInstance()->setLogMessage("Sortie du PlayState", Engine::NORMAL);
}

void PlayState::update(double timeSinceLastFrame) {

}

void PlayState::processEvent(Event* event) {

	if(event->hasProperty("Keyboard"))
	{
		if( (event->getProperty("Fonction").compare("AVANCER")) == 0 )
		{
			if( atoi(event->getProperty("Action").c_str()) == 1 )
			{
				Event event3 ;
					event3.setProperty("Entite","1");
					event3.setProperty("deplaceEntite","1");
					event3.setProperty("idEntite","1");
					event3.setProperty("NewPositionX","1");
					event3.setProperty("NewPositionY","0");
					event3.setProperty("NewPositionZ","0");
					Engine::Engine::getInstance()->addEvent(event3);
			}
			else
			{
				Event event3 ;
					event3.setProperty("Entite","1");
					event3.setProperty("deplaceEntite","1");
					event3.setProperty("idEntite","1");
					event3.setProperty("NewPositionX","0");
					event3.setProperty("NewPositionY","0");
					event3.setProperty("NewPositionZ","0");
					Engine::Engine::getInstance()->addEvent(event3);
			}
		}
	}

}
