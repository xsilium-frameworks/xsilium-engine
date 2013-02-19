#include "Chat.h"
//Chat class


Chat::Chat() :
    d_historyPos(0)
{
	CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

	parent = winMgr.createWindow("DefaultWindow", "CEGUIApp/Console");

	d_root = winMgr.loadLayoutFromFile("XsiliumConsole.layout");

	// we will destroy the console box windows ourselves
	d_root->setDestroyedByParent(false);

	gestionnaireChat = new GestionnaireChat(this);





	// Do events wire-up
	d_root->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&Chat::handleKeyDown, this));

	d_root->getChild("Console/Button")->
	            subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Chat::handleSubmit, this));

	d_root->getChild("Console/Editbox")->
	            subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&Chat::handleSubmit, this));

	        // attach this window if parent is valid
	parent->addChild(d_root);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(d_root);





}

Chat::~Chat()
{
	delete gestionnaireChat;
    CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
    d_root->destroy();
    parent->destroy();
}

void Chat::toggleVisibility()
{
    d_root->isVisible() ? d_root->hide() : d_root->show();
}

bool Chat::isVisible() const
{
    return d_root->isEffectiveVisible();
}

bool Chat::setMessage(const char * message)
{
	using namespace CEGUI;

	String messageChat(message);

	 // add this entry to the command history buffer
	 d_history.push_back(messageChat);
     // reset history position
     d_historyPos = d_history.size();
     // append newline to this entry
     message += '\n';
     // get history window
     MultiLineEditbox* history = static_cast<MultiLineEditbox*>(d_root->getChild("Console/Buffer"));
     // append new text to history output
     history->setText(history->getText() + messageChat);
     // scroll to bottom of history output
     history->setCaretIndex(static_cast<size_t>(-1));

	return true;
}

bool Chat::handleSubmit(const CEGUI::EventArgs&)
{
    using namespace CEGUI;

    // get the text entry editbox
    Editbox* editbox = static_cast<Editbox*>(d_root->getChild("Console/Editbox"));
    // get text out of the editbox
    CEGUI::String edit_text(editbox->getText());

    // if the string is not empty
    if (!edit_text.empty())
    {
    	gestionnaireChat->sendMessageToChat(edit_text.c_str(),0);
        // erase text in text entry box.
        editbox->setText("");
    }

    // re-activate the text entry box
    editbox->activate();

    return true;
}

bool Chat::handleKeyDown(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // get the text entry editbox
    Editbox* editbox = static_cast<Editbox*>(d_root->getChild("Console/Editbox"));

    switch (static_cast<const KeyEventArgs&>(args).scancode)
    {
    case Key::ArrowUp:
        d_historyPos = ceguimax(d_historyPos - 1, -1);
        if (d_historyPos >= 0)
        {
            editbox->setText(d_history[d_historyPos]);
            editbox->setCaretIndex(static_cast<size_t>(-1));
        }
        else
        {
            editbox->setText("");
        }

        editbox->activate();
        break;

    case Key::ArrowDown:
        d_historyPos = ceguimin(d_historyPos + 1, static_cast<int>(d_history.size()));
        if (d_historyPos < static_cast<int>(d_history.size()))
        {
            editbox->setText(d_history[d_historyPos]);
            editbox->setCaretIndex(static_cast<size_t>(-1));
        }
        else
        {
            editbox->setText("");
        }

        editbox->activate();
        break;

    default:
        return false;
    }

    return true;
}

bool Chat::isActive()
{
	return d_root->getChild("Console/Editbox")->isActive();
}


