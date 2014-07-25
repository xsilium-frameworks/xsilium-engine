/*
 * \file InputInterface.cpp
 *
 *  Created on: \date 18 juil. 2014
 *      Author: \author joda
 *  \brief :
 */
#include "InputInterface.h"

InputInterface::InputInterface() {
	m_fRepeatDelay = 0.035f;
	m_fInitialDelay = 0.300f;
	m_nKey = OIS::KC_UNASSIGNED ;
	m_nChar = 0;

	m_fElapsed = 0;
	m_fDelay = 0;

	InputManager::getInstance()->addKeyListener(this,"GestionnaireInterfaceKey");
	InputManager::getInstance()->addMouseListener(this,"GestionnaireInterfaceMouse");

}

InputInterface::~InputInterface() {
	InputManager::getInstance()->removeKeyListener(this);
	InputManager::getInstance()->removeMouseListener(this);
}

void InputInterface::initialisationMouse()
{
	const OIS::MouseState state = InputManager::getInstance()->getMouse()->getMouseState();
	CEGUI::Vector2f mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(state.X.abs-mousePos.d_x,state.Y.abs-mousePos.d_y);
}

bool InputInterface::keyPressed( const OIS::KeyEvent &e ) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(static_cast<CEGUI::Key::Scan>(e.key));
	CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(e.text);
	begin(e);
	return true;
}

bool InputInterface::keyReleased( const OIS::KeyEvent &e ) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(static_cast<CEGUI::Key::Scan>(e.key));
	end(e);
	return true;
}

bool InputInterface::mouseMoved( const OIS::MouseEvent &e ) {
	CEGUI::GUIContext& ctx = CEGUI::System::getSingleton().getDefaultGUIContext();
	ctx.injectMouseMove(e.state.X.rel, e.state.Y.rel);
	return true;
}

bool InputInterface::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertOISButtonToCegui(id));
	return true;
}

bool InputInterface::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertOISButtonToCegui(id));
	return true;
}

CEGUI::MouseButton InputInterface::convertOISButtonToCegui(int buttonID)
{
	using namespace OIS;

	switch (buttonID)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;
	case OIS::MB_Right:
		return CEGUI::RightButton;
	case OIS::MB_Middle:
		return CEGUI::MiddleButton;
	case OIS::MB_Button3:
		return CEGUI::X1Button;
		break;
	case OIS::MB_Button4:
		return CEGUI::X2Button ;
		break;
	case OIS::MB_Button5:
		return CEGUI::NoButton;
		break;
	case OIS::MB_Button6:
		return CEGUI::NoButton;
		break;
	case OIS::MB_Button7:
		return CEGUI::NoButton;
		break;
	default:
		return CEGUI::NoButton;
		break;
	}
	return CEGUI::NoButton;
}

void InputInterface::begin(const OIS::KeyEvent &evt) {
	m_nKey = evt.key;
	m_nChar = evt.text;

	m_fElapsed = 0;
	m_fDelay = m_fInitialDelay;
}

void InputInterface::end(const OIS::KeyEvent &evt) {
	if (m_nKey != evt.key) return;

	m_nKey = OIS::KC_UNASSIGNED;
}

void InputInterface::update(float a_fElapsed) {

	CEGUI::System::getSingleton().injectTimePulse(a_fElapsed);

	if (m_nKey == OIS::KC_UNASSIGNED) return;

	m_fElapsed += a_fElapsed;
	if (m_fElapsed < m_fDelay) return;

	m_fElapsed -= m_fDelay;
	m_fDelay = m_fRepeatDelay;

	do {
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(static_cast<CEGUI::Key::Scan>(m_nKey));   // Key UP
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(static_cast<CEGUI::Key::Scan>(m_nKey)); // Key Down
		CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(m_nChar);       // What that key means
		m_fElapsed -= m_fRepeatDelay;
	} while (m_fElapsed >= m_fRepeatDelay);

	m_fElapsed = 0;
}