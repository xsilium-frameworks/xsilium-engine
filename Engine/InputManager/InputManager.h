#ifndef InputManager_H
#define InputManager_H

#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>
#include <OISInputManager.h>

#include "CEGUI/CEGUI.h"
#include "Singleton/Singleton.h"

#include <OgreRenderWindow.h>
#include <OgrePrerequisites.h>


class InputManager : public OIS::KeyListener, OIS::MouseListener, OIS::JoyStickListener
{

public:
	virtual ~InputManager( void );

	void initialise( Ogre::RenderWindow *renderWindow );
	void capture( float timeSinceLastFrame );

	void addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName );
	void addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName );
	void addJoystickListener( OIS::JoyStickListener *joystickListener, const std::string& instanceName );

	void removeKeyListener( const std::string& instanceName );
	void removeMouseListener( const std::string& instanceName );
	void removeJoystickListener( const std::string& instanceName );

	void removeKeyListener( OIS::KeyListener *keyListener );
	void removeMouseListener( OIS::MouseListener *mouseListener );
	void removeJoystickListener( OIS::JoyStickListener *joystickListener );

	void removeAllListeners( void );
	void removeAllKeyListeners( void );
	void removeAllMouseListeners( void );
	void removeAllJoystickListeners( void );

	void setWindowExtents( int width, int height );

	OIS::Mouse*    getMouse( void );
	OIS::Keyboard* getKeyboard( void );
	OIS::JoyStick* getJoystick( unsigned int index );

	int getNumOfJoysticks( void );

	static InputManager* getSingletonPtr( void );

protected:
	// convert an OIS mouse button into a CEGUI mouse button
	CEGUI::MouseButton convertOISButtonToCegui(int buttonID);

private:
	InputManager( void );
	InputManager( const InputManager& ) { };
	InputManager & operator = ( const InputManager& );

	bool keyPressed( const OIS::KeyEvent &e );
	bool keyReleased( const OIS::KeyEvent &e );

	bool mouseMoved( const OIS::MouseEvent &e );
	bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

	bool povMoved( const OIS::JoyStickEvent &e, int pov );
	bool axisMoved( const OIS::JoyStickEvent &e, int axis );
	bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
	bool buttonPressed( const OIS::JoyStickEvent &e, int button );
	bool buttonReleased( const OIS::JoyStickEvent &e, int button );

	void begin(const OIS::KeyEvent &evt);

	void end(const OIS::KeyEvent &evt);

	void update(float a_fElapsed); // Elapsed time in seconds

	OIS::InputManager *mInputSystem;
	OIS::Mouse        *mMouse;
	OIS::Keyboard     *mKeyboard;

	std::vector<OIS::JoyStick*> mJoysticks;
	std::vector<OIS::JoyStick*>::iterator itJoystick;
	std::vector<OIS::JoyStick*>::iterator itJoystickEnd;

	std::map<std::string, OIS::KeyListener*> mKeyListeners;
	std::map<std::string, OIS::MouseListener*> mMouseListeners;
	std::map<std::string, OIS::JoyStickListener*> mJoystickListeners;

	std::map<std::string, OIS::KeyListener*>::iterator itKeyListener;
	std::map<std::string, OIS::MouseListener*>::iterator itMouseListener;
	std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener;

	std::map<std::string, OIS::KeyListener*>::iterator itKeyListenerEnd;
	std::map<std::string, OIS::MouseListener*>::iterator itMouseListenerEnd;
	std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListenerEnd;

	static InputManager *mInputManager;

	OIS::KeyCode m_nKey;
	unsigned int m_nChar;

	float m_fElapsed;
	float m_fDelay;

	float m_fRepeatDelay;
	float m_fInitialDelay;
};
#endif
