#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "CEGUI/CEGUI.h"

class Console
{
public:
    Console(CEGUI::Window* parent = 0);
    ~Console();

    void toggleVisibility();
    bool isVisible() const;

    bool setMessage(CEGUI::String message);

    bool handleSubmit(const CEGUI::EventArgs& args);
    bool handleKeyDown(const CEGUI::EventArgs& args);

private:

    CEGUI::Window* d_root;
    int d_historyPos;
    std::vector<CEGUI::String> d_history;


};



#endif /* CONSOLE_H_ */
