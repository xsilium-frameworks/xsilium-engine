#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <Input/InputManager.h>
#include <Event/EventManager.h>
#include "GameStateListener.h"


class GameState
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
	bool pause(){ return true;};
	void resume(){};

	virtual void update(double timeSinceLastFrame) = 0;

	virtual void processEvent(Event * event) = 0;

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

};


#endif
