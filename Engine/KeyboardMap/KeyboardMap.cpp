/*
 * \file KeyboardMap.cpp
 *
 *  Created on: \date 16 févr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "KeyboardMap/KeyboardMap.h"

KeyboardMap::KeyboardMap() {

}

KeyboardMap::~KeyboardMap() {
	// TODO Auto-generated destructor stub
}

void KeyboardMap::load(const std::string& file)
{
	std::ifstream fichierConfKey(file.c_str());
	if (fichierConfKey.fail())
	{
		printf("erreur \n");
		return;
	}



	fichierConfKey.seekg(0, std::ios::end);
	size_t length = fichierConfKey.tellg();
	fichierConfKey.seekg(0, std::ios::beg);
	char* buffer = new char[length + 1];
	fichierConfKey.read(buffer, length);
	buffer[length] = '\0';

	fichierConfKey.close();

	rapidxml::xml_document<> doc;
	doc.parse<0>(buffer);

	delete [] buffer;

	for (rapidxml::xml_node<>* n = doc.first_node("KEYBOARD")->first_node(); n; n = n->next_sibling())
		{
	        KeyboardBinding[n->name()] = static_cast<OIS::KeyCode>(strtol(n->value(), NULL, 0));
	    }
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
