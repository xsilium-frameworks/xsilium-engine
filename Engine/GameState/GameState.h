#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "XsiliumFramework.h"
#include "InputManager/InputManager.h"
#include "DotSceneLoader/DotSceneLoader.h"

class GameState;

class GameStateListener
{
public:
	GameStateListener(){};
	virtual ~GameStateListener(){};

	virtual void manageGameState(Ogre::String stateName, GameState* state) = 0;

	virtual GameState*	findByName(Ogre::String stateName) = 0;
	virtual void		changeGameState(GameState *state) = 0;
	virtual bool		pushGameState(GameState* state) = 0;
	virtual void		popGameState() = 0;
	virtual void		pauseGameState() = 0;
	virtual void		shutdown() = 0;
    virtual void        popAllAndPushGameState(GameState* state) = 0;
};

class GameState
{
public:
	static void create(GameStateListener* parent, const Ogre::String name){};

	virtual ~GameState(){};

	void destroy(){delete this;}

	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual bool pause(){return true;}
	virtual void resume(){};
	virtual void update(double timeSinceLastFrame) = 0;

protected:
	GameState(){};
	GameState*	findByName(Ogre::String stateName){return m_pParent->findByName(stateName);}
	void		changeGameState(GameState* state){m_pParent->changeGameState(state);}
	bool		pushGameState(GameState* state){return m_pParent->pushGameState(state);}
	void		popGameState(){m_pParent->popGameState();}
	void		shutdown(){m_pParent->shutdown();}
    void        popAllAndPushGameState(GameState* state){m_pParent->popAllAndPushGameState(state);}

	GameStateListener*			m_pParent;

	Ogre::Camera*				m_pCamera;
	Ogre::SceneManager*			m_pSceneMgr;
    Ogre::FrameEvent            m_FrameEvent;
    Ogre::FrameEvent            e;
    Ogre::RenderWindow* 		m_Window;
};

#define DECLARE_GAMESTATE_CLASS(T)										\
static void create(GameStateListener* parent, const Ogre::String name)	\
{																		\
	T* myGameState = new T();											\
	myGameState->m_pParent = parent;										\
	parent->manageGameState(name, myGameState);							\
}

#endif
