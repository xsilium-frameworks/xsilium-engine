#ifndef GUI_CHAT_UI_H_
#define GUI_CHAT_UI_H_

#include "Interface/Interface.h"


enum messageType
{
	ALL = LASTIDEVENTTYPE,
};


class Chat : public GuiInterface
{
public:
    Chat(ControleInterface * controleInterface);
    ~Chat();

    void processMessage(Event * event);

    void valideText();


    bool handleSubmit(const CEGUI::EventArgs& args);
    bool handleKeyDown(const CEGUI::EventArgs& args);

    void update();

    bool handleMouse(const CEGUI::EventArgs& args);



private:
    int d_historyPos;
    std::vector<CEGUI::String> d_history;
    ControleInterface * controleInterface ;


};



#endif /* GUI_CHAT_UI_H_ */
