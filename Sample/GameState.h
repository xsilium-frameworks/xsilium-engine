#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "AppState.h"

#include "DotSceneLoader.h"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>

/*
enum QueryFlags
{
	OGRE_HEAD_MASK	= 1<<0,
    CUBE_MASK		= 1<<1
};
*/

class GameState : public AppState
{
public:
	GameState();

	DECLARE_APPSTATE_CLASS(GameState)

	void enter();
	void createScene();
	void exit();
//	bool pause();
	void resume();

	void moveCamera();
	void getInput();
//    void buildGUI();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void onLeftPressed(const OIS::MouseEvent &evt);
//    void itemSelected(OgreBites::SelectMenu* menu);

	void update(double timeSinceLastFrame);

private:

/*
	Ogre::SceneNode*			m_pOgreHeadNode;
	Ogre::Entity*				m_pOgreHeadEntity;
	Ogre::MaterialPtr			m_pOgreHeadMat;
	Ogre::MaterialPtr			m_pOgreHeadMatHigh;

    OgreBites::ParamsPanel*		m_pDetailsPanel;
*/

	bool						m_bQuit;

	Ogre::Vector3				m_TranslateVector;
	Ogre::Real					m_MoveSpeed;
	Ogre::Degree				m_RotateSpeed;
	float						m_MoveScale;
	Ogre::Degree				m_RotScale;

	Ogre::RaySceneQuery*		m_pRSQ;
	Ogre::SceneNode*			m_pCurrentObject;
	Ogre::Entity*				m_pCurrentEntity;
	bool						m_bLMouseDown, m_bRMouseDown;
	bool						m_bSettingsMode;

protected:

    // convert an OIS mouse button into a CEGUI mouse button
    CEGUI::MouseButton convertOISButtonToCegui(int buttonID);
//    Console* d_console;
};

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


#endif
