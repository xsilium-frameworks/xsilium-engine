#ifndef CHAT_UI_H_
#define CHAT_UI_H_

#include "CEGUI/CEGUI.h"
#include "Chat/GestionnaireChat/GestionnaireChat.h"

class GestionnaireChat;

class Chat
{
public:
    Chat();
    ~Chat();

    void toggleVisibility();
    bool isVisible() const;

    bool isActive();

    bool setMessage(CEGUI::String message);

    bool handleSubmit(const CEGUI::EventArgs& args);
    bool handleKeyDown(const CEGUI::EventArgs& args);

private:

    CEGUI::Window* d_root;
    CEGUI::Window* parent;
    int d_historyPos;
    std::vector<CEGUI::String> d_history;
    GestionnaireChat * gestionnaireChat ;


};



#endif /* CHAT_UI_H_ */
