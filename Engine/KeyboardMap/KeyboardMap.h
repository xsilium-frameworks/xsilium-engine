/*
 * \file KeyboardMap.h
 *
 *  Created on: \date 16 févr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef KEYBOARDMAP_H_
#define KEYBOARDMAP_H_

#include "Singleton/Singleton.h"

#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

/*
 *
 */
class KeyboardMap : public xsilium::Singleton<KeyboardMap>
{
	friend class xsilium::Singleton<KeyboardMap>;

public:
	KeyboardMap();
	virtual ~KeyboardMap();
	void load(const std::string& file);

	void loadDefault();

	const char * checkKey(OIS::KeyCode key);
	const OIS::KeyCode checkKey(const char * touche);

	void changeKey(const char * touche,OIS::KeyCode key);

	void saveKeyboardMap();

protected:
	typedef std::map<std::string,int> KeyMap;
private:
	KeyMap KeyboardBinding;
	std::string fileName ;

};

#endif /* KEYBOARDMAP_H_ */
