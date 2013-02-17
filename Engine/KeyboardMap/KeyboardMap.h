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

#include "rapidxml/rapidxml.h"

/*
 *
 */
class KeyboardMap : public xsilium::Singleton<KeyboardMap>
{
	friend class xsilium::Singleton<KeyboardMap>;

public:
	KeyboardMap();
	virtual ~KeyboardMap();
	void load(const char * file);

	const char * checkKey(OIS::KeyCode key);
	const OIS::KeyCode checkKey(const char * touche);

protected:
	typedef std::map<std::string,int> KeyMap;
private:
	KeyMap KeyboardBinding;

};

#endif /* KEYBOARDMAP_H_ */
