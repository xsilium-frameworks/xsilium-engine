/*
 * \file KeyboardManager.h
 *
 *  Created on: \date 14 sept. 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef KEYBOARDMANAGER_H_
#define KEYBOARDMANAGER_H_

#include "InputManager.h"
#include "KeyboardMap.h"
#include <Event/EventManager.h>

namespace Engine {

/*
 *
 */
class KeyboardManager : public Singleton<KeyboardManager>, public OIS::KeyListener {

	friend class Singleton<KeyboardManager>;

public:
	KeyboardManager();
	virtual ~KeyboardManager();

	bool keyPressed( const OIS::KeyEvent &e );
	bool keyReleased( const OIS::KeyEvent &e );

	void load(std::string mResourcePath,std::string configFile);

private:
	KeyboardMap * keyboardMap;
};

} /* namespace Engine */

#endif /* KEYBOARDMANAGER_H_ */
