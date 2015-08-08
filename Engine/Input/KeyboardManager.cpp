/*
 * \file KeyboardManager.cpp
 *
 *  Created on: \date 14 sept. 2014
 *      Author: \author joda
 *  \brief :
 */
#include "KeyboardManager.h"

namespace Engine {

KeyboardManager::KeyboardManager() {
	keyboardMap = new KeyboardMap();
	InputManager::getInstance()->addKeyListener(this,"KeyboardManager");

}

KeyboardManager::~KeyboardManager() {
	InputManager::getInstance()->removeKeyListener(this);
	keyboardMap->saveKeyboardMap();
	delete keyboardMap;
}

void KeyboardManager::load(std::string mResourcePath,std::string configFile)
{
	keyboardMap->load(mResourcePath + configFile);
}

bool KeyboardManager::keyPressed( const OIS::KeyEvent &e )
{
	Event event ;
	event.setProperty("Keyboard","1");
	event.setProperty("Fonction",keyboardMap->checkKey(e.key));
	event.setProperty("Action","1");

	EventManager::getInstance()->addEvent(event);
	return true;
}
bool KeyboardManager::keyReleased( const OIS::KeyEvent &e )
{
	Event event ;
	event.setProperty("Keyboard","1");
	event.setProperty("Fonction",keyboardMap->checkKey(e.key));
	event.setProperty("Action","0");

	EventManager::getInstance()->addEvent(event);
	return true;
}

} /* namespace Engine */
