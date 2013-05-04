#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "GameState.h"
#include "Singleton/Singleton.h"

class GameStateManager : public GameStateListener, public xsilium::Singleton<GameStateManager> {

	friend class xsilium::Singleton<GameStateManager>;

public:
	typedef struct
	{
		Ogre::String name;
		GameState* state;
	} state_info;

	GameStateManager();
	~GameStateManager();

	void manageGameState(Ogre::String stateName, GameState* state);

	GameState* findByName(Ogre::String stateName);

	void start(GameState* state);
	void changeGameState(GameState* state);
	bool pushGameState(GameState* state);
	void popGameState();
	void pauseGameState();
	void shutdown();
    void popAllAndPushGameState(GameState* state);


protected:
	void init(GameState *state);

	std::vector<GameState*>		m_ActiveStateStack;
	std::vector<state_info>		m_States;
	bool						m_bShutdown;
	InputManager* 				inputManager;

};

#endif
