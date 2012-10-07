#include <Console.h>
//Console class


Console::Console(CEGUI::Window* parent) :
    d_historyPos(0)
{
    using namespace CEGUI;

    CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

    parent = winMgr.createWindow("DefaultWindow", "CEGUIApp/Console");

    d_root = winMgr.loadLayoutFromFile("XsiliumConsole.layout");

    // we will destroy the console box windows ourselves
    d_root->setDestroyedByParent(false);

    // Do events wire-up
    d_root->subscribeEvent(CEGUI::Window::EventKeyDown, Event::Subscriber(&Console::handleKeyDown, this));

    d_root->getChild("Console/Button")->
        subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Console::handleSubmit, this));

    d_root->getChild("Console/Editbox")->
        subscribeEvent(Editbox::EventTextAccepted, Event::Subscriber(&Console::handleSubmit, this));

    // attach this window if parent is valid
    parent->addChild(d_root);

    d_root->show();
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(d_root);
}

Console::~Console()
{
    // destroy the windows that we loaded earlier
    CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
}

void Console::toggleVisibility()
{
    d_root->isVisible() ? d_root->hide() : d_root->show();
}

bool Console::isVisible() const
{
    return d_root->isEffectiveVisible();
}

bool Console::handleSubmit(const CEGUI::EventArgs&)
{
    using namespace CEGUI;

    // get the text entry editbox
    Editbox* editbox = static_cast<Editbox*>(d_root->getChild("Console/Buffer"));
    // get text out of the editbox
    CEGUI::String edit_text(editbox->getText());

    // if the string is not empty
    if (!edit_text.empty())
    {
        // add this entry to the command history buffer
        d_history.push_back(edit_text);
        // reset history position
        d_historyPos = d_history.size();
        // append newline to this entry
        edit_text += '\n';
        // get history window
        MultiLineEditbox* history = static_cast<MultiLineEditbox*>(d_root->getChild(HistoryID));
        // append new text to history output
        history->setText(history->getText() + edit_text);
        // scroll to bottom of history output
        history->setCaretIndex(static_cast<size_t>(-1));
        // erase text in text entry box.
        editbox->setText("");
    }

    // re-activate the text entry box
    editbox->activate();

    return true;
}

bool Console::handleKeyDown(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // get the text entry editbox
    Editbox* editbox = static_cast<Editbox*>(d_root->getChild(EntryBoxID));

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




