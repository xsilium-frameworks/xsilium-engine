#ifndef CHAT_UI_H_
#define CHAT_UI_H_

#include "Chat/GestionnaireChat/GestionnaireChat.h"

#include "EventManager/EventManager.h"
#include "Interface/Interface.h"

class GestionnaireChat;

enum messageType
{
	ALL = 0,
};


class Chat : public Interface
{
public:
    Chat();
    ~Chat();

    bool setMessage(const char * message);

    void processMessage(Event * event);


    bool handleSubmit(const CEGUI::EventArgs& args);
    bool handleKeyDown(const CEGUI::EventArgs& args);

    void update();



private:
    int d_historyPos;
    std::vector<CEGUI::String> d_history;
    GestionnaireChat * gestionnaireChat ;


};



#endif /* CHAT_UI_H_ */
