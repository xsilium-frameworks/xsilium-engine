/*
 * \file GameStateListener.h
 *
 *  Created on: \date 15 ao�t 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GAMESTATELISTENER_H_
#define GAMESTATELISTENER_H_

class GameState ;

class GameStateListener : public Ogre::FrameListener
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

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent){
		return true;
	}
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent){
		return true;
	}
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent){
		return true;
	}

};


#endif /* GAMESTATELISTENER_H_ */
