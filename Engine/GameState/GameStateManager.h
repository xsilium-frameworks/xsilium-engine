#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "GameState.h"
#include <Event/EventListener.h>
#include <Singleton/Singleton.h>
#include <Logging/LogManager.h>

namespace Engine {


class GameStateManager : public GameStateListener , public EventListener , public Singleton<GameStateManager> {

	friend class Singleton<GameStateManager> ;

public:
	typedef struct
	{
		Ogre::String name;
		GameState* state;
	} state_info;

	GameStateManager();
	~GameStateManager();

	void addGameState(Ogre::String stateName, GameState* state);

	GameState* findByName(Ogre::String stateName);

	void start(GameState* state);
	void changeGameState(GameState* state);
	bool pushGameState(GameState* state);
	void popGameState();
	void shutdown();
    void popAllAndPushGameState(GameState* state);

    void processEvent(Event * event);

    bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);


    void setRoot(Ogre::Root* m_pRoot);
    void setRenderWindow(Ogre::RenderWindow* m_pRenderWnd);


protected:
	void init(GameState *state);

	std::vector<GameState*>		m_ActiveStateStack;
	std::vector<state_info>		m_States;
	InputManager* 				inputManager;

private:
	Ogre::Root* m_pRoot;
	Ogre::RenderWindow*			m_pRenderWnd;


};

}

#endif
