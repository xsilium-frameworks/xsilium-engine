#include <Console.h>
//Console class


Console::Console(CEGUI::Window* d_root) :
    d_historyPos(0)
{
	this->d_root = d_root ;
}

Console::~Console()
{

}

void Console::toggleVisibility()
{
    d_root->isVisible() ? d_root->hide() : d_root->show();
}

bool Console::isVisible() const
{
    return d_root->isEffectiveVisible();
}

bool Console::setMessage(CEGUI::String message)
{
	using namespace CEGUI;

	 // add this entry to the command history buffer
	 d_history.push_back(message);
     // reset history position
     d_historyPos = d_history.size();
     // append newline to this entry
     message += '\n';
     // get history window
     MultiLineEditbox* history = static_cast<MultiLineEditbox*>(d_root->getChild("Console/Buffer"));
     // append new text to history output
     history->setText(history->getText() + message);
     // scroll to bottom of history output
     history->setCaretIndex(static_cast<size_t>(-1));

	return true;
}

bool Console::handleSubmit(const CEGUI::EventArgs&)
{
    using namespace CEGUI;

    // get the text entry editbox
    Editbox* editbox = static_cast<Editbox*>(d_root->getChild("Console/Editbox"));
    // get text out of the editbox
    CEGUI::String edit_text(editbox->getText());

    // if the string is not empty
    if (!edit_text.empty())
    {
        setMessage(edit_text);
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




