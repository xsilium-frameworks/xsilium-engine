#ifndef CHAT_UI_H_
#define CHAT_UI_H_

#include "CEGUI/CEGUI.h"
#include "Chat/GestionnaireChat/GestionnaireChat.h"

#include "EventManager/EventManager.h"

class GestionnaireChat;

enum messageType
{
	ALL = 0,
};


class Chat
{
public:
    Chat();
    ~Chat();

    void toggleVisibility();
    bool isVisible() const;

    bool isActive();

    bool setMessage(const char * message);

    void processMessage(Event * event);

    bool handleSubmit(const CEGUI::EventArgs& args);
    bool handleKeyDown(const CEGUI::EventArgs& args);

    void update();

private:

    CEGUI::Window* d_root;
    CEGUI::Window* parent;
    int d_historyPos;
    std::vector<CEGUI::String> d_history;
    GestionnaireChat * gestionnaireChat ;
    EventManager * eventManager ;


};



#endif /* CHAT_UI_H_ */
