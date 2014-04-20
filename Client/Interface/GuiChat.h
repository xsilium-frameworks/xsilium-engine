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

    void activeSaisi();

    bool saisiActiver();


    bool handleSubmit(const CEGUI::EventArgs& args);

    void update();

    bool handleMouse(const CEGUI::EventArgs& args);

    void historiqueHaut();
    void historiqueBas();



private:
    int d_historyPos;
    std::vector<CEGUI::String> d_history;
    ControleInterface * controleInterface ;


};



#endif /* GUI_CHAT_UI_H_ */
