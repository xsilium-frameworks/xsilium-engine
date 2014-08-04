#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Engine/Engine.h"
#include "Input/InputManager.h"
#include "Event/EventManager.h"

class GameState;

class GameStateListener
{
public:
	GameStateListener(){};
	virtual ~GameStateListener(){};

	virtual void addGameState(Ogre::String stateName, GameState* state) = 0;

	virtual GameState*	findByName(Ogre::String stateName) = 0;
	virtual void		changeGameState(GameState *state) = 0;
	virtual bool		pushGameState(GameState* state) = 0;
	virtual void		popGameState() = 0;
	virtual void		shutdown() = 0;
	virtual void        popAllAndPushGameState(GameState* state) = 0;
};

class GameState : public Ogre::FrameListener
{
public:

	template <class myType>
	static void create(GameStateListener* parent, const Ogre::String name)
	{
		myType * myGameState = new myType();
		myGameState->m_pParent = parent;
		parent->addGameState(name, myGameState);
	}

	virtual ~GameState(){};

	void destroy(){delete this;}

	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual bool pause()
	{
		return true;
	}
	virtual void resume(){};
	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent){
		return true;
	}
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent){
		return true;
	}
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent){
		return true;
	}
	void setExit()
	{
		m_bQuit = true;
	}
	void setChangeState()
	{
		changeState = true;
	}

protected:
	GameState(){};
	GameState*	findByName(Ogre::String stateName){return m_pParent->findByName(stateName);}
	void		changeGameState(GameState* state){m_pParent->changeGameState(state);}
	bool		pushGameState(GameState* state){return m_pParent->pushGameState(state);}
	void		popGameState(){m_pParent->popGameState();}
	void		shutdown(){m_pParent->shutdown();}
	void        popAllAndPushGameState(GameState* state){m_pParent->popAllAndPushGameState(state);}


	GameStateListener*			m_pParent;

	Engine::EventManager * eventManager ;

	bool changeState;
	bool m_bQuit;
};


#endif
