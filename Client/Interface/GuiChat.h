#ifndef GUI_CHAT_UI_H_
#define GUI_CHAT_UI_H_

#include "Interface/Interface.h"

enum typeMessage
{
	ALL = 0
};


class Chat : public GuiInterface
{
public:
    Chat();
    ~Chat();

    void processMessage(Event * event);

    void activeSaisi();

    bool saisiActiver();

    void effaceSaisi();

    const char * getSaisi();

    void update();

    bool handleMouse(const CEGUI::EventArgs& args);

    void historiqueHaut();
    void historiqueBas();



private:
    int d_historyPos;
    std::vector<CEGUI::String> d_history;


};



#endif /* GUI_CHAT_UI_H_ */
