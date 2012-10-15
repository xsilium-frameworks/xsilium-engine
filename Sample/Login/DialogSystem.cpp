/*
 * DialogSystem.cpp
 *
 *  Created on: 2012-10-15
 *      Author: xelfe
 */


#include "DialogSystem.h"
#include "assert.h"

DialogSystem::DialogSystem()
{
	m_modal  = false;
}

bool DialogSystem::isModified()
{
	// Return whether data within the window is modified
	assert(!m_apply.empty() && "The isModified() function requires that you specify an \"Apply\" button");
	return !CEGUI::WindowManager::getSingleton().getWindow(m_apply)->isDisabled();
}

bool DialogSystem::doOpen()
{
	// Open the window
	assert(!m_window.empty() && "You have forgotten to call initialise()");
	if(m_modal)
	{
		// Displaying a modal window disables its parent
		assert(!m_parent.empty() && "The value of m_modal or m_parent has become corrupted");
		CEGUI::WindowManager::getSingleton().getWindow(m_parent)->setEnabled(false);
	}

	// Display the window
	CEGUI::WindowManager::getSingleton().getWindow(m_window)->setVisible(true);

	// Load the data into the widgets
	return doLoad();
}

bool DialogSystem::doLoad()
{
	// Populate the window widgets with data
	// Note that this can also be used to simulate an undo for every widget
	// present in the window

	// Disable the apply button since there are no modifications
	if(!m_apply.empty())
		CEGUI::WindowManager::getSingleton().getWindow(m_apply)->setEnabled(false);
	return true;
}

bool DialogSystem::doSave()
{
	// Update the data with the inputs from the widgets

	// Disable the apply button since there are no modifications
	if(!m_apply.empty())
		CEGUI::WindowManager::getSingleton().getWindow(m_apply)->setEnabled(false);

	return true;
}

bool DialogSystem::doClose()
{
	// Close the window
	assert(!m_window.empty() && "You have forgotten to call initialise()");

	if(m_modal)
	{
		// Closing a modal window enables its parent
		assert(!m_parent.empty() && "The value of m_modal or m_parent has become corrupted");
		CEGUI::WindowManager::getSingleton().getWindow(m_parent)->setEnabled(true);
	}

	CEGUI::WindowManager::getSingleton().getWindow(m_window)->setVisible(false);
	return true;
}

void DialogSystem::initialise(const CEGUI::String& window, bool visible, const CEGUI::String& parent)
{
	// Initialise the window system
	// Specifying a parent makes this window modal
	m_window = window;
	CEGUI::WindowManager::getSingleton().getWindow(m_window)->setVisible(visible);
	m_parent = parent;
	m_modal  = !m_parent.empty();
}


void DialogSystem::bindEvent(const CEGUI::String& widget, const CEGUI::String& widgetEvent, DialogSystemEvents action)
{
	// Subscribe to events
	CEGUI::Window* widgetHandle = CEGUI::WindowManager::getSingleton().getWindow(widget);
	switch(action)
	{
	case open:
		widgetHandle->subscribeEvent(widgetEvent, CEGUI::Event::Subscriber(&DialogSystem::onOpen, this));
		break;
	case ok:
		widgetHandle->subscribeEvent(widgetEvent, CEGUI::Event::Subscriber(&DialogSystem::onOk, this));
		break;
	case cancel:
		widgetHandle->subscribeEvent(widgetEvent, CEGUI::Event::Subscriber(&DialogSystem::onCancel, this));
		break;
	case escape:
		widgetHandle->subscribeEvent(widgetEvent, CEGUI::Event::Subscriber(&DialogSystem::onEscape, this));
		break;
	case apply:
		widgetHandle->subscribeEvent(widgetEvent, CEGUI::Event::Subscriber(&DialogSystem::onApply, this));
		m_apply = widget;
		break;
	case modified:
		if(!m_apply.empty())
			widgetHandle->subscribeEvent(widgetEvent, CEGUI::Event::Subscriber(&DialogSystem::onModified, this));
		break;
	}
}

bool DialogSystem::onOpen(const CEGUI::EventArgs& e)
{
	// Open the window
	return doOpen();
}

bool DialogSystem::onOk(const CEGUI::EventArgs& e)
{
	// The 'ok' button was pressed
	// Respond by saving the data and closing the window
	return doSave() && doClose();
}

bool DialogSystem::onCancel(const CEGUI::EventArgs& e)
{
	// The 'cancel' button was pressed
	// Respond by closing the window without saving the data
	return doClose();
}

bool DialogSystem::onEscape(const CEGUI::EventArgs& e)
{
	// The 'escape' key was pressed
	// Respond by closing the dialog without saving the data
	// Note that Win32AppHelper::doDirectInputEvents() intercepts this key
	// This means that the escape key will NOT reach here
    const CEGUI::KeyEventArgs& keyArgs = static_cast<const CEGUI::KeyEventArgs&>(e);
	if(keyArgs.scancode == CEGUI::Key::Escape)
	{
		return doClose();
	}
	else
		return false;
}

bool DialogSystem::onApply(const CEGUI::EventArgs& e)
{
	// The 'apply' button was pressed
	// Respond by saving the data without closing the window
	return doSave();
}

bool DialogSystem::onModified(const CEGUI::EventArgs& e)
{
	// A widget within the window was modified
	// Respond by enabling the 'apply' button
	CEGUI::WindowManager::getSingleton().getWindow(m_apply)->setEnabled(true);
	return true;
}

