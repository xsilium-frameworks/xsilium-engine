/*
 * \file KeyboardMap.cpp
 *
 *  Created on: \date 16 févr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "KeyboardMap/KeyboardMap.h"

KeyboardMap::KeyboardMap() {
	// TODO Auto-generated constructor stub

}

KeyboardMap::~KeyboardMap() {
	// TODO Auto-generated destructor stub
}

void KeyboardMap::load(const std::string& File)
{
	KeyboardBinding["avance"] = OIS::KC_W;
	KeyboardBinding["reculer"] = OIS::KC_S;
	KeyboardBinding["gauche"] = OIS::KC_A;
	KeyboardBinding["droite"] = OIS::KC_D;

}

const char * KeyboardMap::checkKey(OIS::KeyCode key)
{
	for ( KeyMap::iterator increment = KeyboardBinding.begin(); increment != KeyboardBinding.end(); ++increment  )
	{
		if ( (*increment).second == key)
		{
			return ((*increment).first).c_str();
		}
	}
	return "";

}
const OIS::KeyCode KeyboardMap::checkKey(const char * touche)
{

	KeyMap::iterator increment = KeyboardBinding.find(touche);
	if( increment != KeyboardBinding.end() )
	{
		return static_cast<OIS::KeyCode>((*increment).second) ;
	}
	else
		return OIS::KC_UNASSIGNED;
}
