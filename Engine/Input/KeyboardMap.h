/*
 * \file KeyboardMap.h
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef KEYBOARDMAP_H_
#define KEYBOARDMAP_H_

#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

namespace Engine {

/*
 *
 */
class KeyboardMap{

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

} /* namespace Engine */

#endif /* KEYBOARDMAP_H_ */
