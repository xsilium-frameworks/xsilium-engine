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

    bool handleSubmit(const CEGUI::EventArgs& args);
    bool handleKeyDown(const CEGUI::EventArgs& args);

private:
    // these must match the IDs assigned in the layout
    static const unsigned int SubmitButtonID = 1;
    static const unsigned int EntryBoxID = 2;
    static const unsigned int HistoryID = 3;



    CEGUI::Window* d_root;
    int d_historyPos;
    std::vector<CEGUI::String> d_history;


};



#endif /* CONSOLE_H_ */
