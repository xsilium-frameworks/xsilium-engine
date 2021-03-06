#include "InputManager.h"

namespace Engine {

InputManager::InputManager( void ) :mInputSystem( 0 ),mMouse( 0 ),mKeyboard( 0 ){
}

InputManager::~InputManager( void ) {
	if( mInputSystem ) {
		if( mMouse ) {
			mInputSystem->destroyInputObject( mMouse );
			mMouse = 0;
		}

		if( mKeyboard ) {
			mInputSystem->destroyInputObject( mKeyboard );
			mKeyboard = 0;
		}

		if( !mJoysticks.empty() ) {
			itJoystick    = mJoysticks.begin();
			itJoystickEnd = mJoysticks.end();
			for(; itJoystick != itJoystickEnd; ++itJoystick ) {
				mInputSystem->destroyInputObject( *itJoystick );
			}

			mJoysticks.clear();
		}

		OIS::InputManager::destroyInputSystem(mInputSystem);
		mInputSystem = 0;

		// Clear Listeners
		mKeyListeners.clear();
		mMouseListeners.clear();
		mJoystickListeners.clear();
	}
}

void InputManager::initialise( Ogre::RenderWindow *renderWindow ) {
	if( !mInputSystem ) {
		// Setup basic variables
		OIS::ParamList paramList;
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;

		// Get window handle
		if (renderWindow)
			renderWindow->getCustomAttribute( "WINDOW", &windowHnd );

		// Fill parameter list
		windowHndStr << windowHnd;
		paramList.insert( std::make_pair( std::string( "WINDOW" ), windowHndStr.str()));


		// insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
#if defined OIS_WIN32_PLATFORM
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#else
		paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		paramList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
		paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif


		// Create inputsystem
		mInputSystem = OIS::InputManager::createInputSystem( paramList );

		// If possible create a buffered keyboard
		if( mInputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0 ) {
			mKeyboard = static_cast<OIS::Keyboard*>( mInputSystem->createInputObject( OIS::OISKeyboard, true ) );
			mKeyboard->setEventCallback( this );
		}

		// If possible create a buffered mouse
		if( mInputSystem->getNumberOfDevices(OIS::OISMouse) > 0 ) {
			mMouse = static_cast<OIS::Mouse*>( mInputSystem->createInputObject( OIS::OISMouse, true ) );
			mMouse->setEventCallback( this );

			// Get window size
			setWindowExtents(renderWindow->getWidth(),renderWindow->getHeight());
		}

		// If possible create all joysticks in buffered mode
		if( mInputSystem->getNumberOfDevices(OIS::OISJoyStick) > 0 ) {
			mJoysticks.resize( mInputSystem->getNumberOfDevices(OIS::OISJoyStick) );

			itJoystick    = mJoysticks.begin();
			itJoystickEnd = mJoysticks.end();
			for(; itJoystick != itJoystickEnd; ++itJoystick ) {
				(*itJoystick) = static_cast<OIS::JoyStick*>( mInputSystem->createInputObject( OIS::OISJoyStick, true ) );
				(*itJoystick)->setEventCallback( this );
			}
		}
	}
}

void InputManager::capture( float timeSinceLastFrame ) {
	// Need to capture / update each device every frame
	if( mMouse ) {
		mMouse->capture();
	}

	if( mKeyboard ) {
		mKeyboard->capture();
	}

	if( !mJoysticks.empty() ) {
		itJoystick    = mJoysticks.begin();
		itJoystickEnd = mJoysticks.end();
		for(; itJoystick != itJoystickEnd; ++itJoystick ) {
			(*itJoystick)->capture();
		}
	}
}

void InputManager::addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName ) {
	if( mKeyboard ) {
		// Check for duplicate items
		itKeyListener = mKeyListeners.find( instanceName );
		if( itKeyListener == mKeyListeners.end() ) {
			mKeyListeners[ instanceName ] = keyListener;
		}
		else {
			// Duplicate Item
		}
	}
}

void InputManager::addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName ) {
	if( mMouse ) {
		// Check for duplicate items
		itMouseListener = mMouseListeners.find( instanceName );
		if( itMouseListener == mMouseListeners.end() ) {
			mMouseListeners[ instanceName ] = mouseListener;
		}
		else {
			// Duplicate Item
		}
	}
}

void InputManager::addJoystickListener( OIS::JoyStickListener *joystickListener, const std::string& instanceName ) {
	if( !mJoysticks.empty() ) {
		// Check for duplicate items
		itJoystickListener = mJoystickListeners.find( instanceName );
		if( itJoystickListener != mJoystickListeners.end() ) {
			mJoystickListeners[ instanceName ] = joystickListener;
		}
		else {
			// Duplicate Item
		}
	}
}

void InputManager::removeKeyListener( const std::string& instanceName ) {
	// Check if item exists
	itKeyListener = mKeyListeners.find( instanceName );
	if( itKeyListener != mKeyListeners.end() ) {
		mKeyListeners.erase( itKeyListener );
	}
	else {
		// Doesn't Exist
	}
}

void InputManager::removeMouseListener( const std::string& instanceName ) {
	// Check if item exists
	itMouseListener = mMouseListeners.find( instanceName );
	if( itMouseListener != mMouseListeners.end() ) {
		mMouseListeners.erase( itMouseListener );
	}
	else {
		// Doesn't Exist
	}
}

void InputManager::removeJoystickListener( const std::string& instanceName ) {
	// Check if item exists
	itJoystickListener = mJoystickListeners.find( instanceName );
	if( itJoystickListener != mJoystickListeners.end() ) {
		mJoystickListeners.erase( itJoystickListener );
	}
	else {
		// Doesn't Exist
	}
}

void InputManager::removeKeyListener( OIS::KeyListener *keyListener ) {
	itKeyListener    = mKeyListeners.begin();
	itKeyListenerEnd = mKeyListeners.end();
	for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
		if( itKeyListener->second == keyListener ) {
			mKeyListeners.erase( itKeyListener );
			break;
		}
	}
}

void InputManager::removeMouseListener( OIS::MouseListener *mouseListener ) {
	itMouseListener    = mMouseListeners.begin();
	itMouseListenerEnd = mMouseListeners.end();
	for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
		if( itMouseListener->second == mouseListener ) {
			mMouseListeners.erase( itMouseListener );
			break;
		}
	}
}

void InputManager::removeJoystickListener( OIS::JoyStickListener *joystickListener ) {
	itJoystickListener    = mJoystickListeners.begin();
	itJoystickListenerEnd = mJoystickListeners.end();
	for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
		if( itJoystickListener->second == joystickListener ) {
			mJoystickListeners.erase( itJoystickListener );
			break;
		}
	}
}

void InputManager::removeAllListeners( void ) {
	mKeyListeners.clear();
	mMouseListeners.clear();
	mJoystickListeners.clear();
}

void InputManager::removeAllKeyListeners( void ) {
	mKeyListeners.clear();
}

void InputManager::removeAllMouseListeners( void ) {
	mMouseListeners.clear();
}

void InputManager::removeAllJoystickListeners( void ) {
	mJoystickListeners.clear();
}

void InputManager::setWindowExtents( int width, int height ) {
	// Set mouse region (if window resizes, we should alter this to reflect as well)
	const OIS::MouseState &mouseState = mMouse->getMouseState();
	mouseState.width  = width;
	mouseState.height = height;
}

OIS::Mouse* InputManager::getMouse( void ) {
	return mMouse;
}

OIS::Keyboard* InputManager::getKeyboard( void ) {
	return mKeyboard;
}

OIS::JoyStick* InputManager::getJoystick( unsigned int index ) {
	// Make sure it's a valid index
	if( index < mJoysticks.size() ) {
		return mJoysticks[ index ];
	}

	return 0;
}

int InputManager::getNumOfJoysticks( void ) {
	// Cast to keep compiler happy ^^
	return (int) mJoysticks.size();
}

bool InputManager::keyPressed( const OIS::KeyEvent &e ) {

	itKeyListener    = mKeyListeners.begin();
	itKeyListenerEnd = mKeyListeners.end();

	for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
		itKeyListener->second->keyPressed( e );
	}

	return true;
}

bool InputManager::keyReleased( const OIS::KeyEvent &e ) {
	itKeyListener    = mKeyListeners.begin();
	itKeyListenerEnd = mKeyListeners.end();

	for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
		itKeyListener->second->keyReleased( e );
	}



	return true;
}

bool InputManager::mouseMoved( const OIS::MouseEvent &e ) {
	itMouseListener    = mMouseListeners.begin();
	itMouseListenerEnd = mMouseListeners.end();

	for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
		itMouseListener->second->mouseMoved( e );
	}

	return true;
}

bool InputManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
	itMouseListener    = mMouseListeners.begin();
	itMouseListenerEnd = mMouseListeners.end();

	for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
		itMouseListener->second->mousePressed( e, id );
	}

	return true;
}

bool InputManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
	itMouseListener    = mMouseListeners.begin();
	itMouseListenerEnd = mMouseListeners.end();

	for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
		itMouseListener->second->mouseReleased( e, id );
	}

	return true;
}

bool InputManager::povMoved( const OIS::JoyStickEvent &e, int pov ) {
	itJoystickListener    = mJoystickListeners.begin();
	itJoystickListenerEnd = mJoystickListeners.end();
	for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
		itJoystickListener->second->povMoved( e, pov );
	}

	return true;
}

bool InputManager::axisMoved( const OIS::JoyStickEvent &e, int axis ) {
	itJoystickListener    = mJoystickListeners.begin();
	itJoystickListenerEnd = mJoystickListeners.end();
	for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
		itJoystickListener->second->axisMoved( e, axis );
	}

	return true;
}

bool InputManager::sliderMoved( const OIS::JoyStickEvent &e, int sliderID ) {
	itJoystickListener    = mJoystickListeners.begin();
	itJoystickListenerEnd = mJoystickListeners.end();
	for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
		itJoystickListener->second->sliderMoved( e, sliderID );
	}

	return true;
}

bool InputManager::buttonPressed( const OIS::JoyStickEvent &e, int button ) {
	itJoystickListener    = mJoystickListeners.begin();
	itJoystickListenerEnd = mJoystickListeners.end();
	for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
		itJoystickListener->second->buttonPressed( e, button );
	}

	return true;
}

bool InputManager::buttonReleased( const OIS::JoyStickEvent &e, int button ) {
	itJoystickListener    = mJoystickListeners.begin();
	itJoystickListenerEnd = mJoystickListeners.end();
	for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
		itJoystickListener->second->buttonReleased( e, button );
	}

	return true;
}

}
