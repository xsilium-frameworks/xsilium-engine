#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "GameState.h"
#include "Singleton/Singleton.h"



class GameStateManager : public GameStateListener, public Ogre::FrameListener , public xsilium::Singleton<GameStateManager> {

	friend class xsilium::Singleton<GameStateManager>;

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


protected:
	void init(GameState *state);

    bool frameStarted (const Ogre::FrameEvent &evt);
     	//Called when a frame is about to begin rendering.
    bool frameRenderingQueued (const Ogre::FrameEvent &evt);
     	//Called after all render targets have had their rendering commands issued, but before render windows have been asked to flip their buffers over.
    bool frameEnded (const Ogre::FrameEvent &evt);
     	//Called just after a frame has been rendered.

	std::vector<GameState*>		m_ActiveStateStack;
	std::vector<state_info>		m_States;
	bool						m_bShutdown;
	InputManager* 				inputManager;


};

#endif
