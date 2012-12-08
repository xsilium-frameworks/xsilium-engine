/*
 * \file GameStateManager.cpp
 *
 *  Created on: \date 8 dŽc. 2012
 *      Author: \author joda
 *  \brief :
 */

#include "GameState/GameStateManager.h"

GameStateManager::GameStateManager()
{
	mShutdown = false;
	inputManager = InputManager::getSingletonPtr();
}

/** Cleans up the game states before the instance dies. */
GameStateManager::~GameStateManager()
{
    // clean up all the states on the stack
    while (!mStateStack.empty())
    {
        cleanup(mStateStack.back());
        mStateStack.back()->exit();
        mStateStack.pop_back();
    }

    // destroy the game states
    while(!mStates.empty())
    {
        mStates.back().state->destroy();
        mStates.pop_back();
    }
}

/** Store a game state to manage. */
void GameStateManager::ManageGameState(Ogre::String state_name,GameState *state)
{
    state_info new_state_info;
    new_state_info.name=state_name;
    new_state_info.state=state;
    mStates.push_back(new_state_info);
}

/** Find a game state by name.
    @Remarks returns 0 on failure.*/
GameState *GameStateManager::findByName(Ogre::String state_name)
{
    std::vector<state_info>::iterator itr;

    for(itr=mStates.begin();itr!=mStates.end();itr++)
    {
        if(itr->name==state_name)
            return itr->state;
    }

    return 0;
}

/**  Start game state. This is used to start the game state
     manager functioning with a particular state.
     This function also does the main game loop and
     takes care of the Windows message pump.*/
void GameStateManager::start(GameState *state)
{
    changeGameState(state);

	int timeSinceLastFrame = 1;
	int startTime = 0;

    while (!mShutdown)
    {

    	if(XsiliumFramework::getInstance()->m_pRenderWnd->isClosed())
    		mShutdown = true;

    	Ogre::WindowEventUtilities::messagePump();

    	if(XsiliumFramework::getInstance()->m_pRenderWnd->isActive())
    	{
    		startTime = XsiliumFramework::getInstance()->m_pTimer->getMillisecondsCPU();

    		inputManager->capture();

    		mStateStack.back()->update(timeSinceLastFrame);

    		XsiliumFramework::getInstance()->updateOgre(timeSinceLastFrame);
    		XsiliumFramework::getInstance()->m_pRoot->renderOneFrame();

    		timeSinceLastFrame = XsiliumFramework::getInstance()->m_pTimer->getMillisecondsCPU() - startTime;
    	}
    	else
    	{
    		#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    	        Sleep(1000);
    		#else
    	        sleep(1);
    	    #endif
            XsiliumFramework::getInstance()->m_pRoot->renderOneFrame();
    	}
    }
}

/** Change to a game state.  This replaces the current game state
    with a new game state.  The current game state ends before
    the new begins. */
void GameStateManager::changeGameState(GameState* state)
{
    // cleanup the current game state
    if ( !mStateStack.empty() )
    {
        cleanup(mStateStack.back());
        mStateStack.back()->exit();
        mStateStack.pop_back();
    }

    // store and init the new game state
    mStateStack.push_back(state);
    init(state);
    mStateStack.back()->enter();
}

/** Push a game state onto the stack. This pauses the current game state
    and begins a new game state. If the current game state refuses to
    be paused, this will return false. */
bool GameStateManager::pushGameState(GameState* state)
{
    // pause current game state
    if ( !mStateStack.empty() )
    {
        if(!mStateStack.back()->pause())
            return false;
        cleanup(mStateStack.back());
    }

    // store and init the new state
    mStateStack.push_back(state);
    init(state);
    mStateStack.back()->enter();

    return true;
}

/** Pop a game state off the stack. This destroys the current game state
    and returns control to the previous game state. */
void GameStateManager::popGameState(void)
{
    // cleanup the current game state
    if ( !mStateStack.empty() )
    {
        cleanup(mStateStack.back());
        mStateStack.back()->exit();
        mStateStack.pop_back();
    }

    // resume previous game state or quit if there isn't one
    if ( !mStateStack.empty() )
    {
        init(mStateStack.back());
        mStateStack.back()->resume();
    }
    else
    	Shutdown();
}

/** Special case function to shutdown the system. */
void GameStateManager::Shutdown()
{
    mShutdown=true;
}

/** This initializes a game state to receive the events. */
void GameStateManager::init(GameState *state)
{
	XsiliumFramework::getInstance()->m_pRoot->addFrameListener(state);
}

/** This removes event handling from a previous game state. */
void GameStateManager::cleanup(GameState *state)
{
	XsiliumFramework::getInstance()->m_pRoot->removeFrameListener(state);
}
