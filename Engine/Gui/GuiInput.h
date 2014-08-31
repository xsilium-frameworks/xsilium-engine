/*
 * \file GuiInput.h
 *
 *  Created on: \date 31 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GUIINPUT_H_
#define GUIINPUT_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "Input/InputManager.h"

namespace Engine {

/*
 *
 */
class GuiInput : public OIS::KeyListener, public OIS::MouseListener {
public:
	GuiInput();
	virtual ~GuiInput();

	void update(float a_fElapsed); // Elapsed time in seconds

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved( const OIS::MouseEvent &e );
	bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

	void initialisationMouse();

private:

	void begin(const OIS::KeyEvent &evt);
	void end(const OIS::KeyEvent &evt);

	// convert an OIS mouse button into a CEGUI mouse button
	CEGUI::MouseButton convertOISButtonToCegui(int buttonID);


	OIS::KeyCode m_nKey;
	unsigned int m_nChar;

	float m_fElapsed;
	float m_fDelay;

	float m_fRepeatDelay;
	float m_fInitialDelay;

};

} /* namespace Engine */

#endif /* GUIINPUT_H_ */
