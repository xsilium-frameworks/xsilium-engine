#ifndef CONSOLE_H_
#define CONSOLE_H_

class Console
{
public:
    Console(CEGUI::Window* parent = 0);
    ~Console();

    void toggleVisibility();
    bool isVisible() const;

private:
    // these must match the IDs assigned in the layout
    static const unsigned int SubmitButtonID;
    static const unsigned int EntryBoxID;
    static const unsigned int HistoryID;

    bool handleSubmit(const CEGUI::EventArgs& args);
    bool handleKeyDown(const CEGUI::EventArgs& args);

    CEGUI::Window* d_root;
    int d_historyPos;
    std::vector<CEGUI::String> d_history;


};



#endif /* CONSOLE_H_ */
