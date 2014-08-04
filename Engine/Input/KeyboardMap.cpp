/*
 * \file KeyboardMap.cpp
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "KeyboardMap.h"

namespace Engine {

KeyboardMap::KeyboardMap() {
	// TODO Auto-generated constructor stub

}

KeyboardMap::~KeyboardMap() {
	// TODO Auto-generated destructor stub
}

void KeyboardMap::load(const std::string& file)
{
	fileName = file ;
	std::ifstream fichierConfKey(file.c_str());
	if (fichierConfKey.fail())
	{
		printf("Fichier %s non trouve chargement de la configuration par defaut  \n",fileName.c_str());
		loadDefault();
		saveKeyboardMap();
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

void KeyboardMap::changeKey(const char * touche,OIS::KeyCode key)
{
	KeyboardBinding[touche] = static_cast<int>(key);
}

void KeyboardMap::saveKeyboardMap()
{

	rapidxml::xml_document<> doc;

	rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "ISO-8859-1"));
	doc.append_node(decl);

	rapidxml::xml_node<> *Keyboard = doc.allocate_node(rapidxml::node_element, "KEYBOARD");
	doc.append_node(Keyboard);


	for ( KeyMap::iterator increment = KeyboardBinding.begin(); increment != KeyboardBinding.end(); ++increment  )
	{
		rapidxml::xml_node<> *Key = doc.allocate_node(rapidxml::node_element, ((*increment).first).c_str());
		std::stringstream ss;
		ss << "0x" << std::hex << (*increment).second  ;

		char* numBuff =  doc.allocate_string(ss.str().c_str());

		Key->value(numBuff);

		Keyboard->append_node(Key);
	}
	std::string data;
	rapidxml::print(std::back_inserter(data), doc);

	std::ofstream myfile(fileName.c_str()) ;
	myfile << data;
	myfile.close();


}

void KeyboardMap::loadDefault()
{
	KeyboardBinding["AVANCER"] = static_cast<int>(0x11);
	KeyboardBinding["DROITE"] = static_cast<int>(0x20);
	KeyboardBinding["GAUCHE"] = static_cast<int>(0x1e);
	KeyboardBinding["RECULER"] = static_cast<int>(0x1f);
	KeyboardBinding["DEGAINER"] = static_cast<int>(0x2c);
}

} /* namespace Engine */
