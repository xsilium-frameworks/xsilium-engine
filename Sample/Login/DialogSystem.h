/*
 * DialogSystem.h
 *
 *  Created on: 2012-10-15
 *      Author: xelfe
 */

#ifndef DIALOGSYSTEM_H_
#define DIALOGSYSTEM_H_

#include "CEGUI/CEGUI.h"
#include "vector"

class DialogSystem
{
public:
	DialogSystem();
	enum DialogSystemEvents { open, ok, cancel, escape, apply, modified };
	bool isModified(); // Return whether data within the window is modified

	// Actions
	virtual bool doOpen(); // Open the window
	virtual bool doLoad(); // Assign the data into the widgets
	virtual bool doSave(); // Assign the widgets into the data
	virtual bool doClose(); // Close the window
	void initialise(const CEGUI::String& window, bool visible, const CEGUI::String& parent = ""); // Initialise the window system
	void bindEvent(const CEGUI::String& widget, const CEGUI::String& event, DialogSystem::DialogSystemEvents action); // Subscribe to window events
private:
	// Events
	bool onOpen(const CEGUI::EventArgs& e); // Open the window
	bool onOk(const CEGUI::EventArgs& e); // Save the data and close the window
	bool onCancel(const CEGUI::EventArgs& e); // Close the window
	bool onEscape(const CEGUI::EventArgs& e); // Close the window
	bool onApply(const CEGUI::EventArgs& e); // Save the data
	bool onModified(const CEGUI::EventArgs& e); // A widget in the window has been modified

	CEGUI::String m_parent; // Handle to the parent
	CEGUI::String m_window; // Handle to the window
	CEGUI::String m_apply;  // Handle of the apply button
	bool m_modal; // Whether the window is modal
};


#endif /* DIALOGSYSTEM_H_ */
